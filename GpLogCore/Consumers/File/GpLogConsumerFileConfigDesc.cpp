#include "GpLogConsumerFileConfigDesc.hpp"

#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerFileConfigDesc, GP_MODULE_UUID)

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

GpLogConsumerFileConfigDesc::~GpLogConsumerFileConfigDesc (void) noexcept
{
}

void    GpLogConsumerFileConfigDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& aPropsOut)
{
    PROP(out_file_path);
    PROP(out_file_prefix);
    PROP(file_max_size);
    PROP(max_flush_period);
    PROP(max_buffer_size);
}

}// namespace GPlatform
