#pragma once

#include "../GpLogConsumerFactory.hpp"
#include "GpLogConsumerFileConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerFileFactory final: public GpLogConsumerFactory
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumerFileFactory)
    CLASS_DD(GpLogConsumerFileFactory)

public:
    inline                          GpLogConsumerFileFactory    (GpByteSerializer::SP aFormatter) noexcept;
    inline                          GpLogConsumerFileFactory    (GpByteSerializer::SP               aFormatter,
                                                                 const GpLogConsumerFileConfigDesc& aConfigDesc);
    virtual                         ~GpLogConsumerFileFactory   (void) noexcept override final;

    virtual GpLogConsumer::SP       NewInstance                 (void) const override final;

private:
    GpLogConsumerFileConfigDesc::SP iConfigDesc;
};

GpLogConsumerFileFactory::GpLogConsumerFileFactory (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumerFactory(std::move(aFormatter))
{
}

GpLogConsumerFileFactory::GpLogConsumerFileFactory
(
    GpByteSerializer::SP                aFormatter,
    const GpLogConsumerFileConfigDesc&  aConfigDesc
):
GpLogConsumerFactory(std::move(aFormatter)),
iConfigDesc(MakeSP<GpLogConsumerFileConfigDesc>(aConfigDesc))
{
}

}//namespace GPlatform
