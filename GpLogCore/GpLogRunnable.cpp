#include "GpLogRunnable.hpp"
#include "../../GpCore2/GpUtils/Types/Strings/GpStringUtils.hpp"

#include <iostream>

namespace GPlatform {

GpLogRunnable::~GpLogRunnable (void) noexcept
{
}

void    GpLogRunnable::Run (std::atomic_flag& aStopRequest) noexcept
{
    try
    {
        GpLogConsumer::C::Vec::SP consumers = CreateConsumers();
        GpDoOnceInPeriod flushOnceInPeriod(iFlushPeriod, GpDoOnceInPeriod::Mode::AT_FIRST_CALL);

        while (!aStopRequest.test())
        {
            Consume(consumers, flushOnceInPeriod);
            WaitForAndReset(0.25_si_s);
        }

        Consume(consumers, flushOnceInPeriod);
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

void    GpLogRunnable::Consume
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

    notEndedChains.Apply
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

}//namespace GPlatform
