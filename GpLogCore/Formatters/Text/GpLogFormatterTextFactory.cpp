#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterTextFactory.hpp>
#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterText.hpp>

namespace GPlatform {

GpLogFormatterTextFactory::GpLogFormatterTextFactory (void) noexcept
{
}

GpLogFormatterTextFactory::~GpLogFormatterTextFactory (void) noexcept
{
}

GpByteSerializer::SP    GpLogFormatterTextFactory::NewInstance (void) const
{
    return MakeSP<GpLogFormatterText>();
}

}// namespace GPlatform
