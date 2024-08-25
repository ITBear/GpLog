#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumersFactoryProcessorConsole.hpp>
#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsoleConfigDesc.hpp>
#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsoleFactory.hpp>

#include <GpCore2/GpReflection/GpReflectManager.hpp>

namespace GPlatform {

GpLogConsumersFactoryProcessorConsole::GpLogConsumersFactoryProcessorConsole (void):
GpLogConsumersFactoryProcessor{"console"}
{
}

GpLogConsumersFactoryProcessorConsole::~GpLogConsumersFactoryProcessorConsole (void) noexcept
{
}

GpLogConsumerFactory::SP    GpLogConsumersFactoryProcessorConsole::Process
(
    GpByteSerializer::SP            aFormatter,
    const GpLogConsumerConfigDesc&  aCfgDesc
) const
{
    const GpLogConsumerConsoleConfigDesc& consoleCfgDesc = GpReflectManager::SCastRef<const GpLogConsumerConsoleConfigDesc>(aCfgDesc);

    return MakeSP<GpLogConsumerConsoleFactory>
    (
        std::move(aFormatter),
        consoleCfgDesc
    );
}

}// namespace GPlatform
