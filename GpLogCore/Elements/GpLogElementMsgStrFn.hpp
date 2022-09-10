#pragma once

#include "GpLogElementMsg.hpp"

namespace GPlatform {

/*class GP_LOG_CORE_API GpLogElementMsgStrFn final: public GpLogElementMsg
{
public:
	CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogElementMsgStrFn)
	CLASS_DECLARE_DEFAULTS(GpLogElementMsgStrFn)

	using MsgGenT = std::function<std::string()>;

public:
	inline						GpLogElementMsgStrFn	(MsgGenT aMessageFn);
	virtual						~GpLogElementMsgStrFn	(void) noexcept override final;

	std::string					Message					(void) const {return iMessageFn();}

private:
	MsgGenT						iMessageFn;
};

GpLogElementMsgStrFn::GpLogElementMsgStrFn (MsgGenT aMessageFn):
GpLogElementMsg(TypeT::STR_FN),
iMessageFn(std::move(aMessageFn))
{
}*/

}//namespace GPlatform
