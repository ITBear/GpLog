#pragma once

#include <GpLog/GpLogCore/Elements/GpLogElementMsgStr.hpp>

namespace GPlatform {

class GpLogFormatterTextElementMsgStr
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogFormatterTextElementMsgStr)

public:
    inline static std::string   SGen (const GpLogElementMsg& aMessage);
};

std::string GpLogFormatterTextElementMsgStr::SGen (const GpLogElementMsg& aMessage)
{
    const GpLogElementMsgStr& e = static_cast<const GpLogElementMsgStr&>(aMessage);
    return std::string(e.Message());
}

}// namespace GPlatform
