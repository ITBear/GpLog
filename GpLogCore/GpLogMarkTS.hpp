#pragma once

#include "GpLogCore_global.hpp"

#if defined(GP_USE_TIMERS)

namespace GPlatform {

class GpLogMarkTS
{
public:
	CLASS_DECLARE_DEFAULTS(GpLogMarkTS)

public:
	using SourceLocationOptT = std::optional<SourceLocationT>;

public:
	inline						GpLogMarkTS		(void) noexcept;
	inline						GpLogMarkTS		(const GpLogMarkTS& aTag);
	inline						GpLogMarkTS		(GpLogMarkTS&& aTag) noexcept;
	inline						GpLogMarkTS		(std::string			aComment,
												 const SourceLocationT&	aSourceLocation) noexcept;
								~GpLogMarkTS	(void) noexcept = default;

	microseconds_t				HiResTS			(void) const noexcept {return iHiResTS;}
	microseconds_t				SteadyTS		(void) const noexcept {return iSteadyTS;}
	std::string_view			Comment			(void) const noexcept {return iComment;}
	const SourceLocationOptT&	SourceLocation	(void) const noexcept {return iSourceLocation;}

private:
	microseconds_t				iHiResTS;
	microseconds_t				iSteadyTS;
	std::string					iComment;
	SourceLocationOptT			iSourceLocation;
};

GpLogMarkTS::GpLogMarkTS (void) noexcept
{
}

GpLogMarkTS::GpLogMarkTS (const GpLogMarkTS& aTag):
iHiResTS(aTag.iHiResTS),
iSteadyTS(aTag.iSteadyTS),
iComment(aTag.iComment),
iSourceLocation(aTag.iSourceLocation)
{
}

GpLogMarkTS::GpLogMarkTS (GpLogMarkTS&& aTag) noexcept:
iHiResTS(std::move(aTag.iHiResTS)),
iSteadyTS(std::move(aTag.iSteadyTS)),
iComment(std::move(aTag.iComment)),
iSourceLocation(std::move(aTag.iSourceLocation))
{
}

GpLogMarkTS::GpLogMarkTS
(
	std::string				aComment,
	const SourceLocationT&	aSourceLocation
) noexcept:
iHiResTS(GpDateTimeOps::SHighResTS_us()),
iSteadyTS(GpDateTimeOps::SSteadyTS_us() - GpDateTimeOps::SSteadyTS_us_AtAppStart()),
iComment(std::move(aComment)),
iSourceLocation(aSourceLocation)
{
}

}//namespace GPlatform

#endif//#if defined(GP_USE_TIMERS)
