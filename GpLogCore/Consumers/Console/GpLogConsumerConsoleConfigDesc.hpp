#pragma once

#include "../GpLogConsumerConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerConsoleConfigDesc final: public GpLogConsumerConfigDesc
{
public:
    CLASS_DD(GpLogConsumerConsoleConfigDesc)
    REFLECT_DECLARE("4684da56-0aeb-45f4-aa0b-27fe6711d97e"_uuid)

public:
                        GpLogConsumerConsoleConfigDesc  (void) noexcept;
                        GpLogConsumerConsoleConfigDesc  (const GpLogConsumerConsoleConfigDesc& aDesc);
                        GpLogConsumerConsoleConfigDesc  (GpLogConsumerConsoleConfigDesc&& aDesc) noexcept;
    virtual             ~GpLogConsumerConsoleConfigDesc (void) noexcept override final;

public:
};

}// namespace GPlatform
