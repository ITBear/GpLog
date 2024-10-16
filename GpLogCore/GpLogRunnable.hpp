#pragma once

#include <GpLog/GpLogCore/GpLogQueue.hpp>
#include <GpLog/GpLogCore/Consumers/GpLogConsumersFactory.hpp>
#include <GpCore2/GpUtils/Threads/GpRunnable.hpp>
#include <GpCore2/GpUtils/Threads/Timers/GpDoOnceInPeriod.hpp>

#include <atomic>

namespace GPlatform {

class GP_LOG_CORE_API GpLogRunnable final: public GpRunnable
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogRunnable)
    CLASS_DD(GpLogRunnable)

public:
                                        GpLogRunnable       (const GpLogConsumerFactory::C::Vec::SP aConsumerFactories,
                                                             const seconds_t                        aFlushPeriod,
                                                             GpLogQueue&                            aLogQueue);
    virtual                             ~GpLogRunnable      (void) noexcept override final;

    void                                FlushExternal       (void);

    virtual void                        Run                 (std::atomic_flag& aStopRequest) noexcept override final;

protected:
    virtual void                        OnNotify            (void) noexcept override final;

private:
    void                                ConsumeAll          (GpLogConsumer::C::Vec::SP& aConsumers,
                                                             GpDoOnceInPeriod&          aFlushOnceInPeriod);
    void                                ConsumeNotEnded     (GpLogConsumer::C::Vec::SP& aConsumers);
    void                                Flush               (GpLogConsumer::C::Vec::SP& aConsumers);
    GpLogConsumer::C::Vec::SP           CreateConsumers     (void);

private:
    GpLogConsumerFactory::C::Vec::SP    iConsumerFactories;
    const seconds_t                     iFlushPeriod;
    GpLogQueue&                         iLogQueue;
    std::atomic_bool                    iIsFlushExternal;
};

}// namespace GPlatform
