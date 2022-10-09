#pragma once

#include "../GpLogConsumerConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerFileConfigDesc final: public GpLogConsumerConfigDesc
{
public:
    CLASS_DD(GpLogConsumerFileConfigDesc)
    REFLECT_DECLARE("911f8edc-f5b4-4781-a738-3abf74bf06f5"_uuid)

public:
                        GpLogConsumerFileConfigDesc     (void) noexcept;
                        GpLogConsumerFileConfigDesc     (const GpLogConsumerFileConfigDesc& aDesc);
                        GpLogConsumerFileConfigDesc     (GpLogConsumerFileConfigDesc&& aDesc) noexcept;
    virtual             ~GpLogConsumerFileConfigDesc    (void) noexcept override final;

public:
    std::string         out_file_path;
    std::string         out_file_prefix;
    size_byte_t         file_max_size;
    milliseconds_t      max_flush_period;
    size_byte_t         max_buffer_size;
};

}//namespace GPlatform
