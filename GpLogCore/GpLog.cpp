#include <GpCore2/Config/IncludeExt/fmt.hpp>
#include <GpLog/GpLogCore/GpLog.hpp>

#include <GpLog/GpLogCore/Consumers/Console/GpLogConsumerConsoleFactory.hpp>
#include <GpLog/GpLogCore/Formatters/Text/GpLogFormatterText.hpp>

#include <GpCore2/GpUtils/Types/Strings/GpStringUtils.hpp>
#include <GpCore2/GpUtils/Exceptions/GpExceptionUtils.hpp>
#include <GpCore2/GpUtils/Other/GpSystemInfo.hpp>
#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>
#include <GpCore2/GpUtils/Threads/GpSleepStrategy.hpp>

namespace GPlatform {

GpLog::SP           GpLog::sInstance;
GpLogLevel::EnumT   GpLog::sLevel = GpLogLevel::L_INFO;

GpLog::GpLog (void) noexcept:
iLogExecutor{iLogQueue}
{
}

GpLog::~GpLog (void) noexcept
{
}

void    GpLog::SInit (void)
{
    GpLog::sInstance = MakeSP<GpLog>();
}

void    GpLog::SClear (void)
{
    GpLog::sInstance.Clear();
}

void    GpLog::StartDefault (void)
{
    GpLogConsumerFactory::C::Vec::SP consumerFactories;

    consumerFactories.emplace_back
    (
        MakeSP<GpLogConsumerConsoleFactory>
        (
            MakeSP<GpLogFormatterText>()
        )
    );

    Start
    (
        consumerFactories,
        GpLogLevel::L_DEBUG,
        1.0_si_s
    );
}

void    GpLog::StartFromConfig
(
    const GpLogConfigDesc&          aConfigDesc,
    const GpLogLevel::EnumT         aExtLevelValue,
    const GpLogConsumersFactory&    aConsumersFactory
)
{
    //Formatter
    GpByteSerializer::SP formatter = MakeSP<GpLogFormatterText>();

    //Consumers
    GpLogConsumerFactory::C::Vec::SP consumerFactories;

    for (auto&[name, cfg]: aConfigDesc.consumers)
    {
        consumerFactories.emplace_back
        (
            aConsumersFactory.FactoryFromCfg
            (
                name,
                cfg.V(),
                formatter
            )
        );
    }

    Start
    (
        std::move(consumerFactories),
        std::min(aConfigDesc.level.Value(), aExtLevelValue),
        aConfigDesc.flush_period
    );
}

void    GpLog::Start
(
    const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories,
    const GpLogLevel::EnumT                 aLevel,
    const seconds_t                         aFlushPeriod
)
{
    SSetLevel(aLevel);

    iLogExecutor.Start
    (
        aConsumerFactories,
        aFlushPeriod
    );
}

void    GpLog::Stop (void)
{
    iLogExecutor.RequestStop();
    iLogExecutor.Join();

    // Check if message queue is not empty
    if (!iLogQueue.Empty())
    {
        StartDefault();

        // Wait for empty queue
        constexpr std::array<std::pair<size_t, std::chrono::milliseconds>, 2> tryStages =
        {
            std::pair<size_t, std::chrono::milliseconds>{size_t{10000}, std::chrono::milliseconds(0)},
            std::pair<size_t, std::chrono::milliseconds>{size_t{100}, std::chrono::milliseconds(1)}
        };

        GpSleepStrategy::SWaitFor
        (
            [&]()-> bool
            {
                return iLogQueue.Empty();
            },
            tryStages,
            std::chrono::milliseconds(10)
        );
    }

    iLogExecutor.RequestStop();
    iLogExecutor.Join();
}

void    GpLog::Flush (void)
{
    iLogExecutor.Flush();
}

void    GpLog::Logout
(
    GpLogElementMsg::CSP    aMessage,
    const GpLogLevel::EnumT aLevel,
    const GpLogMode::EnumT  aMode,
    const GpUUID&           aChainId,
    const SourceLocationT&  /*aSourceLocation*/
)
{
    if (static_cast<int>(aLevel) < static_cast<int>(SLevel()))
    {
        return;
    }

    GpLogElement logElement
    {
        GpDateTimeOps::SUnixTS_ms(),
        GpDateTimeOps::SSteadyTS_us() - GpDateTimeOps::SSteadyTS_us_AtAppStart(),
        aLevel,
        aMode,
        std::move(aMessage)
    };

    iLogQueue.AddElement(aChainId, std::move(logElement));
}

void    GpLog::EndChain (const GpUUID& aChainId)
{
    iLogQueue.EndChain(aChainId);
}

void LOG_SYS_INFO
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    std::string message = fmt::format
    (
        "{}:" \
        "\n{:>12}: {} {}" \
        "\n{:>12}: {}" \
        "\n{:>12}: {}",
        aMessage,
        "OS",         GpSystemInfo::SOsName(), GpSystemInfo::SOsInfo(),
        "Build arch", GpSystemInfo::SArcName(),
        "CPU cores",  GpSystemInfo::SHardwareConcurrency()
    );

    // Linked libraries
    message.append("\n\nLinked libraries:");
    const GpLinkedLibsInfo::InfoAsTextT linkedLibraries = GpLinkedLibsInfo::S().InfoAsText();
    size_t id = 1;
    for (const auto&[name, version]: linkedLibraries)
    {
        message.append
        (
            fmt::format
            (
                "\n[{:03}]: {:>22}: v{}",
                id++,
                name,
                version
            )
        );
    }

    LOG_INFO(message, aSourceLocation);
}

void LOG_END_CHAIN
(
    const GpUUID& aChainId
) noexcept
{
    try
    {
        GpLog::S().EndChain(aChainId);
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_END_CHAIN]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_END_CHAIN]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_END_CHAIN]: unknown"_sv);
    }
}

void LOG_DEBUG
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_DEBUG,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown"_sv);
    }
}

void LOG_DEBUG
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_DEBUG,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown"_sv);
    }
}

void LOG_DEBUG
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_DEBUG,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown"_sv);
    }
}

void LOG_DEBUG
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_DEBUG,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown"_sv);
    }
}

void LOG_INFO
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_INFO,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown"_sv);
    }
}

void LOG_INFO
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_INFO,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown"_sv);
    }
}

void LOG_INFO
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_INFO,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown"_sv);
    }
}

void LOG_INFO
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_INFO,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown"_sv);
    }
}

void LOG_WARNING
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_WARNING,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown"_sv);
    }
}

void LOG_WARNING
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_WARNING,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown"_sv);
    }
}

void LOG_WARNING
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_WARNING,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown"_sv);
    }
}

void LOG_WARNING
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_WARNING,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown"_sv);
    }
}

void LOG_ERROR
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown"_sv);
    }
}

void LOG_ERROR
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown"_sv);
    }
}

void LOG_ERROR
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown"_sv);
    }
}

void LOG_ERROR
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown"_sv);
    }
}

void LOG_CRITICAL_ERROR
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_CRITICAL_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown"_sv);
    }
}

void LOG_CRITICAL_ERROR
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::L_CRITICAL_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown"_sv);
    }
}

void LOG_CRITICAL_ERROR
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_CRITICAL_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown"_sv);
    }
}

void LOG_CRITICAL_ERROR
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::string(aMessage)),
            GpLogLevel::L_CRITICAL_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown"_sv);
    }
}

void LOG_EXCEPTION
(
    std::string_view        aPrefix,
    const GpException&      aException,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        std::string exceptionMsg;

        if (aPrefix.empty())
        {
            exceptionMsg = aException.what();
        } else
        {
            exceptionMsg = fmt::format
            (
                "{}: {}",
                aPrefix,
                aException.what()
            );
        }

        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(exceptionMsg)),
            GpLogLevel::L_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown"_sv);
    }
}

void LOG_EXCEPTION
(
    std::string_view        aPrefix,
    const GpException&      aException,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        std::string exceptionMsg;

        if (aPrefix.empty())
        {
            exceptionMsg = aException.what();
        } else
        {
            exceptionMsg = fmt::format
            (
                "{}: {}",
                aPrefix,
                aException.what()
            );
        }

        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(exceptionMsg)),
            GpLogLevel::L_ERROR,
            GpLogMode::CHAIN_END,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown"_sv);
    }
}

//------------------------------------- GpMarkTraceTS -------------------------------------
void LOG_DEBUG
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_DEBUG,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown"_sv);
    }
}

void LOG_DEBUG
(
    const GpLogMarkTraceTS& aMarkTraceTS,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    LOG_DEBUG(GpLogMarkTraceTS(aMarkTraceTS), aSourceLocation);
}

void LOG_DEBUG
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_DEBUG,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown"_sv);
    }
}

void LOG_INFO
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_INFO,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown"_sv);
    }
}

void LOG_INFO
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_INFO,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown"_sv);
    }
}

void LOG_WARNING
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_WARNING,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown"_sv);
    }
}

void LOG_WARNING
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_WARNING,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown"_sv);
    }
}

void LOG_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown"_sv);
    }
}

void LOG_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown"_sv);
    }
}

void LOG_CRITICAL_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_CRITICAL_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown"_sv);
    }
}

void LOG_CRITICAL_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgMarkTraceTS>(std::move(aMarkTraceTS)),
            GpLogLevel::L_CRITICAL_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what());
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown"_sv);
    }
}

}// namespace GPlatform
