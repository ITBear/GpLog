#pragma once

#include "GpLogCore_global.hpp"

#if defined(GP_USE_TIMERS)

#include "GpLogMarkTS.hpp"

namespace GPlatform {

class GpLogMarkTraceTS
{
public:
    CLASS_DD(GpLogMarkTraceTS)

public:
    inline                          GpLogMarkTraceTS    (void) noexcept;
    inline                          GpLogMarkTraceTS    (const GpLogMarkTraceTS& aTrace);
    inline                          GpLogMarkTraceTS    (GpLogMarkTraceTS&& aTrace) noexcept;
    inline                          ~GpLogMarkTraceTS   (void) noexcept;

    inline void                     Mark                (std::u8string          aComment,
                                                         const SourceLocationT& aSourceLocation = SourceLocationT::current());
    inline void                     Mark                (std::u8string_view     aComment,
                                                         const SourceLocationT& aSourceLocation = SourceLocationT::current());

    const GpLogMarkTS::C::Vec::Val& Marks               (void) const noexcept {return iMarks;}

private:
    GpLogMarkTS::C::Vec::Val        iMarks;
};

GpLogMarkTraceTS::GpLogMarkTraceTS (void) noexcept
{
}

GpLogMarkTraceTS::GpLogMarkTraceTS (const GpLogMarkTraceTS& aTrace):
iMarks(aTrace.iMarks)
{
}

GpLogMarkTraceTS::GpLogMarkTraceTS (GpLogMarkTraceTS&& aTrace) noexcept:
iMarks(std::move(aTrace.iMarks))
{
}

GpLogMarkTraceTS::~GpLogMarkTraceTS (void) noexcept
{
}

void    GpLogMarkTraceTS::Mark
(
    std::u8string           aComment,
    const SourceLocationT&  aSourceLocation
)
{
    iMarks.emplace_back(GpLogMarkTS{std::move(aComment), aSourceLocation});
}

void    GpLogMarkTraceTS::Mark
(
    std::u8string_view      aComment,
    const SourceLocationT&  aSourceLocation
)
{
    iMarks.emplace_back(GpLogMarkTS{std::u8string(aComment), aSourceLocation});
}

}//namespace GPlatform

#endif//#if defined(GP_USE_TIMERS)
