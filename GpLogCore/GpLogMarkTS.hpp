#pragma once

#include <GpCore2/Config/IncludeExt/fmt.hpp>
#include <GpLog/GpLogCore/GpLogCore_global.hpp>
#include <GpCore2/GpUtils/DateTime/GpDateTimeOps.hpp>

#if defined(GP_USE_TIMERS)

namespace GPlatform {

class GpLogMarkTS
{
public:
    CLASS_DD(GpLogMarkTS)

public:
    using SourceLocationOptT = std::optional<SourceLocationT>;

public:
    inline                      GpLogMarkTS     (void) noexcept;
    inline                      GpLogMarkTS     (const GpLogMarkTS& aTag);
    inline                      GpLogMarkTS     (GpLogMarkTS&& aTag) noexcept;
    inline                      GpLogMarkTS     (std::string            aComment,
                                                 const SourceLocationT& aSourceLocation) noexcept;
                                ~GpLogMarkTS    (void) noexcept = default;

    unix_ts_ms_t                UnixTS          (void) const noexcept {return iUnixTS;}
    microseconds_t              HiResTS         (void) const noexcept {return iHiResTS;}
    microseconds_t              SteadyTS        (void) const noexcept {return iSteadyTS;}
    std::string_view            Comment         (void) const noexcept {return iComment;}
    const SourceLocationOptT&   SourceLocation  (void) const noexcept {return iSourceLocation;}

private:
    unix_ts_ms_t                iUnixTS;
    microseconds_t              iHiResTS;
    microseconds_t              iSteadyTS;
    std::string                 iComment;
    SourceLocationOptT          iSourceLocation;
};

GpLogMarkTS::GpLogMarkTS (void) noexcept
{
}

GpLogMarkTS::GpLogMarkTS (const GpLogMarkTS& aTag):
iUnixTS        {aTag.iUnixTS},
iHiResTS       {aTag.iHiResTS},
iSteadyTS      {aTag.iSteadyTS},
iComment       {aTag.iComment},
iSourceLocation{aTag.iSourceLocation}
{
}

GpLogMarkTS::GpLogMarkTS (GpLogMarkTS&& aTag) noexcept:
iUnixTS        {std::move(aTag.iUnixTS)},
iHiResTS       {std::move(aTag.iHiResTS)},
iSteadyTS      {std::move(aTag.iSteadyTS)},
iComment       {std::move(aTag.iComment)},
iSourceLocation{std::move(aTag.iSourceLocation)}
{
}

GpLogMarkTS::GpLogMarkTS
(
    std::string             aComment,
    const SourceLocationT&  aSourceLocation
) noexcept:
iUnixTS        {GpDateTimeOps::SUnixTS_ms()},
iHiResTS       {GpDateTimeOps::SHighResTS_us()},
iSteadyTS      {GpDateTimeOps::SSteadyTS_us() - GpDateTimeOps::SSteadyTS_us_AtAppStart()},
iComment       {std::move(aComment)},
iSourceLocation{aSourceLocation}
{
}

}// namespace GPlatform

// --------------------------------------------------------------------

namespace FMT_NAMESPASE {

using namespace GPlatform;

template<>
struct formatter<GpLogMarkTS>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& aCtx)
    {
        return std::begin(aCtx);
    }

    template<typename FormatContext>
    auto format(const GpLogMarkTS& aMark, FormatContext& aCtx) const
    {
        iTsId++;

        // Delta
        microseconds_t  delta       = 0.0_si_us;
        microseconds_t  nowHiResTs  = aMark.HiResTS();

        if (iTsId > 1) [[likely]]
        {
            delta = nowHiResTs - iPrevHiResTs;
        }

        iPrevHiResTs     = nowHiResTs;
        iDuration       += delta;

        const auto& sourceLocationOpt = aMark.SourceLocation();

        return ::fmt::format_to
        (
            aCtx.out(),
            "   \033[1m[{}]\033[0m(TS: {}: STS: {:.6f}s(Δ{:.6f}s, Σ{:.6f}s): \033[1m{}\033[0m\n      {}",
            iTsId,
            aMark.UnixTS(),
            aMark.SteadyTS().As<seconds_t>().Value(),
            delta.As<seconds_t>().Value(),
            iDuration.As<seconds_t>().Value(),
            aMark.Comment(),
            sourceLocationOpt
        );
    }

private:
    mutable size_t          iTsId           = 0;
    mutable microseconds_t  iPrevHiResTs    = 0.0_si_us;
    mutable microseconds_t  iDuration       = 0.0_si_us;
};

}// namespace FMT_NAMESPASE

#endif// #if defined(GP_USE_TIMERS)
