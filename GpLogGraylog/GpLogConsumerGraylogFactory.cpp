#include <GpLog/GpLogGraylog/GpLogConsumerGraylogFactory.hpp>
#include <GpLog/GpLogGraylog/GpLogConsumerGraylog.hpp>

namespace GPlatform {

GpLogConsumerGraylogFactory::~GpLogConsumerGraylogFactory (void) noexcept
{
}

GpLogConsumer::SP   GpLogConsumerGraylogFactory::NewInstance (void) const
{
    //const GpLogConsumerGraylogConfigDesc& configDesc = iConfigDesc.V();

    return MakeSP<GpLogConsumerGraylog>
    (
        Formatter()
    );
}

}// namespace GPlatform
