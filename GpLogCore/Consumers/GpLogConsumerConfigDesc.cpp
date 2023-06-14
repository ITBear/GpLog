#include "GpLogConsumerConfigDesc.hpp"
#include "../../../GpCore2/GpReflection/GpReflectManager.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerConfigDesc, GP_MODULE_UUID)

GpLogConsumerConfigDesc::~GpLogConsumerConfigDesc (void) noexcept
{
}

void    GpLogConsumerConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& /*aPropsOut*/)
{
}

}//namespace GPlatform
