#include "GpLogConsumerGraylogConfigDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpLogConsumerGraylogConfigDesc, GP_MODULE_UUID)

GpLogConsumerGraylogConfigDesc::GpLogConsumerGraylogConfigDesc (void) noexcept
{
}

GpLogConsumerGraylogConfigDesc::GpLogConsumerGraylogConfigDesc (const GpLogConsumerGraylogConfigDesc& aDesc):
GpLogConsumerConfigDesc(aDesc)
{
}

GpLogConsumerGraylogConfigDesc::GpLogConsumerGraylogConfigDesc (GpLogConsumerGraylogConfigDesc&& aDesc) noexcept:
GpLogConsumerConfigDesc(std::move(aDesc))
{
}

GpLogConsumerGraylogConfigDesc::~GpLogConsumerGraylogConfigDesc (void) noexcept
{
}

void    GpLogConsumerGraylogConfigDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& /*aPropsOut*/)
{
    //PROP(formatter);
}

}//namespace GPlatform
