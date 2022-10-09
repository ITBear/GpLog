#include "GpLogConsumerConfigDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerConfigDesc, GP_MODULE_UUID)

GpLogConsumerConfigDesc::GpLogConsumerConfigDesc (void) noexcept
{
}

GpLogConsumerConfigDesc::GpLogConsumerConfigDesc (const GpLogConsumerConfigDesc& aDesc):
GpReflectObject(aDesc)
{
}

GpLogConsumerConfigDesc::GpLogConsumerConfigDesc (GpLogConsumerConfigDesc&& aDesc) noexcept:
GpReflectObject(std::move(aDesc))
{
}

GpLogConsumerConfigDesc::~GpLogConsumerConfigDesc (void) noexcept
{
}

void    GpLogConsumerConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& /*aPropsOut*/)
{
}

}//namespace GPlatform
