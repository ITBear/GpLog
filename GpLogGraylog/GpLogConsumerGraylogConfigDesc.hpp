#pragma once

#include "GpLogGraylog_global.hpp"

namespace GPlatform {

class GP_LOG_GRAYLOG_API GpLogConsumerGraylogConfigDesc final: public GpLogConsumerConfigDesc
{
public:
    CLASS_DD(GpLogConsumerGraylogConfigDesc)
    REFLECT_DECLARE("57b8bc51-ea51-4498-93f4-a71010e9c27c"_uuid)

public:
                                GpLogConsumerGraylogConfigDesc  (void) noexcept;
                                GpLogConsumerGraylogConfigDesc  (const GpLogConsumerGraylogConfigDesc& aDesc);
                                GpLogConsumerGraylogConfigDesc  (GpLogConsumerGraylogConfigDesc&& aDesc) noexcept;
    virtual                     ~GpLogConsumerGraylogConfigDesc (void) noexcept override final;

public:
};

}//namespace GPlatform
