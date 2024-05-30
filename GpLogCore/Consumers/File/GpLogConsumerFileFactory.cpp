#include "GpLogConsumerFileFactory.hpp"
#include "GpLogConsumerFile.hpp"
#include "../../Formatters/Text/GpLogFormatterText.hpp"

namespace GPlatform {

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
