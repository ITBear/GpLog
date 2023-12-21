#include "GpLogConsumersFactoryProcessorFile.hpp"
#include "GpLogConsumerFileConfigDesc.hpp"
#include "GpLogConsumerFileFactory.hpp"

#include <GpCore2/GpReflection/GpReflectManager.hpp>

namespace GPlatform {

GpLogConsumersFactoryProcessorFile::GpLogConsumersFactoryProcessorFile (void):
GpLogConsumersFactoryProcessor(u8"file")
{
}

GpLogConsumersFactoryProcessorFile::~GpLogConsumersFactoryProcessorFile (void) noexcept
{
}

GpLogConsumerFactory::SP    GpLogConsumersFactoryProcessorFile::Process
(
    GpByteSerializer::SP            aFormatter,
    const GpLogConsumerConfigDesc&  aCfgDesc
) const
{
    const GpLogConsumerFileConfigDesc& fileCfgDesc = GpReflectManager::SCastRef<const GpLogConsumerFileConfigDesc>(aCfgDesc);

    return MakeSP<GpLogConsumerFileFactory>
    (
        std::move(aFormatter),
        fileCfgDesc
    );
}

}//namespace GPlatform
