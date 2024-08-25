#pragma once

#include <GpLog/GpLogCore/GpLogCore_global.hpp>

#include <GpCore2/GpUtils/Macro/GpMacroClass.hpp>
#include <GpCore2/GpUtils/Types/Containers/GpContainersT.hpp>
#include <GpCore2/GpReflection/GpReflectObject.hpp>
#include <GpCore2/GpReflection/GpReflectUtils.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerConfigDesc: public GpReflectObject
{
public:
    CLASS_DD(GpLogConsumerConfigDesc)
    REFLECT_DECLARE("ee5f2329-dd46-485c-ace8-0abb6f322b92"_uuid)

public:
                GpLogConsumerConfigDesc     (void) noexcept = default;
                GpLogConsumerConfigDesc     (const GpLogConsumerConfigDesc& aDesc);
                GpLogConsumerConfigDesc     (GpLogConsumerConfigDesc&& aDesc) noexcept;
    virtual     ~GpLogConsumerConfigDesc    (void) noexcept override;

public:
};

}// namespace GPlatform
