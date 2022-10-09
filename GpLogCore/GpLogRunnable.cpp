#include "GpLogRunnable.hpp"

#include <iostream>

namespace GPlatform {

GpLogRunnable::~GpLogRunnable (void) noexcept
{
}

void    GpLogRunnable::Run (GpThreadStopToken aStopToken) noexcept
{
    try
    {
        GpLogConsumer::C::Vec::SP consumers = CreateConsumers();
        GpDoOnceInPeriod flushOnceInPeriod(iFlushPeriod);

        while (!aStopToken.stop_requested())
        {
            Consume(consumers, flushOnceInPeriod);

            if (WaitForWakeup(0.5_si_s) == false)
            {
                std::cerr << "WaitForWakeup return false"_sv << std::endl;
            }
        }

        Consume(consumers, flushOnceInPeriod);
        ConsumeNotEnded(consumers);
        Flush(consumers);
    } catch (const std::exception& e)
    {
        std::cerr << "[GpLogRunnable::Run]: exception " << e.what() << std::endl;
    } catch (...)
    {
        std::cerr << "[GpLogRunnable::Run]: unknown exception " << std::endl;
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
