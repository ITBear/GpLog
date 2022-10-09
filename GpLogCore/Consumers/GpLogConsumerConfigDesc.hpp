#pragma once

#include "../GpLogCore_global.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerConfigDesc: public GpReflectObject
{
public:
    CLASS_DD(GpLogConsumerConfigDesc)
    REFLECT_DECLARE("ee5f2329-dd46-485c-ace8-0abb6f322b92"_uuid)

public:
                                GpLogConsumerConfigDesc     (void) noexcept;
    explicit                    GpLogConsumerConfigDesc     (const GpLogConsumerConfigDesc& aDesc);
    explicit                    GpLogConsumerConfigDesc     (GpLogConsumerConfigDesc&& aDesc) noexcept;
    virtual                     ~GpLogConsumerConfigDesc    (void) noexcept override;

public:
};

}//namespace GPlatform
