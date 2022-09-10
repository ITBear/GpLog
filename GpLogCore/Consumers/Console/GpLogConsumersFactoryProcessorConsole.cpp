#include "GpLogConsumersFactoryProcessorConsole.hpp"
#include "GpLogConsumerConsoleConfigDesc.hpp"
#include "GpLogConsumerConsoleFactory.hpp"

namespace GPlatform {

GpLogConsumersFactoryProcessorConsole::GpLogConsumersFactoryProcessorConsole (void):
GpLogConsumersFactoryProcessor("console")
{
}

GpLogConsumersFactoryProcessorConsole::~GpLogConsumersFactoryProcessorConsole (void) noexcept
{
}

GpLogConsumerFactory::SP	GpLogConsumersFactoryProcessorConsole::Process
(
	GpByteSerializer::SP			aFormatter,
	const GpLogConsumerConfigDesc&	aCfgDesc
) const
{
	const GpLogConsumerConsoleConfigDesc& consoleCfgDesc = GpReflectManager::SCastRef<const GpLogConsumerConsoleConfigDesc>(aCfgDesc);

	return MakeSP<GpLogConsumerConsoleFactory>
	(
		std::move(aFormatter),
		consoleCfgDesc
	);
}

}//namespace GPlatform
