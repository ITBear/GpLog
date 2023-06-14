#pragma once

#include "../../GpCore2/GpUtils/SyncPrimitives/GpSpinlock.hpp"
#include "Elements/GpLogElements.hpp"
#include <mutex>

namespace GPlatform {

class GpLogChain
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogChain)
    CLASS_DD(GpLogChain)

    using ElementsT = GpLogElement::C::List::Val;

public:
    inline              GpLogChain      (const GpUUID& aChainId) noexcept;
                        ~GpLogChain     (void) noexcept = default;

    const GpUUID&       ChainId         (void) const noexcept {return iChainId;}
    inline void         AddElement      (GpLogElement&& aElement);
    const ElementsT&    Elements        (void) const {return iElements;}

private:
    mutable GpSpinlock  iLock;
    const GpUUID        iChainId;
    ElementsT           iElements;
};

GpLogChain::GpLogChain (const GpUUID& aChainId) noexcept:
iChainId(aChainId)
{
}

void    GpLogChain::AddElement (GpLogElement&& aElement)
{
    std::scoped_lock lock(iLock);
    iElements.push_back(std::move(aElement));
}

}//namespace GPlatform
