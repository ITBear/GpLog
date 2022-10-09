#include "GpLogConsumerGraylog.hpp"

#include <iostream>

namespace GPlatform {

GpLogConsumerGraylog::GpLogConsumerGraylog (GpByteSerializer::SP aFormatter) noexcept:
GpLogConsumer(std::move(aFormatter))
{
}

GpLogConsumerGraylog::~GpLogConsumerGraylog (void) noexcept
{
}

void    GpLogConsumerGraylog::Consume (GpLogChain::CSP aLogChain)
{
    //TODO: implement
    THROW_GP_NOT_IMPLEMENTED();
/*
    const GpLogChain& logChain = aLogChain.V();

    iTmpBuffer.resize(4096);
    GpByteWriterStorageByteArray    dataStorage(iTmpBuffer);
    GpByteWriter                    dataWriter(dataStorage);

    Formatter().Serialize
    (
        std::make_any<std::reference_wrapper<const GpLogChain>>(logChain),
        dataWriter
    );

    dataWriter.ShrinkToFit();

    std::cout << GpSpanPtrByteR(iTmpBuffer).AsStringView();
    std::cout.flush();*/
}

void    GpLogConsumerGraylog::OnFlush (void) noexcept
{
    std::cout.flush();
}

}//namespace GPlatform
