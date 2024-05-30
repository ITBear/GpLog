#include "GpLogConfigDesc.hpp"

#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConfigDesc, GP_MODULE_UUID)

GpLogConfigDesc::~GpLogConfigDesc (void) noexcept
{
}

void    GpLogConfigDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& aPropsOut)
{
    PROP(min_level);
    PROP(flush_period);
    PROP(consumers);
}

}// namespace GPlatform
