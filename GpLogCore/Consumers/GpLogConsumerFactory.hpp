#pragma once

#include "GpLogConsumer.hpp"

namespace GPlatform {

class GpLogConsumerFactory
{
public:
	CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumerFactory)
	CLASS_DECLARE_DEFAULTS(GpLogConsumerFactory)

protected:
								GpLogConsumerFactory	(GpByteSerializer::SP aFormatter) noexcept: iFormatter(std::move(aFormatter)) {}

public:
	virtual						~GpLogConsumerFactory	(void) noexcept = default;

	virtual GpLogConsumer::SP	NewInstance				(void) const = 0;

protected:
	GpByteSerializer::SP		Formatter				(void) const {return iFormatter;}

private:
	GpByteSerializer::SP		iFormatter;
};

}//namespace GPlatform
