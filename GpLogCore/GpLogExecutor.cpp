#include <GpLog/GpLogCore/GpLogExecutor.hpp>

namespace GPlatform {

GpLogExecutor::GpLogExecutor (GpLogQueue& aLogQueue) noexcept:
iThread  {iThreadStopFlag, "Log executor"},
iLogQueue{aLogQueue}
{
}

GpLogExecutor::~GpLogExecutor (void) noexcept
{
}

void    GpLogExecutor::Flush (void)
{
    if (iRunnable != nullptr)
    {
        iRunnable->FlushExternal();
    }
}

void    GpLogExecutor::Start
(
    const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories,
    const seconds_t                         aFlushPeriod
) noexcept
{
    // Create executor
    GpLogRunnable::UP logRunnableUP = std::make_unique<GpLogRunnable>
    (
        aConsumerFactories,
        aFlushPeriod,
        iLogQueue
    );

    iRunnable = logRunnableUP.get();

    // Run
    iThread.Run(std::move(logRunnableUP));
}

}// namespace GPlatform
