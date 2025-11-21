#include <GpLog/GpLogCore/GpLogQueue.hpp>
#include <GpCore2/GpUtils/SyncPrimitives/GpSyncPrimitives.hpp>

namespace GPlatform {

bool    GpLogQueue::Empty (void) const noexcept
{
    GpUniqueLock uniuqeLock{iChainsEndedSpinLock};

    return     (iChainsEnded.empty())
            && (iChainsById.Empty());
}

void    GpLogQueue::AddElement
(
    const GpUUID&   aChainId,
    GpLogElement&&  aLogElement
)
{
    const GpLogMode::EnumT mode = aLogElement.Mode();

    if (mode == GpLogMode::CHAIN_END)
    {
        GpLogChain::SP chain;

        if (aChainId.IsNotZero())
        {
            auto chainOpt = iChainsById.Extract(aChainId);

            if (chainOpt.has_value())
            {
                chain = chainOpt.value();
            } else
            {
                chain = MakeSP<GpLogChain>(aChainId);
            }
        } else
        {
            chain = MakeSP<GpLogChain>(aChainId);
        }

        chain.V().AddElement(std::move(aLogElement));

        PushToEnd(std::move(chain));
    } else
    {
        GpLogChain::SP chain;

        chain = FindOrRegisterChain(aChainId);
        chain.V().AddElement(std::move(aLogElement));
    }
}

void    GpLogQueue::EndChain (const GpUUID& aChainId)
{
    if (aChainId.IsZero())
    {
        return;
    }

    auto chainOpt = iChainsById.Extract(aChainId);

    if (chainOpt.has_value())
    {
        PushToEnd(std::move(chainOpt.value()));
    }
}

std::optional<GpLogChain::SP>   GpLogQueue::PopFromEnd (void)
{
    GpUniqueLock uniuqeLock{iChainsEndedSpinLock};

    if (iChainsEnded.empty())
    {
        return std::nullopt;
    }

    GpLogChain::SP chain = iChainsEnded.front();
    iChainsEnded.pop();

    return chain;
}

void    GpLogQueue::PushToEnd (GpLogChain::SP&& aChain)
{
    GpUniqueLock uniuqeLock{iChainsEndedSpinLock};

    iChainsEnded.push(std::move(aChain));
}

GpLogChain::SP  GpLogQueue::FindOrRegisterChain (const GpUUID& aChainId)
{
    auto[chain, status] = iChainsById.FindOrGenerate
    (
        aChainId,
        [aChainId]()
        {
            return MakeSP<GpLogChain>(aChainId);
        }
    );

    return chain;
}

}// namespace GPlatform
