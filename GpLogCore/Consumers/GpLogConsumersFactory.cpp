#include "GpLogConsumersFactory.hpp"
#include "Console/GpLogConsumersFactoryProcessorConsole.hpp"
#include "File/GpLogConsumersFactoryProcessorFile.hpp"

namespace GPlatform {

void	GpLogConsumersFactory::AddDefaultProcessors (void)
{
	AddProcessor(MakeSP<GpLogConsumersFactoryProcessorConsole>());
	AddProcessor(MakeSP<GpLogConsumersFactoryProcessorFile>());
}

void	GpLogConsumersFactory::AddProcessor (GpLogConsumersFactoryProcessor::SP aProcessor)
{
	iProcessors.Register
	(
		std::string(aProcessor.V().Name()),
		std::move(aProcessor)
	);
}

GpLogConsumerFactory::SP	GpLogConsumersFactory::FactoryFromCfg
(
	std::string_view				aName,
	const GpLogConsumerConfigDesc&	aCfgDesc,
	GpByteSerializer::SP			aFormatter
) const
{
	auto processorOpt = iProcessors.FindOpt(aName);

	THROW_COND_GP
	(
		processorOpt.has_value(),
		[&](){return "Processor not found by name '"_sv + aName + "'"_sv;}
	);

	return processorOpt.value().get().V().Process
	(
		aFormatter,
		aCfgDesc
	);
}

}//namespace GPlatform
