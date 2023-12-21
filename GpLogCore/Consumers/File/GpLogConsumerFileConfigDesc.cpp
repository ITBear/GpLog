#include "GpLogConsumerFileConfigDesc.hpp"

#include <GpCore2/GpReflection/GpReflectManager.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerFileConfigDesc, GP_MODULE_UUID)

GpLogConsumerFileConfigDesc::~GpLogConsumerFileConfigDesc (void) noexcept
{
}

void    GpLogConsumerFileConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& aPropsOut)
{
    PROP(out_file_path);
    PROP(out_file_prefix);
    PROP(file_max_size);
    PROP(max_flush_period);
    PROP(max_buffer_size);
}

}//namespace GPlatform
