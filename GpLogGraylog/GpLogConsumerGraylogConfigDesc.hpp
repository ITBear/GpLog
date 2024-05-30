#pragma once

#include "GpLogGraylog_global.hpp"
#include "../GpLogCore/Consumers/GpLogConsumerConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_GRAYLOG_API GpLogConsumerGraylogConfigDesc final: public GpLogConsumerConfigDesc
{
public:
    CLASS_DD(GpLogConsumerGraylogConfigDesc)
    REFLECT_DECLARE("57b8bc51-ea51-4498-93f4-a71010e9c27c"_uuid)

public:
                                GpLogConsumerGraylogConfigDesc  (void) noexcept = default;
    inline                      GpLogConsumerGraylogConfigDesc  (const GpLogConsumerGraylogConfigDesc& aDesc);
    inline                      GpLogConsumerGraylogConfigDesc  (GpLogConsumerGraylogConfigDesc&& aDesc) noexcept;
    virtual                     ~GpLogConsumerGraylogConfigDesc (void) noexcept override final;

public:
};

GpLogConsumerGraylogConfigDesc::GpLogConsumerGraylogConfigDesc (const GpLogConsumerGraylogConfigDesc& aDesc):
GpLogConsumerConfigDesc(aDesc)
{
}

GpLogConsumerGraylogConfigDesc::GpLogConsumerGraylogConfigDesc (GpLogConsumerGraylogConfigDesc&& aDesc) noexcept:
GpLogConsumerConfigDesc(std::move(aDesc))
{
}

}// namespace GPlatform
