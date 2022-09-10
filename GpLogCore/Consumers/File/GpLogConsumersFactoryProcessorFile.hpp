#pragma once

#include "../GpLogConsumersFactoryProcessor.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumersFactoryProcessorFile final: public GpLogConsumersFactoryProcessor
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumersFactoryProcessorFile)
	CLASS_DECLARE_DEFAULTS(GpLogConsumersFactoryProcessorFile)

public:
										GpLogConsumersFactoryProcessorFile	(void);
	virtual								~GpLogConsumersFactoryProcessorFile	(void) noexcept override final;


	virtual GpLogConsumerFactory::SP	Process								(GpByteSerializer::SP			aFormatter,
																			 const GpLogConsumerConfigDesc&	aCfgDesc) const override final;
};

}//namespace GPlatform
