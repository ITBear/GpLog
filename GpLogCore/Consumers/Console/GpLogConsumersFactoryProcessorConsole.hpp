#pragma once

#include "../GpLogConsumersFactoryProcessor.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumersFactoryProcessorConsole final: public GpLogConsumersFactoryProcessor
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumersFactoryProcessorConsole)
	CLASS_DECLARE_DEFAULTS(GpLogConsumersFactoryProcessorConsole)

public:
										GpLogConsumersFactoryProcessorConsole	(void);
	virtual								~GpLogConsumersFactoryProcessorConsole	(void) noexcept override final;


	virtual GpLogConsumerFactory::SP	Process									(GpByteSerializer::SP			aFormatter,
																				 const GpLogConsumerConfigDesc&	aCfgDesc) const override final;
};

}//namespace GPlatform
