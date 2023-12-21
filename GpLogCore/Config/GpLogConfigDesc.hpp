#pragma once

#include "../GpLogLevel.hpp"
#include "../Consumers/GpLogConsumerConfigDesc.hpp"

#include <GpCore2/GpUtils/Types/Units/SI/GpUnitsSI_Time.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogConfigDesc final: public GpReflectObject
{
public:
    CLASS_DD(GpLogConfigDesc)
    REFLECT_DECLARE(u8"f007fab7-abbf-4ced-a230-0d6c18a73bdd"_uuid)

    using CategoryLevelsT   = std::map<std::u8string, std::u8string, std::less<>>;
    using ConsumersT        = GpLogConsumerConfigDesc::C::MapStr::SP;

public:
                            GpLogConfigDesc     (void) noexcept = default;
    inline                  GpLogConfigDesc     (const GpLogConfigDesc& aDesc);
    inline                  GpLogConfigDesc     (GpLogConfigDesc&& aDesc) noexcept;
    inline                  GpLogConfigDesc     (const GpLogLevel::EnumT    aMinLevel,
                                                 const seconds_t            aFlushPeriod,
                                                 ConsumersT                 aConsumers) noexcept;
    virtual                 ~GpLogConfigDesc    (void) noexcept override final;

public:
    GpLogLevel              min_level       = GpLogLevel::INFO;
    seconds_t               flush_period    = 3.0_si_s;
    ConsumersT              consumers;
};

GpLogConfigDesc::GpLogConfigDesc (const GpLogConfigDesc& aDesc):
GpReflectObject(aDesc),
min_level   (GpReflectUtils::SCopyValue(aDesc.min_level)),
flush_period(GpReflectUtils::SCopyValue(aDesc.flush_period)),
consumers   (GpReflectUtils::SCopyValue(aDesc.consumers))
{
}

GpLogConfigDesc::GpLogConfigDesc (GpLogConfigDesc&& aDesc) noexcept:
GpReflectObject(std::move(aDesc)),
min_level   (std::move(aDesc.min_level)),
flush_period(std::move(aDesc.flush_period)),
consumers   (std::move(aDesc.consumers))
{
}

GpLogConfigDesc::GpLogConfigDesc
(
    const GpLogLevel::EnumT aMinLevel,
    const seconds_t         aFlushPeriod,
    ConsumersT              aConsumers
) noexcept:
min_level   (std::move(aMinLevel)),
flush_period(std::move(aFlushPeriod)),
consumers   (std::move(aConsumers))
{
}

}//namespace GPlatform
