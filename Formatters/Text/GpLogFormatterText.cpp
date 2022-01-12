#include "GpLogFormatterText.hpp"
#include "../../GpLogChain.hpp"
#include "../../Elements/GpLogElementMsg.hpp"
#include <sstream>

namespace GPlatform {

const GpArray<std::string, GpLogLevel::SCount().As<size_t>()>   GpLogFormatterText::sLevels =
{
    std::string("[D]"_sv),
    std::string("[I]"_sv),
    std::string("[W]"_sv),
    std::string("[E]"_sv),
    std::string("[!]"_sv)
};


GpLogFormatterText::GpLogFormatterText
(
    const GpLogFormatterTextConfigDesc& aConfigDesc,
    const GpLogElementFormatter&        aElementFormatter
):
iConfigDesc(aConfigDesc),
iElementFormatter(aElementFormatter)
{
}

GpLogFormatterText::~GpLogFormatterText (void) noexcept
{
}

void    GpLogFormatterText::Format
(
    const std::any& aObject,
    GpByteWriter&   aWriter
) const
{
    const GpLogChain&                   logChain        = std::any_cast<std::reference_wrapper<const GpLogChain>>(aObject).get();
    const GpLogElement::C::Vec::Val&    chainElements   = logChain.Elements();

    const GpUUID        chainId         = logChain.ChainId();
    const std::string   chainIdStr      = chainId.ToString();
    const bool          chainNotEmpty   = chainId.IsNotZero();

    if (chainNotEmpty)
    {
        aWriter
            .Bytes("==vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv[ Chain begin: "_sv)
            .Bytes(chainIdStr)
            .Bytes(" ]vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv==\n"_sv);
    }

    for (const GpLogElement& element: chainElements)
    {
        WriteLevel(element.Level(), aWriter);
        WriteUnixTS(element.UnixTS(), aWriter);
        WriteSteadyTS(element.SteadyTS(), aWriter);
        WriteThreadId(element.ThreadId(), aWriter);
        WriteTaskName(element.TaskName(), aWriter);
        WriteCategory(element.Category(), aWriter);
        WriteMessage(element.Message(), aWriter);

        aWriter.
            Bytes("\n"_sv);
    }

    if (chainNotEmpty)
    {
        aWriter
            .Bytes("==^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ Chain end: "_sv)
            .Bytes(chainIdStr)
            .Bytes(" ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^==\n"_sv);
    }
}

void    GpLogFormatterText::WriteLevel
(
    const GpLogLevel::EnumT aLevel,
    GpByteWriter&           aWriter
) const
{
    aWriter
        .Bytes(GpLogFormatterText::sLevels.at(int(aLevel)));
}

void    GpLogFormatterText::WriteThreadId
(
    const std::thread::id&  aThreadId,
    GpByteWriter&           aWriter
) const
{
    std::ostringstream s;
    s << aThreadId;

    aWriter
        .Bytes(" ThreadID: "_sv)
        .Bytes(s.str());
}

void    GpLogFormatterText::WriteTaskName
(
    std::string_view    aTaskName,
    GpByteWriter&       aWriter
) const
{
    aWriter
        .Bytes(", task: '"_sv)
        .Bytes(aTaskName)
        .Bytes("'"_sv);
}

void    GpLogFormatterText::WriteCategory
(
    std::string_view    aCategory,
    GpByteWriter&       aWriter
) const
{
    aWriter
        .Bytes(", category: '"_sv)
        .Bytes(aCategory)
        .Bytes("'"_sv);
}

void    GpLogFormatterText::WriteUnixTS
(
    const unix_ts_ms_t  aUnixTS,
    GpByteWriter&       aWriter
) const
{
    const std::string str = GpDateTimeOps::SUnixTsToStr(aUnixTS, GpDateTimeFormat::STD_DATE_TIME);

    aWriter
        .Bytes("(TS: "_sv)
        .Bytes(str);
}

void    GpLogFormatterText::WriteSteadyTS
(
    const microseconds_t    aSteadyTS,
    GpByteWriter&           aWriter
) const
{
    const std::string str = StrOps::SFromDouble(aSteadyTS.As<seconds_t>().Value());

    aWriter
        .Bytes(", STS: "_sv)
        .Bytes(str)
        .Bytes("s)"_sv);
}

void    GpLogFormatterText::WriteMessage
(
    const GpLogElementMsg&  aMessage,
    GpByteWriter&           aWriter
) const
{
    aWriter.Bytes("\n"_sv);

    iElementFormatter.Find(typeid(aMessage)).Format
    (
        std::make_any<std::reference_wrapper<const GpLogElementMsg>>(aMessage),
        aWriter
    );
}

}//namespace GPlatform
