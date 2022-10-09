#pragma once

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
    std::string resStr;
    resStr.reserve(1024);

    const GpLogElementMsgMarkTraceTS& e = static_cast<const GpLogElementMsgMarkTraceTS&>(aMessage);

    const GpLogMarkTraceTS&         markTraceTS = e.MarkTraceTS();
    const GpLogMarkTS::C::Vec::Val& marks       = markTraceTS.Marks();

    size_t          tsId        = 0;
    microseconds_t  nowHiResTs  = 0.0_si_us;
    microseconds_t  prevHiResTs = 0.0_si_us;
    microseconds_t  duration    = 0.0_si_us;
    microseconds_t  delta       = 0.0_si_us;

    for (const GpLogMarkTS& mark: marks)
    {
        std::string str;

        if (tsId > 0)
        {
            resStr.append("\n"_sv);
        }

        //id
        tsId++;
        str = StrOps::SFromUI64(u_int_64(tsId));
        resStr
            .append("["_sv)
            .append(str)
            .append("]: STS: "_sv);

        //steady ts
        str = StrOps::SFromDouble(mark.SteadyTS().As<seconds_t>().Value());
        resStr
            .append(str)
            .append("s, D: "_sv);

        //Delta
        nowHiResTs = mark.HiResTS();

        if (tsId <= 1)
        {
            prevHiResTs = nowHiResTs;
            delta       = 0.0_si_s;
        } else
        {
            delta       = nowHiResTs - prevHiResTs;
        }

        prevHiResTs = nowHiResTs;
        duration   += delta;

        //Duration
        str = StrOps::SFromDouble(duration.As<seconds_t>().Value());
        resStr
            .append(str)
            .append("s: "_sv);

        //Comment
        resStr
            .append(mark.Comment());

        //Source location
        const auto& sourceLocation = mark.SourceLocation();

        if (sourceLocation.has_value())
        {
            const SourceLocationT& sl = sourceLocation.value();

            resStr
                .append("    Function: '"_sv)
                .append(std::string_view(sl.function_name()))
                .append("', file '"_sv)
                .append(std::string_view(sl.file_name()))
                .append("', line "_sv)
                .append(StrOps::SFromUI64(sl.line()));
        }
    }

    return resStr;
}

}//namespace GPlatform
