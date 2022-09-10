#pragma once

#include "GpLogChain.hpp"
#include "Consumers/GpLogConsumerFactory.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogQueue
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogQueue)
	CLASS_DECLARE_DEFAULTS(GpLogQueue)

	using ChainsByIdT	= GpElementsCatalog<GpUUID, GpLogChain::SP>;
	using ChainsEndedT	= GpLogChain::C::Queue::SP;

public:
								GpLogQueue			(void) noexcept = default;
								~GpLogQueue			(void) noexcept = default;

	bool						IsEmpty				(void) const noexcept;
	void						AddElement			(const GpUUID&	aChainId,
													 GpLogElement&&	aLogElement);
	void						EndChain			(const GpUUID&	aChainId);
	GpLogChain::C::Opt::SP		PopFromEnd			(void);
	ChainsByIdT					RemoveNotEnded		(void) noexcept {return iChainsById.UnregisterAll();}

private:
	void						PushToEnd			(GpLogChain::SP&& aChain);
	GpLogChain::SP				FindOrRegisterChain	(const GpUUID& aChainId);

private:
	ChainsByIdT					iChainsById;
	mutable GpSpinlock			iChainsEndedLock;
	ChainsEndedT				iChainsEnded;
};

}//namespace GPlatform
