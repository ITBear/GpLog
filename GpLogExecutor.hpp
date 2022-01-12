#pragma once

#include "GpLogRunnable.hpp"

namespace GPlatform {

class GPLOG_API GpLogExecutor
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogExecutor)
    CLASS_DECLARE_DEFAULTS(GpLogExecutor)

public:
                            GpLogExecutor   (void) noexcept;
                            ~GpLogExecutor  (void) noexcept;

    void                    Start           (const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories) noexcept;
    void                    RequestStop     (void) noexcept;
    void                    Join            (void) noexcept;
    void                    WakeupAll       (void) noexcept;
    void                    WakeupOne       (void) noexcept;

    void                    AddElement      (const GpUUID&  aChainId,
                                             GpLogElement&& aLogElement);

    void                    EndChain        (const GpUUID&  aChainId);

private:
    mutable GpSpinlock      iLock;
    GpConditionVar::SP      iCondVar;
    GpThread                iThread;
    GpLogRunnable::SP       iRunnable;
};

}//namespace GPlatform
