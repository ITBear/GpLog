#pragma once

#include "../GpLogConsumerFactory.hpp"
#include "GpLogConsumerConsoleConfigDesc.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerConsoleFactory final: public GpLogConsumerFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumerConsoleFactory)
    CLASS_DD(GpLogConsumerConsoleFactory)

public:
    inline                              GpLogConsumerConsoleFactory     (GpByteSerializer::SP aFormatter) noexcept;
    inline                              GpLogConsumerConsoleFactory     (GpByteSerializer::SP                   aFormatter,
                                                                         const GpLogConsumerConsoleConfigDesc&  aConfigDesc);
    virtual                             ~GpLogConsumerConsoleFactory    (void) noexcept override final = default;

    virtual GpLogConsumer::SP           NewInstance                     (void) const override final;

private:
    GpLogConsumerConsoleConfigDesc::SP  iConfigDesc;
};

GpLogConsumerConsoleFactory::GpLogConsumerConsoleFactory (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumerFactory(std::move(aFormatter))
{
}

GpLogConsumerConsoleFactory::GpLogConsumerConsoleFactory
(
    GpByteSerializer::SP                    aFormatter,
    const GpLogConsumerConsoleConfigDesc&   aConfigDesc
):
GpLogConsumerFactory(std::move(aFormatter)),
iConfigDesc(MakeSP<GpLogConsumerConsoleConfigDesc>(aConfigDesc))
{
}

}// namespace GPlatform
