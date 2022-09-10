#include "GpLogConfigDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConfigDesc, GP_MODULE_UUID)

GpLogConfigDesc::GpLogConfigDesc (void) noexcept
{
}

GpLogConfigDesc::GpLogConfigDesc (const GpLogConfigDesc& aDesc):
GpReflectObject(aDesc),
min_level(GpReflectUtils::SCopyValue(aDesc.min_level)),
flush_period (GpReflectUtils::SCopyValue(aDesc.flush_period)),
consumers    (GpReflectUtils::SCopyValue(aDesc.consumers))
{
}

GpLogConfigDesc::GpLogConfigDesc (GpLogConfigDesc&& aDesc) noexcept:
GpReflectObject(std::move(aDesc)),
min_level(std::move(aDesc.min_level)),
flush_period (std::move(aDesc.flush_period)),
consumers    (std::move(aDesc.consumers))
{
}

GpLogConfigDesc::~GpLogConfigDesc (void) noexcept
{
}

void	GpLogConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& aPropsOut)
{
	PROP(min_level);
	PROP(flush_period);
	PROP(consumers);
}

}//namespace GPlatform
