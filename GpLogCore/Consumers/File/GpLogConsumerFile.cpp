#include "GpLogConsumerFile.hpp"

#include <GpCore2/GpUtils/Streams/GpByteWriterStorageByteArray.hpp>
#include <filesystem>

namespace GPlatform {

GpLogConsumerFile::GpLogConsumerFile
(
    std::u8string_view      aOutFilePath,
    std::u8string_view      aOutFilePrefix,
    const size_byte_t       aFileMaxSize,
    const milliseconds_t    aMaxFlushPeriod,
    const size_byte_t       aMaxBufferSize,
    GpByteSerializer::SP    aFormatter
):
GpLogConsumer(std::move(aFormatter)),
iOutFilePath(aOutFilePath),
iOutFilePrefix(aOutFilePrefix),
iFileMaxSize(aFileMaxSize),
iMaxFlushPeriod(aMaxFlushPeriod),
iMaxBufferSize(aMaxBufferSize)
{
}

GpLogConsumerFile::~GpLogConsumerFile (void) noexcept
{
}

void    GpLogConsumerFile::Consume (GpLogChain::CSP aLogChain)
{
    const GpLogChain& logChain = aLogChain.V();

    //TODO: rewrite iBufferData with GpByteWriter.TotalWrite()

    GpByteWriterStorageByteArray    dataStorage(iBufferData);
    dataStorage.OffsetToEnd();
    GpByteWriter                    dataWriter(dataStorage);

    Formatter().Serialize(GpAny{std::reference_wrapper<const GpLogChain>(logChain)}, dataWriter);

    dataWriter.OnEnd();

    const milliseconds_t nowSteadyTS = GpDateTimeOps::SSteadyTS_ms();

    if (   (iBufferData.size() > iMaxBufferSize.As<size_t>())
        || ((nowSteadyTS - iSteadyLastFlushTS) >= iMaxFlushPeriod))
    {
        iSteadyLastFlushTS = nowSteadyTS;
        WriteToFile();
    }
}

void    GpLogConsumerFile::OnFlush (void) noexcept
{
    iSteadyLastFlushTS = GpDateTimeOps::SSteadyTS_ms();

    WriteToFile();

    if (iOFStream)
    {
        iOFStream.flush();
    }
}

void    GpLogConsumerFile::WriteToFile (void)
{
    if (   (!iOFStream.is_open())
        || (iBytesWriteToStream >= iFileMaxSize))
    {
        iOFStream = CreateFile(iOutFilePath, iOutFilePrefix);
    }

    iOFStream.write
    (
        reinterpret_cast<const std::ofstream::char_type*>(iBufferData.data()),
        NumOps::SConvert<std::streamsize>(iBufferData.size())
    );

    if (iOFStream.fail())
    {
        iOFStream.clear();
        THROW_GP(u8"Failed to write to file '"_sv + iOFStreamFileName + u8"'"_sv);
    }

    iBytesWriteToStream += size_byte_t::SMake(iBufferData.size());
    iBufferData.clear();
}

std::ofstream   GpLogConsumerFile::CreateFile
(
    std::u8string_view aFilePath,
    std::u8string_view aFilePrefix
)
{
    if (iOFStream.is_open())
    {
        iOFStream.flush();
        iOFStream.close();
    }

    iBytesWriteToStream = 0_byte;

    size_t sameNameFileCount    = 0;
    iOFStreamFileName           = GenFullFileName(aFilePath, aFilePrefix, sameNameFileCount);
    while (std::filesystem::exists(iOFStreamFileName))
    {
        sameNameFileCount++;
        iOFStreamFileName = GenFullFileName(aFilePath, aFilePrefix, sameNameFileCount);
    }

    std::ofstream oftream;
    oftream.open(std::filesystem::path(iOFStreamFileName), std::ios::out | std::ios::binary);

    if (oftream.fail())
    {
        iOFStream.clear();
        THROW_GP(u8"Failed to create file '"_sv + iOFStreamFileName + u8"'"_sv);
    }

    oftream.rdbuf()->pubsetbuf
    (
        reinterpret_cast<std::ofstream::char_type*>(iBufferStream.data()),
        NumOps::SConvert<std::streamsize>(iBufferStream.size())
    );

    return oftream;
}

std::u8string   GpLogConsumerFile::GenFullFileName
(
    std::u8string_view  aFilePath,
    std::u8string_view  aFilePrefix,
    const size_t        aPostfix
)
{
    std::u8string dateTimeStr = GpDateTimeOps::SUnixTsToStr(GpDateTimeOps::SUnixTS_s(), GpDateTimeFormat::STD_DATE_TIME_T);
    std::replace(dateTimeStr.begin(), dateTimeStr.end(), '-', '_');

    std::u8string fileName;
    fileName.reserve(128);
    fileName
        .append(aFilePrefix)
        .append(u8"_"_sv)
        .append(dateTimeStr)
        .append(u8".log."_sv)
        .append(StrOps::SFromUI64(aPostfix));

    std::filesystem::path path(aFilePath);
    path /= fileName;

    return path.u8string();
}

}//namespace GPlatform
