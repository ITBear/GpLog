#pragma once

#include "GpLogConsumerGraylogConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_GRAYLOG_API GpLogConsumerGraylogFactory final: public GpLogConsumerFactory
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumerGraylogFactory)
    CLASS_DD(GpLogConsumerGraylogFactory)

public:
    inline                              GpLogConsumerGraylogFactory     (GpByteSerializer::SP aFormatter) noexcept;
    inline                              GpLogConsumerGraylogFactory     (GpByteSerializer::SP                   aFormatter,
                                                                         const GpLogConsumerGraylogConfigDesc&  aConfigDesc);
    virtual                             ~GpLogConsumerGraylogFactory    (void) noexcept override final;

    virtual GpLogConsumer::SP           NewInstance                     (void) const override final;

private:
    GpLogConsumerGraylogConfigDesc::SP  iConfigDesc;
};

GpLogConsumerGraylogFactory::GpLogConsumerGraylogFactory (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumerFactory(std::move(aFormatter))
{
}

GpLogConsumerGraylogFactory::GpLogConsumerGraylogFactory
(
    GpByteSerializer::SP                    aFormatter,
    const GpLogConsumerGraylogConfigDesc&   aConfigDesc
):
GpLogConsumerFactory(std::move(aFormatter)),
iConfigDesc(MakeSP<GpLogConsumerGraylogConfigDesc>(aConfigDesc))
{
}

}//namespace GPlatform
