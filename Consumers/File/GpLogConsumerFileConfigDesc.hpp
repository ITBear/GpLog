#pragma once

#include "../../Formatters/GpLogFormatterConfigDesc.hpp"

namespace GPlatform {

class GPLOG_API GpLogConsumerFileConfigDesc final: public GpTypeStructBase
{
public:
    CLASS_REMOVE_CTRS_MOVE(GpLogConsumerFileConfigDesc);
    CLASS_DECLARE_DEFAULTS(GpLogConsumerFileConfigDesc)
    TYPE_STRUCT_DECLARE("911f8edc-f5b4-4781-a738-3abf74bf06f5"_sv)

public:
                                GpLogConsumerFileConfigDesc     (void) noexcept;
    virtual                     ~GpLogConsumerFileConfigDesc    (void) noexcept override final;

public:
    std::string                 out_file_path;
    std::string                 out_file_prefix;
    size_byte_t                 file_max_size;
    milliseconds_t              max_flush_period;
    size_byte_t                 max_buffer_size;
    GpLogFormatterConfigDesc    formatter;
};

}//namespace GPlatform
