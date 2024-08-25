#include <GpLog/GpLogCore/GpLogRunnable.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringUtils.hpp>

namespace GPlatform {

GpLogRunnable::GpLogRunnable
(
    const GpLogConsumerFactory::C::Vec::SP  aConsumerFactories,
    const seconds_t                         aFlushPeriod,
    GpLogQueue&                             aLogQueue
):
GpRunnable(),
iConsumerFactories{std::move(aConsumerFactories)},
iFlushPeriod      {aFlushPeriod},
iLogQueue         {aLogQueue}
{
}

GpLogRunnable::~GpLogRunnable (void) noexcept
{
}

void    GpLogRunnable::FlushExternal (void)
{
    iIsFlushExternal.store(true, std::memory_order_release);

    while (iIsFlushExternal.load(std::memory_order_acquire) == true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void    GpLogRunnable::Run (std::atomic_flag& aStopRequest) noexcept
{
    try
    {
        GpLogConsumer::C::Vec::SP consumers = CreateConsumers();
        GpDoOnceInPeriod flushOnceInPeriod(iFlushPeriod, GpDoOnceInPeriod::Mode::AT_FIRST_CALL);

        while (!aStopRequest.test())
        {
            ConsumeAll(consumers, flushOnceInPeriod);

            if (iIsFlushExternal.load(std::memory_order_acquire) == false)
            {
                WaitForAndReset(0.25_si_s);
            } else
            {
                iIsFlushExternal.store(false, std::memory_order_release);
            }
        }

        ConsumeAll(consumers, flushOnceInPeriod);
        ConsumeNotEnded(consumers);
        Flush(consumers);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[GpLogRunnable::Run]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[GpLogRunnable::Run]: unknown exception"_sv);
    }
}

void    GpLogRunnable::OnNotify (void) noexcept
{
    // NOP
}

void    GpLogRunnable::ConsumeAll
(
    GpLogConsumer::C::Vec::SP&  aConsumers,
    GpDoOnceInPeriod&           aFlushOnceInPeriod
)
{
    std::optional<GpLogChain::SP> chain = iLogQueue.PopFromEnd();

    while (chain.has_value())
    {
        for (auto& consumer: aConsumers)
        {
            consumer.V().Consume(chain.value());
        }

        aFlushOnceInPeriod.Do
        (
            [&](){Flush(aConsumers);}
        );

        chain = iLogQueue.PopFromEnd();
    }
}

void    GpLogRunnable::ConsumeNotEnded (GpLogConsumer::C::Vec::SP& aConsumers)
{
    auto notEndedChains = iLogQueue.RemoveNotEnded();

    notEndedChains.ApplyToAll
    (
        [&](auto& aChain)
        {
            for (auto& consumer: aConsumers)
            {
                consumer.V().Consume(aChain);
            }
        }
    );
}

void    GpLogRunnable::Flush (GpLogConsumer::C::Vec::SP& aConsumers)
{
    for (auto& consumer: aConsumers)
    {
        consumer.V().OnFlush();
    }
}

GpLogConsumer::C::Vec::SP   GpLogRunnable::CreateConsumers (void)
{
    GpLogConsumer::C::Vec::SP consumers;

    for (auto& consumerFactory: iConsumerFactories)
    {
        consumers.emplace_back(consumerFactory.V().NewInstance());
    }

    return consumers;
}

}// namespace GPlatform
