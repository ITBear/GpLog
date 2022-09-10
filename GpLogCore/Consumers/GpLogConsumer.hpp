#pragma once

#include "../GpLogChain.hpp"

namespace GPlatform {

class GpLogConsumer
{
public:
	CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumer)
	CLASS_DECLARE_DEFAULTS(GpLogConsumer)

protected:
	inline					GpLogConsumer	(GpByteSerializer::SP aFormatter) noexcept;

public:
	inline virtual			~GpLogConsumer	(void) noexcept = default;

	virtual void			Consume			(GpLogChain::CSP aLogChain) = 0;
	virtual void			OnFlush			(void) noexcept = 0;

protected:
	const GpByteSerializer&	Formatter		(void) const noexcept {return iFormatter.Vn();}

private:
	GpByteSerializer::SP	iFormatter;
};

GpLogConsumer::GpLogConsumer (GpByteSerializer::SP aFormatter) noexcept:
iFormatter(std::move(aFormatter))
{
}

}//namespace GPlatform
