#pragma once

#include <GpLog/GpLogCore/Consumers/GpLogConsumerFactory.hpp>
#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsoleConfigDesc.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerConsoleFactory final: public GpLogConsumerFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumerConsoleFactory)
    CLASS_DD(GpLogConsumerConsoleFactory)

public:
                                        GpLogConsumerConsoleFactory     (GpByteSerializer::SP aFormatter) noexcept;
                                        GpLogConsumerConsoleFactory     (GpByteSerializer::SP                   aFormatter,
                                                                         const GpLogConsumerConsoleConfigDesc&  aConfigDesc);
    virtual                             ~GpLogConsumerConsoleFactory    (void) noexcept override final = default;

    virtual GpLogConsumer::SP           NewInstance                     (void) const override final;

private:
    GpLogConsumerConsoleConfigDesc::SP  iConfigDesc;
};

}// namespace GPlatform
