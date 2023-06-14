#include "GpLogFormatterText.hpp"
#include "../../GpLogChain.hpp"
#include "../../Elements/GpLogElementMsg.hpp"
#include "GpLogFormatterTextElementMsgStr.hpp"
#include "GpLogFormatterTextElementMsgStrFn.hpp"
#include "GpLogFormatterTextElementMsgMarkTraceTS.hpp"
#include <sstream>

namespace GPlatform {

const std::array<std::u8string, GpLogLevel::SCount()>   GpLogFormatterText::sLevels =
{
    std::u8string(u8"[D]"_sv),
    std::u8string(u8"[I]"_sv),
    std::u8string(u8"[W]"_sv),
    std::u8string(u8"[E]"_sv),
    std::u8string(u8"[!]"_sv)
};

GpLogFormatterText::~GpLogFormatterText (void) noexcept
{
}

void    GpLogFormatterText::Serialize
(
    const GpAny&    aObject,
    GpByteWriter&   aWriter
) const
{
    const GpLogChain&                   logChain        = aObject.Value<const std::reference_wrapper<const GpLogChain>>().get();
    const GpLogElement::C::List::Val&   chainElements   = logChain.Elements();

    const GpUUID        chainId         = logChain.ChainId();
    const std::u8string chainIdStr      = chainId.ToString();
    const bool          chainNotEmpty   = chainId.IsNotZero();

    if (chainNotEmpty)
    {
        aWriter
            .Bytes("\n==vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv [ Chain begin: "_sv)
            .Bytes(chainIdStr)
            .Bytes(" ] vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv=="_sv);
    }

    for (const GpLogElement& element: chainElements)
    {
        aWriter.Bytes("\n"_sv);
        WriteLevel(element.Level(), aWriter);
        WriteUnixTS(element.UnixTS(), aWriter);
        WriteSteadyTS(element.SteadyTS(), aWriter);

        std::u8string msg = GenMessage(element.Message());
        if (msg.find_first_of('\n') == std::u8string::npos)
        {
            aWriter
                .Bytes(": "_sv)
                .Bytes(msg);
        } else
        {
            aWriter
                .Bytes(":\n"_sv)
                .Bytes(msg);
        }
    }

    if (chainNotEmpty)
    {
        aWriter
            .Bytes("\n==^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [ Chain end:   "_sv)
            .Bytes(chainIdStr)
            .Bytes(" ] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^=="_sv);
    }
}

void    GpLogFormatterText::WriteLevel
(
    const GpLogLevel::EnumT aLevel,
    GpByteWriter&           aWriter
) const
{
    aWriter
        .Bytes(GpLogFormatterText::sLevels.at(static_cast<size_t>(aLevel)));
}

void    GpLogFormatterText::WriteUnixTS
(
    const unix_ts_ms_t  aUnixTS,
    GpByteWriter&       aWriter
) const
{
    const std::u8string str = GpDateTimeOps::SUnixTsToStr(aUnixTS, GpDateTimeFormat::STD_DATE_TIME);

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
    const std::u8string str = StrOps::SFromDouble(aSteadyTS.As<seconds_t>().Value());

    aWriter
        .Bytes(", STS: "_sv)
        .Bytes(str)
        .Bytes("s)"_sv);
}

std::u8string   GpLogFormatterText::GenMessage (const GpLogElementMsg& aMessage) const
{
    const auto t = aMessage.Type();

    switch (t)
    {
        case GpLogElementMsg::TypeT::STR:
        {
            return GpLogFormatterTextElementMsgStr::SGen(aMessage);
        } break;
        case GpLogElementMsg::TypeT::TRACE_TS:
        {
            return GpLogFormatterTextElementMsgMarkTraceTS::SGen(aMessage);
        } break;
        default:
        {
            THROW_GP(u8"Unknown log element with type id "_sv + int(t));
        }
    }
}

}//namespace GPlatform
