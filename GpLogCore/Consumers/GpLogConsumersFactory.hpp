#pragma once

#include "GpLogConsumerFactory.hpp"
#include "GpLogConsumerConfigDesc.hpp"
#include "GpLogConsumersFactoryProcessor.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumersFactory
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumersFactory)
	CLASS_DECLARE_DEFAULTS(GpLogConsumersFactory)

	using ProcessorsT = GpElementsCatalog<std::string, GpLogConsumersFactoryProcessor::SP>;

public:
								GpLogConsumersFactory	(void) noexcept = default;
	virtual						~GpLogConsumersFactory	(void) noexcept = default;

	void						AddDefaultProcessors	(void);
	void						AddProcessor			(GpLogConsumersFactoryProcessor::SP aProcessor);

	GpLogConsumerFactory::SP	FactoryFromCfg			(std::string_view				aName,
														 const GpLogConsumerConfigDesc&	aCfgDesc,
														 GpByteSerializer::SP			aFormatter) const;
protected:
	ProcessorsT					iProcessors;
};

}//namespace GPlatform
