#include "GpLogExecutor.hpp"

namespace GPlatform {

GpLogExecutor::~GpLogExecutor (void) noexcept
{
}

void    GpLogExecutor::Start
(
    const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories,
    const seconds_t                         aFlushPeriod
) noexcept
{
    //Create executor
    GpLogRunnable::SP runnable = MakeSP<GpLogRunnable>
    (
        aConsumerFactories,
        aFlushPeriod,
        iLogQueue
    );

    //Run
    iThread.Run(std::move(runnable));
}

void    GpLogExecutor::RequestStop (void) noexcept
{
    iThread.RequestStop();
}

void    GpLogExecutor::Join (void) noexcept
{
    iThread.Join();
}

}//namespace GPlatform
