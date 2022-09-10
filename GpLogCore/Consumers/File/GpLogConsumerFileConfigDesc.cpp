#include "GpLogConsumerFileConfigDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerFileConfigDesc, GP_MODULE_UUID)

GpLogConsumerFileConfigDesc::GpLogConsumerFileConfigDesc (void) noexcept
{
}

GpLogConsumerFileConfigDesc::GpLogConsumerFileConfigDesc (const GpLogConsumerFileConfigDesc& aDesc):
GpLogConsumerConfigDesc(aDesc),
out_file_path(aDesc.out_file_path),
out_file_prefix(aDesc.out_file_prefix),
file_max_size(aDesc.file_max_size),
max_flush_period(aDesc.max_flush_period),
max_buffer_size(aDesc.max_buffer_size)
{
}

GpLogConsumerFileConfigDesc::GpLogConsumerFileConfigDesc (GpLogConsumerFileConfigDesc&& aDesc) noexcept:
GpLogConsumerConfigDesc(std::move(aDesc)),
out_file_path(std::move(aDesc.out_file_path)),
out_file_prefix(std::move(aDesc.out_file_prefix)),
file_max_size(std::move(aDesc.file_max_size)),
max_flush_period(std::move(aDesc.max_flush_period)),
max_buffer_size(std::move(aDesc.max_buffer_size))
{
}

GpLogConsumerFileConfigDesc::~GpLogConsumerFileConfigDesc (void) noexcept
{
}

void	GpLogConsumerFileConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& aPropsOut)
{
	PROP(out_file_path);
	PROP(out_file_prefix);
	PROP(file_max_size);
	PROP(max_flush_period);
	PROP(max_buffer_size);
}

}//namespace GPlatform
