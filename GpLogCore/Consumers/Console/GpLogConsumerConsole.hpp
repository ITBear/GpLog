#pragma once

#include  <GpLog/GpLogCore/Consumers/GpLogConsumer.hpp>

namespace GPlatform {

class GpLogConsumerConsole final: public GpLogConsumer
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumerConsole)
    CLASS_DD(GpLogConsumerConsole)

public:
                            GpLogConsumerConsole    (GpByteSerializer::SP aFormatter) noexcept;
    virtual                 ~GpLogConsumerConsole   (void) noexcept override final;

    virtual void            Consume                 (GpLogChain::CSP aLogChain) override final;
    virtual void            OnFlush                 (void) noexcept override final;

private:
    GpBytesArray            iTmpBuffer;
};

}// namespace GPlatform
