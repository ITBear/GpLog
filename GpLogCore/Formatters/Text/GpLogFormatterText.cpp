#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterText.hpp>
#include <GpLog/GpLogCore/GpLogChain.hpp>
#include <GpLog/GpLogCore/Elements/GpLogElementMsg.hpp>
#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterTextElementMsgStr.hpp>
#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterTextElementMsgMarkTraceTS.hpp>

#include <sstream>

namespace GPlatform {

const std::array<std::string, GpLogLevel::SCount()> GpLogFormatterText::sLevels =
{
    std::string("\033[1m[D]\033[0m"_sv),
    std::string("\033[1m[I]\033[0m"_sv),
    std::string("\033[1m[W]\033[0m"_sv),
    std::string("\033[1m[E]\033[0m"_sv),
    std::string("\033[1m[!]\033[0m"_sv)
};

GpLogFormatterText::GpLogFormatterText (void) noexcept
{
}

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
    const std::string   chainIdStr      = chainId.ToString();
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

        std::string msg = GenMessage(element.Message());
        if (msg.find_first_of('\n') == std::string::npos)
        {
            aWriter
                .Bytes(": "_sv)
                .Bytes(msg);
        } else
        {
            aWriter
                .Bytes(":\n[VVV=========================================================================VVV]:\n"_sv)
                .Bytes(msg)
                .Bytes("\n[^^^=========================================================================^^^]"_sv);
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

std::string GpLogFormatterText::GenMessage (const GpLogElementMsg& aMessage) const
{
    const GpLogElementMsg::TypeT t = aMessage.Type();

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
            THROW_GP("Unknown log element with type id "_sv + int(t));
        }
    }
}

}// namespace GPlatform
