#include "GpLogFormatterTextFactory.hpp"
#include "GpLogFormatterText.hpp"

namespace GPlatform {

GpByteSerializer::SP    GpLogFormatterTextFactory::NewInstance (void) const
{
    return MakeSP<GpLogFormatterText>();
}

}// namespace GPlatform
