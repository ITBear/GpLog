#pragma once

#include "../GpLogConsumerConfigDesc.hpp"
#include "../../../../GpCore2/GpUtils/Types/Units/SI/GpUnitsSI_Time.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerFileConfigDesc final: public GpLogConsumerConfigDesc
{
public:
    CLASS_DD(GpLogConsumerFileConfigDesc)
    REFLECT_DECLARE(u8"911f8edc-f5b4-4781-a738-3abf74bf06f5"_uuid)

public:
                        GpLogConsumerFileConfigDesc     (void) noexcept = default;
    inline              GpLogConsumerFileConfigDesc     (const GpLogConsumerFileConfigDesc& aDesc);
    inline              GpLogConsumerFileConfigDesc     (GpLogConsumerFileConfigDesc&& aDesc) noexcept;
    virtual             ~GpLogConsumerFileConfigDesc    (void) noexcept override final;

public:
    std::u8string       out_file_path;
    std::u8string       out_file_prefix;
    size_byte_t         file_max_size;
    milliseconds_t      max_flush_period;
    size_byte_t         max_buffer_size;
};

GpLogConsumerFileConfigDesc::GpLogConsumerFileConfigDesc (const GpLogConsumerFileConfigDesc& aDesc):
GpLogConsumerConfigDesc(aDesc),
out_file_path   (GpReflectUtils::SCopyValue(aDesc.out_file_path)),
out_file_prefix (GpReflectUtils::SCopyValue(aDesc.out_file_prefix)),
file_max_size   (GpReflectUtils::SCopyValue(aDesc.file_max_size)),
max_flush_period(GpReflectUtils::SCopyValue(aDesc.max_flush_period)),
max_buffer_size (GpReflectUtils::SCopyValue(aDesc.max_buffer_size))
{
}

GpLogConsumerFileConfigDesc::GpLogConsumerFileConfigDesc (GpLogConsumerFileConfigDesc&& aDesc) noexcept:
GpLogConsumerConfigDesc(std::move(aDesc)),
out_file_path   (std::move(aDesc.out_file_path)),
out_file_prefix (std::move(aDesc.out_file_prefix)),
file_max_size   (std::move(aDesc.file_max_size)),
max_flush_period(std::move(aDesc.max_flush_period)),
max_buffer_size (std::move(aDesc.max_buffer_size))
{
}

}//namespace GPlatform
