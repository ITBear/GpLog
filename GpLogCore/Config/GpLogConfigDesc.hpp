#pragma once

#include "../GpLogLevel.hpp"
#include "../Consumers/GpLogConsumerConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConfigDesc final: public GpReflectObject
{
public:
    CLASS_DD(GpLogConfigDesc)
    REFLECT_DECLARE("f007fab7-abbf-4ced-a230-0d6c18a73bdd"_uuid)

    using CategoryLevelsT   = std::map<std::string, std::string, std::less<>>;
    using ConsumersT        = GpLogConsumerConfigDesc::C::MapStr::SP;

public:
                            GpLogConfigDesc     (void) noexcept;
                            GpLogConfigDesc     (const GpLogConfigDesc& aDesc);
                            GpLogConfigDesc     (GpLogConfigDesc&& aDesc) noexcept;
    virtual                 ~GpLogConfigDesc    (void) noexcept override final;

public:
    GpLogLevel              min_level       = GpLogLevel::INFO;
    seconds_t               flush_period    = 3.0_si_s;
    ConsumersT              consumers;
};

}//namespace GPlatform
