#include <GpLog/GpLogCore/Consumers/File/GpLogConsumerFileFactory.hpp>
#include <GpLog/GpLogCore/Consumers/File/GpLogConsumerFile.hpp>
#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterText.hpp>

namespace GPlatform {

GpLogConsumerFileFactory::GpLogConsumerFileFactory (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumerFactory{std::move(aFormatter)}
{
}

GpLogConsumerFileFactory::GpLogConsumerFileFactory
(
    GpByteSerializer::SP                aFormatter,
    const GpLogConsumerFileConfigDesc&  aConfigDesc
):
GpLogConsumerFactory{std::move(aFormatter)},
iConfigDesc{MakeSP<GpLogConsumerFileConfigDesc>(aConfigDesc)}
{
}

GpLogConsumerFileFactory::~GpLogConsumerFileFactory (void) noexcept
{
}

GpLogConsumer::SP   GpLogConsumerFileFactory::NewInstance (void) const
{
    const GpLogConsumerFileConfigDesc& configDesc = iConfigDesc.V();

    return MakeSP<GpLogConsumerFile>
    (
        configDesc.out_file_path,
        configDesc.out_file_prefix,
        configDesc.file_max_size,
        configDesc.max_flush_period,
        configDesc.max_buffer_size,
        Formatter()
    );
}

}// namespace GPlatform
