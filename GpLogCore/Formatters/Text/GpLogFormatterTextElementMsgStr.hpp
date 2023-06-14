#pragma once

#include "../../Elements/GpLogElementMsgStr.hpp"

namespace GPlatform {

class GpLogFormatterTextElementMsgStr
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogFormatterTextElementMsgStr)

public:
    inline static std::u8string SGen (const GpLogElementMsg& aMessage);
};

std::u8string   GpLogFormatterTextElementMsgStr::SGen (const GpLogElementMsg& aMessage)
{
    const GpLogElementMsgStr& e = static_cast<const GpLogElementMsgStr&>(aMessage);
    return std::u8string(e.Message());
}

}//namespace GPlatform
