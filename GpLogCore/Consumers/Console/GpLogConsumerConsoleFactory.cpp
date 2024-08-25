#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsoleFactory.hpp>
#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsole.hpp>

namespace GPlatform {

GpLogConsumerConsoleFactory::GpLogConsumerConsoleFactory (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumerFactory{std::move(aFormatter)}
{
}

GpLogConsumerConsoleFactory::GpLogConsumerConsoleFactory
(
    GpByteSerializer::SP                    aFormatter,
    const GpLogConsumerConsoleConfigDesc&   aConfigDesc
):
GpLogConsumerFactory{std::move(aFormatter)},
iConfigDesc{MakeSP<GpLogConsumerConsoleConfigDesc>(aConfigDesc)}
{
}

GpLogConsumer::SP   GpLogConsumerConsoleFactory::NewInstance (void) const
{
    return MakeSP<GpLogConsumerConsole>(Formatter());
}

}// namespace GPlatform
