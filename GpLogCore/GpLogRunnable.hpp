#pragma once

#include "GpLogQueue.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogRunnable final: public GpRunnable
{
public:
	CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogRunnable)
	CLASS_DECLARE_DEFAULTS(GpLogRunnable)

public:
	inline								GpLogRunnable		(const GpLogConsumerFactory::C::Vec::SP	aConsumerFactories,
															 const seconds_t						aFlushPeriod,
															 GpLogQueue&							aLogQueue);
	virtual								~GpLogRunnable		(void) noexcept override final;

	virtual void						Run					(GpThreadStopToken aStopToken) noexcept override final;

private:
	void								Consume				(GpLogConsumer::C::Vec::SP& aConsumers,
															 GpDoOnceInPeriod&			aFlushOnceInPeriod);
	void								ConsumeNotEnded		(GpLogConsumer::C::Vec::SP& aConsumers);
	void								Flush				(GpLogConsumer::C::Vec::SP& aConsumers);
	GpLogConsumer::C::Vec::SP			CreateConsumers		(void);

private:
	GpLogConsumerFactory::C::Vec::SP	iConsumerFactories;
	const seconds_t						iFlushPeriod;
	GpLogQueue&							iLogQueue;
};

GpLogRunnable::GpLogRunnable
(
	const GpLogConsumerFactory::C::Vec::SP	aConsumerFactories,
	const seconds_t							aFlushPeriod,
	GpLogQueue&								aLogQueue
):
GpRunnable(MakeSP<GpConditionVar>()),
iConsumerFactories(std::move(aConsumerFactories)),
iFlushPeriod(aFlushPeriod),
iLogQueue(aLogQueue)
{
}

}//namespace GPlatform
