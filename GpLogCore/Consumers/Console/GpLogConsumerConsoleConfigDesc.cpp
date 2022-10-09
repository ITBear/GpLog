#include "GpLogConsumerConsoleConfigDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerConsoleConfigDesc, GP_MODULE_UUID)

GpLogConsumerConsoleConfigDesc::GpLogConsumerConsoleConfigDesc (void) noexcept
{
}

GpLogConsumerConsoleConfigDesc::GpLogConsumerConsoleConfigDesc (const GpLogConsumerConsoleConfigDesc& aDesc):
GpLogConsumerConfigDesc(aDesc)
{
}

GpLogConsumerConsoleConfigDesc::GpLogConsumerConsoleConfigDesc (GpLogConsumerConsoleConfigDesc&& aDesc) noexcept:
GpLogConsumerConfigDesc(std::move(aDesc))
{
}

GpLogConsumerConsoleConfigDesc::~GpLogConsumerConsoleConfigDesc (void) noexcept
{
}

void    GpLogConsumerConsoleConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& /*aPropsOut*/)
{
}

}//namespace GPlatform
