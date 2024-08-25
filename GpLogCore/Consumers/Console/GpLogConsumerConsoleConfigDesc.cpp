#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsoleConfigDesc.hpp>
#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerConsoleConfigDesc, GP_MODULE_UUID)

GpLogConsumerConsoleConfigDesc::GpLogConsumerConsoleConfigDesc (void) noexcept
{
}

GpLogConsumerConsoleConfigDesc::GpLogConsumerConsoleConfigDesc (const GpLogConsumerConsoleConfigDesc& aDesc):
GpLogConsumerConfigDesc{aDesc}
{
}

GpLogConsumerConsoleConfigDesc::GpLogConsumerConsoleConfigDesc (GpLogConsumerConsoleConfigDesc&& aDesc) noexcept:
GpLogConsumerConfigDesc{std::move(aDesc)}
{
}

GpLogConsumerConsoleConfigDesc::~GpLogConsumerConsoleConfigDesc (void) noexcept
{
}

void    GpLogConsumerConsoleConfigDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& /*aPropsOut*/)
{
}

}// namespace GPlatform
