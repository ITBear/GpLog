#pragma once

#include <GpLog/GpLogCore/Consumers/GpLogConsumerFactory.hpp>
#include <GpLog/GpLogCore/Consumers/File/GpLogConsumerFileConfigDesc.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumerFileFactory final: public GpLogConsumerFactory
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumerFileFactory)
    CLASS_DD(GpLogConsumerFileFactory)

public:
                                    GpLogConsumerFileFactory    (GpByteSerializer::SP aFormatter) noexcept;
                                    GpLogConsumerFileFactory    (GpByteSerializer::SP               aFormatter,
                                                                 const GpLogConsumerFileConfigDesc& aConfigDesc);
    virtual                         ~GpLogConsumerFileFactory   (void) noexcept override final;

    virtual GpLogConsumer::SP       NewInstance                 (void) const override final;

private:
    GpLogConsumerFileConfigDesc::SP iConfigDesc;
};

}// namespace GPlatform
