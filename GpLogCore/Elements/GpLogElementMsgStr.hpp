#pragma once

#include "GpLogElementMsg.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogElementMsgStr final: public GpLogElementMsg
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogElementMsgStr)
    CLASS_DD(GpLogElementMsgStr)

public:
    inline                      GpLogElementMsgStr  (std::u8string&& aMessage) noexcept;
    virtual                     ~GpLogElementMsgStr (void) noexcept override final;

    std::u8string_view          Message             (void) const noexcept {return iMessage;}

private:
    std::u8string               iMessage;
};

GpLogElementMsgStr::GpLogElementMsgStr (std::u8string&& aMessage) noexcept:
GpLogElementMsg(TypeT::STR),
iMessage(std::move(aMessage))
{
}

}//namespace GPlatform
