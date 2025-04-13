#include <GpLog/GpLogCore/Consumers/GpLogConsumersFactory.hpp>
#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumersFactoryProcessorConsole.hpp>
#include <GpLog/GpLogCore/Consumers/File/GpLogConsumersFactoryProcessorFile.hpp>

namespace GPlatform {

GpLogConsumersFactory::GpLogConsumersFactory (void) noexcept
{
}

GpLogConsumersFactory::~GpLogConsumersFactory (void) noexcept
{
}

void    GpLogConsumersFactory::AddDefaultProcessorConsole (void)
{
    AddProcessor(MakeSP<GpLogConsumersFactoryProcessorConsole>());
}

void    GpLogConsumersFactory::AddDefaultProcessorFile (void)
{
    AddProcessor(MakeSP<GpLogConsumersFactoryProcessorFile>());
}

void    GpLogConsumersFactory::AddProcessor (GpLogConsumersFactoryProcessor::SP aProcessor)
{
    iProcessors.Set
    (
        aProcessor.V().Name(),
        std::move(aProcessor)
    );
}

GpLogConsumerFactory::SP    GpLogConsumersFactory::FactoryFromCfg
(
    std::string_view                aName,
    const GpLogConsumerConfigDesc&  aCfgDesc,
    GpByteSerializer::SP            aFormatter
) const
{
    auto processorOpt = iProcessors.FindOpt(aName);

    VERIFY
    (
        processorOpt.has_value(),
        [aName]()
        {
            return fmt::format
            (
                "Processor not found by name '{}'",
                aName
            );
        }
    );

    return processorOpt.value().V().Process
    (
        aFormatter,
        aCfgDesc
    );
}

}// namespace GPlatform
