#pragma once

#include "GpLogGraylog_global.hpp"
#include "../GpLogCore/Consumers/GpLogConsumer.hpp"

namespace GPlatform {

class GpLogConsumerGraylog final: public GpLogConsumer
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumerGraylog)
    CLASS_DD(GpLogConsumerGraylog)

public:
                            GpLogConsumerGraylog    (GpByteSerializer::SP aFormatter) noexcept;
    virtual                 ~GpLogConsumerGraylog   (void) noexcept override final;

    virtual void            Consume                 (GpLogChain::CSP aLogChain) override final;
    virtual void            OnFlush                 (void) noexcept override final;

private:
    GpBytesArray            iTmpBuffer;
};

}// namespace GPlatform
