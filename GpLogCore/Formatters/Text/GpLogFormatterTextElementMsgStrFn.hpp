#pragma once

#include "../../Elements/GpLogElementMsgStrFn.hpp"

namespace GPlatform {

/*class GpLogFormatterTextElementMsgStrFn
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogFormatterTextElementMsgStrFn)
	CLASS_DECLARE_DEFAULTS(GpLogFormatterTextElementMsgStrFn)

public:
						GpLogFormatterTextElementMsgStrFn	(void) noexcept = default;
	virtual				~GpLogFormatterTextElementMsgStrFn	(void) noexcept = default;

	inline void			Serialize							(const GpLogElementMsg&	aMessage,
															 GpByteWriter&			aWriter) const;
};

void	GpLogFormatterTextElementMsgStrFn::Serialize
(
	const GpLogElementMsg&	aMessage,
	GpByteWriter&			aWriter
) const
{
	const GpLogElementMsgStrFn& e = static_cast<const GpLogElementMsgStrFn&>(aMessage);

	const std::string s = e.Message();
	aWriter.Bytes(s);
}*/

}//namespace GPlatform
