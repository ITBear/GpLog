#pragma once

#include "GpLogRunnable.hpp"

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
    void                RequestStop     (void) noexcept;
    void                Join            (void) noexcept;

private:
    GpThread            iThread;
    GpLogQueue&         iLogQueue;
};

GpLogExecutor::GpLogExecutor (GpLogQueue& aLogQueue) noexcept:
iLogQueue(aLogQueue)
{
}

}//namespace GPlatform
