#include "GpLogConsumerGraylogConfigDesc.hpp"
#include "../../GpCore2/GpReflection/GpReflectManager.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerGraylogConfigDesc, GP_MODULE_UUID)

GpLogConsumerGraylogConfigDesc::~GpLogConsumerGraylogConfigDesc (void) noexcept
{
}

void    GpLogConsumerGraylogConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& /*aPropsOut*/)
{
    //PROP(formatter);
}

}//namespace GPlatform
