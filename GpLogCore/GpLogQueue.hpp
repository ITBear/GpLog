#pragma once

#include <GpLog/GpLogCore/GpLogChain.hpp>
#include <GpCore2/GpUtils/Types/Containers/GpDictionary.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogQueue
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogQueue)
    CLASS_DD(GpLogQueue)

    using ChainsByIdT   = GpDictionary<std::map<GpUUID, GpLogChain::SP>>;
    using ChainsEndedT  = GpLogChain::C::Queue::SP;

public:
                            GpLogQueue          (void) noexcept = default;
                            ~GpLogQueue         (void) noexcept = default;

    bool                    Empty               (void) const noexcept;
    void                    AddElement          (const GpUUID&  aChainId,
                                                 GpLogElement&& aLogElement);
    void                    EndChain            (const GpUUID&  aChainId);
    GpLogChain::C::Opt::SP  PopFromEnd          (void);
    ChainsByIdT             RemoveNotEnded      (void) noexcept {return iChainsById.ExtractAll();}

private:
    void                    PushToEnd           (GpLogChain::SP&& aChain);
    GpLogChain::SP          FindOrRegisterChain (const GpUUID& aChainId);

private:
    ChainsByIdT             iChainsById;
    mutable GpSpinLock      iChainsEndedSpinLock;
    ChainsEndedT            iChainsEnded        GUARDED_BY(iChainsEndedSpinLock);
};

}// namespace GPlatform
