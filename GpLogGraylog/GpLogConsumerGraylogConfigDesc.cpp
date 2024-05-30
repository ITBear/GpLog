#include "GpLogConsumerGraylogConfigDesc.hpp"

#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerGraylogConfigDesc, GP_MODULE_UUID)

GpLogConsumerGraylogConfigDesc::~GpLogConsumerGraylogConfigDesc (void) noexcept
{
}

void    GpLogConsumerGraylogConfigDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& /*aPropsOut*/)
{
    //PROP(formatter);
}

}// namespace GPlatform
