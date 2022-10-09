#pragma once

#include "GpLogElementMsg.hpp"
#include "../GpLogMarkTraceTS.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogElementMsgMarkTraceTS final: public GpLogElementMsg
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogElementMsgMarkTraceTS)
    CLASS_DD(GpLogElementMsgMarkTraceTS)

public:
    inline                      GpLogElementMsgMarkTraceTS  (GpLogMarkTraceTS&& aMarkTraceTS) noexcept;
    virtual                     ~GpLogElementMsgMarkTraceTS (void) noexcept override final;

    const GpLogMarkTraceTS&     MarkTraceTS                 (void) const noexcept {return iMarkTraceTS;}

private:
    const GpLogMarkTraceTS      iMarkTraceTS;
};

GpLogElementMsgMarkTraceTS::GpLogElementMsgMarkTraceTS (GpLogMarkTraceTS&& aMarkTraceTS) noexcept:
GpLogElementMsg(TypeT::TRACE_TS),
iMarkTraceTS(std::move(aMarkTraceTS))
{
}

}//namespace GPlatform
