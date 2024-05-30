#include "GpLogConsumersFactory.hpp"
#include "Console/GpLogConsumersFactoryProcessorConsole.hpp"
#include "File/GpLogConsumersFactoryProcessorFile.hpp"

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
    iProcessors.SetOrUpdate
    (
        std::string(aProcessor.V().Name()),
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
    auto processorOpt = iProcessors.GetOpt(aName);

    THROW_COND_GP
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
