#include "GpLogQueue.hpp"

namespace GPlatform {

bool	GpLogQueue::IsEmpty (void) const noexcept
{
	std::scoped_lock lock(iChainsEndedLock);

	return     (iChainsEnded.size() == 0)
			&& (iChainsById.Size() == 0);
}

void	GpLogQueue::AddElement
(
	const GpUUID&	aChainId,
	GpLogElement&&	aLogElement
)
{
	const GpLogMode::EnumT mode = aLogElement.Mode();

	if (mode == GpLogMode::CHAIN_END)
	{
		GpLogChain::SP chain;

		if (aChainId.IsNotZero())
		{
			auto chainOpt = iChainsById.UnregisterOpt(aChainId);

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

void	GpLogQueue::EndChain (const GpUUID& aChainId)
{
	if (aChainId.IsZero())
	{
		return;
	}

	auto chainOpt = iChainsById.UnregisterOpt(aChainId);

	if (chainOpt.has_value())
	{
		PushToEnd(std::move(chainOpt.value()));
	}
}

std::optional<GpLogChain::SP>	GpLogQueue::PopFromEnd (void)
{
	std::scoped_lock lock(iChainsEndedLock);

	if (iChainsEnded.empty())
	{
		return std::nullopt;
	}

	GpLogChain::SP chain = iChainsEnded.front();
	iChainsEnded.pop();

	return chain;
}

void	GpLogQueue::PushToEnd (GpLogChain::SP&& aChain)
{
	std::scoped_lock lock(iChainsEndedLock);
	iChainsEnded.push(std::move(aChain));
}

GpLogChain::SP	GpLogQueue::FindOrRegisterChain (const GpUUID& aChainId)
{
	return iChainsById.FindOrRegister
	(
		aChainId,
		[&]()
		{
			return MakeSP<GpLogChain>(aChainId);
		}
	);
}

}//namespace GPlatform
