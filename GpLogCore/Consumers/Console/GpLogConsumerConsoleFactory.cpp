#include "GpLogConsumerConsoleFactory.hpp"
#include "GpLogConsumerConsole.hpp"

namespace GPlatform {

GpLogConsumer::SP   GpLogConsumerConsoleFactory::NewInstance (void) const
{
    return MakeSP<GpLogConsumerConsole>(Formatter());
}

}// namespace GPlatform
