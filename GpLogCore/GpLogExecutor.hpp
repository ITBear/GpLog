#pragma once

#include "GpLogRunnable.hpp"
#include <GpCore2/GpUtils/Threads/GpThread.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogExecutor
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogExecutor)

public:
    inline              GpLogExecutor   (GpLogQueue& aLogQueue) noexcept;
                        ~GpLogExecutor  (void) noexcept;

    void                Start           (const GpLogConsumerFactory::C::Vec::SP&    aConsumerFactories,
                                         const seconds_t                            aFlushPeriod) noexcept;
    inline void         RequestStop     (void) noexcept;
    inline void         Join            (void) noexcept;

private:
    GpThread            iThread;
    GpLogQueue&         iLogQueue;
};

GpLogExecutor::GpLogExecutor (GpLogQueue& aLogQueue) noexcept:
iThread  (u8"Log executor"),
iLogQueue(aLogQueue)
{
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
