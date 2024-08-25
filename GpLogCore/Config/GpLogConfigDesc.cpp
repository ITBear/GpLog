#include <GpLog/GpLogCore/Config/GpLogConfigDesc.hpp>
#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConfigDesc, GP_MODULE_UUID)

GpLogConfigDesc::GpLogConfigDesc (const GpLogConfigDesc& aDesc):
GpReflectObject{aDesc},
level       {GpReflectUtils::SCopyValue(aDesc.level)},
flush_period{GpReflectUtils::SCopyValue(aDesc.flush_period)},
consumers   {GpReflectUtils::SCopyValue(aDesc.consumers)}
{
}

GpLogConfigDesc::GpLogConfigDesc (GpLogConfigDesc&& aDesc) noexcept:
GpReflectObject{std::move(aDesc)},
level       {std::move(aDesc.level)},
flush_period{std::move(aDesc.flush_period)},
consumers   {std::move(aDesc.consumers)}
{
}

GpLogConfigDesc::GpLogConfigDesc
(
    const GpLogLevel::EnumT aLevel,
    const seconds_t         aFlushPeriod,
    ConsumersT              aConsumers
) noexcept:
level       {std::move(aLevel)},
flush_period{std::move(aFlushPeriod)},
consumers   {std::move(aConsumers)}
{
}

GpLogConfigDesc::~GpLogConfigDesc (void) noexcept
{
}

void    GpLogConfigDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& aPropsOut)
{
    PROP(level);
    PROP(flush_period);
    PROP(consumers);
}

}// namespace GPlatform
