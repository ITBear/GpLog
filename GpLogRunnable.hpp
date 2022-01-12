#pragma once

#include "GpLogChain.hpp"
#include "Consumers/GpLogConsumerFactory.hpp"

namespace GPlatform {

class GPLOG_API GpLogRunnable final: public GpRunnable
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogRunnable)
    CLASS_DECLARE_DEFAULTS(GpLogRunnable)

    using ChainsByIdT   = GpElementsCatalog<GpUUID, GpLogChain::SP>;
    using ChainsEndedT  = GpLogChain::C::Queue::SP;

public:
                                        GpLogRunnable       (GpConditionVar::SP                         aCondVar,
                                                             const GpLogConsumerFactory::C::Vec::SP&    aConsumerFactories);
    virtual                             ~GpLogRunnable      (void) noexcept override final;

    virtual void                        Run                 (GpThreadStopToken aStopToken) noexcept override final;

    void                                AddElement          (const GpUUID&      aChainId,
                                                             GpLogElement&&     aLogElement);
    void                                EndChain            (const GpUUID&      aChainId);

private:
    GpLogChain::SP                      FindAndRemoveChain  (const GpUUID& aChainId);
    GpLogChain::SP                      FindOrRegisterChain (const GpUUID& aChainId);

    void                                PushToEnd           (GpLogChain::SP&& aChain);
    std::optional<GpLogChain::SP>       PopFromEnd          (void);

    void                                Consume             (GpLogConsumer::C::Vec::SP& aConsumers);
    void                                ConsumeNotEnded     (GpLogConsumer::C::Vec::SP& aConsumers);
    void                                Flush               (GpLogConsumer::C::Vec::SP& aConsumers);
    GpLogConsumer::C::Vec::SP           CreateConsumers     (void);

private:
    GpLogConsumerFactory::C::Vec::SP    iConsumerFactories;
    ChainsByIdT                         iChainsById;
    GpSpinlock                          iChainsEndedLock;
    ChainsEndedT                        iChainsEnded;
};

}//namespace GPlatform
