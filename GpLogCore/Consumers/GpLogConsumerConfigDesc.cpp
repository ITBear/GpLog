#include <GpLog/GpLogCore/Consumers/GpLogConsumerConfigDesc.hpp>
#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerConfigDesc, GP_MODULE_UUID)

GpLogConsumerConfigDesc::GpLogConsumerConfigDesc (const GpLogConsumerConfigDesc& aDesc):
GpReflectObject{aDesc}
{
}

GpLogConsumerConfigDesc::GpLogConsumerConfigDesc (GpLogConsumerConfigDesc&& aDesc) noexcept:
GpReflectObject{std::move(aDesc)}
{
}

GpLogConsumerConfigDesc::~GpLogConsumerConfigDesc (void) noexcept
{
}

void    GpLogConsumerConfigDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& /*aPropsOut*/)
{
}

}// namespace GPlatform
