#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsole.hpp>
#include <GpCore2/GpUtils/Streams/GpByteWriterStorageByteArray.hpp>
#include <iostream>

namespace GPlatform {

GpLogConsumerConsole::GpLogConsumerConsole (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumer{std::move(aFormatter)}
{
}

GpLogConsumerConsole::~GpLogConsumerConsole (void) noexcept
{
}

void    GpLogConsumerConsole::Consume (GpLogChain::CSP aLogChain)
{
    const GpLogChain& logChain = aLogChain.V();

    iTmpBuffer.resize(4096);
    GpByteWriterStorageByteArray    dataStorage(iTmpBuffer);
    GpByteWriter                    dataWriter(dataStorage);

    Formatter().Serialize
    (
        GpAny{std::reference_wrapper<const GpLogChain>(logChain)},
        dataWriter
    );

    dataWriter.OnEnd();

    std::string_view sv = GpSpanByteR(std::data(iTmpBuffer), std::size(iTmpBuffer)).AsStringView();

    std::cout << sv;
    std::cout.flush();
}

void    GpLogConsumerConsole::OnFlush (void) noexcept
{
    std::cout.flush();
}

}// namespace GPlatform
