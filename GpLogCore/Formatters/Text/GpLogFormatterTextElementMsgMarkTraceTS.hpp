#pragma once

#include <GpCore2/Config/IncludeExt/fmt.hpp>

#include "../../Elements/GpLogElementMsgMarkTraceTS.hpp"

namespace GPlatform {

class GpLogFormatterTextElementMsgMarkTraceTS
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogFormatterTextElementMsgMarkTraceTS)

public:
    inline static std::string   SGen (const GpLogElementMsg& aMessage);
};

std::string GpLogFormatterTextElementMsgMarkTraceTS::SGen (const GpLogElementMsg& aMessage)
{
    const GpLogElementMsgMarkTraceTS&   e           = static_cast<const GpLogElementMsgMarkTraceTS&>(aMessage);
    const GpLogMarkTraceTS&             markTraceTS = e.MarkTraceTS();
    const GpLogMarkTS::C::Vec::Val&     marks       = markTraceTS.Marks();

    std::string res;
    res.reserve(std::size(marks) * 64);

    for (const auto& mark: marks)
    {
        res.append(fmt::format("{}\n", mark));
    }

    return res;
}

}// namespace GPlatform
