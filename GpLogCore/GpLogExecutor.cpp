#include <GpLog/GpLogCore/GpLogExecutor.hpp>

namespace GPlatform {

GpLogExecutor::~GpLogExecutor (void) noexcept
{
    iRunnable.Clear();
}

void    GpLogExecutor::Flush (void)
{
    if (iRunnable.IsNotNULL())
    {
        iRunnable.Vn().FlushExternal();
    }
}

void    GpLogExecutor::Start
(
    const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories,
    const seconds_t                         aFlushPeriod
) noexcept
{
    //Create executor
    iRunnable = MakeSP<GpLogRunnable>
    (
        aConsumerFactories,
        aFlushPeriod,
        iLogQueue
    );

    //Run
    iThread.Run(iRunnable);
}

}// namespace GPlatform
