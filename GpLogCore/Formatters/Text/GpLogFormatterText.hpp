#pragma once

#include "../../GpLogLevel.hpp"

namespace GPlatform {

class GpLogElementMsg;

class GP_LOG_CORE_API GpLogFormatterText final: public GpByteSerializer
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogFormatterText)
	CLASS_DECLARE_DEFAULTS(GpLogFormatterText)

public:
							GpLogFormatterText	(void) noexcept = default;
	virtual					~GpLogFormatterText	(void) noexcept override final;

	virtual void			Serialize			(const std::any&	aObject,
												 GpByteWriter&		aWriter) const override final;

private:
	void					WriteLevel			(const GpLogLevel::EnumT	aLevel,
												 GpByteWriter&				aWriter) const;
	void					WriteUnixTS			(const unix_ts_ms_t			aUnixTS,
												 GpByteWriter&				aWriter) const;
	void					WriteSteadyTS		(const microseconds_t		aSteadyTS,
												 GpByteWriter&				aWriter) const;
	std::string				GenMessage			(const GpLogElementMsg&		aMessage) const;

private:
	static const GpArray<std::string, GpLogLevel::SCount()>	sLevels;
};

}//namespace GPlatform
