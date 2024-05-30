#pragma once

#include "../GpLogConsumer.hpp"

#include <GpCore2/GpUtils/Types/Units/Other/size_byte_t.hpp>
#include <fstream>

namespace GPlatform {

class GpLogConsumerFile final: public GpLogConsumer
{
    static_assert(sizeof(std::ofstream::char_type) == 1);

public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumerFile)
    CLASS_DD(GpLogConsumerFile)

public:
                                GpLogConsumerFile   (std::string_view       aOutFilePath,
                                                     std::string_view       aOutFilePrefix,
                                                     size_byte_t            aFileMaxSize,
                                                     milliseconds_t         aMaxFlushPeriod,
                                                     size_byte_t            aMaxBufferSize,
                                                     GpByteSerializer::SP   aFormatter);
    virtual                     ~GpLogConsumerFile  (void) noexcept override final;

    virtual void                Consume             (GpLogChain::CSP aLogChain) override final;
    virtual void                OnFlush             (void) noexcept override final;

private:
    void                        WriteToFile         (void);
    std::ofstream               CreateFile          (std::string_view aFilePath,
                                                     std::string_view aFilePrefix);
    std::string                 GenFullFileName     (std::string_view   aFilePath,
                                                     std::string_view   aFilePrefix,
                                                     size_t             aPostfix);

private:
    const std::string           iOutFilePath;
    const std::string           iOutFilePrefix;
    const size_byte_t           iFileMaxSize;
    const milliseconds_t        iMaxFlushPeriod;
    const size_byte_t           iMaxBufferSize;

    GpBytesArray                iBufferData;
    milliseconds_t              iSteadyLastFlushTS = 0.0_si_ms;

    std::string                 iOFStreamFileName;
    std::ofstream               iOFStream;
    size_byte_t                 iBytesWriteToStream;
    std::array<std::byte, 8192> iBufferStream;
};

}// namespace GPlatform
