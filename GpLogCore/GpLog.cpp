#include "GpLog.hpp"
#include "Consumers/Console/GpLogConsumerConsoleFactory.hpp"
#include "Formatters/Text/GpLogFormatterText.hpp"
#include "../../GpCore2/GpUtils/Types/Strings/GpStringUtils.hpp"
#include "../../GpCore2/GpUtils/Exceptions/GpExceptionUtils.hpp"

#include <iostream>

namespace GPlatform{

GpLog   GpLog::sInstance;

GpLog::~GpLog (void) noexcept
{
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
        GpLogLevel::DEBUG,
        1.0_si_s
    );
}

void    GpLog::StartFromConfig
(
    const GpLogConfigDesc&          aConfigDesc,
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
        aConfigDesc.min_level.Value(),
        aConfigDesc.flush_period
    );
}

void    GpLog::Start
(
    const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories,
    const GpLogLevel::EnumT                 aMinLevel,
    const seconds_t                         aFlushPeriod
)
{
    iMinLevel = aMinLevel;

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

    if (!iLogQueue.IsEmpty())
    {
        StartDefault();

        while (!iLogQueue.IsEmpty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        iLogExecutor.RequestStop();
        iLogExecutor.Join();
    }
}

void    LOG_END_CHAIN
(
    const GpUUID& aChainId
) noexcept
{
    try
    {
        GpLog::S().EndChain(aChainId);
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_END_CHAIN]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_END_CHAIN]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_END_CHAIN]: unknown\n"_sv);
    }
}

void    LOG_DEBUG
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::DEBUG,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown\n"_sv);
    }
}

void    LOG_DEBUG
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::DEBUG,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown\n"_sv);
    }
}

void    LOG_DEBUG
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::DEBUG,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown\n"_sv);
    }
}

void    LOG_DEBUG
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::DEBUG,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown\n"_sv);
    }
}

void    LOG_INFO
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::INFO,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown\n"_sv);
    }
}

void    LOG_INFO
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::INFO,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown\n"_sv);
    }
}

void    LOG_INFO
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::INFO,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown\n"_sv);
    }
}

void    LOG_INFO
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::INFO,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown\n"_sv);
    }
}

void    LOG_WARNING
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::WARNING,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown\n"_sv);
    }
}

void    LOG_WARNING
(
    std::u8string               aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::WARNING,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown\n"_sv);
    }
}

void    LOG_WARNING
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::WARNING,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown\n"_sv);
    }
}

void    LOG_WARNING
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::WARNING,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown\n"_sv);
    }
}

void    LOG_ERROR
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown\n"_sv);
    }
}

void    LOG_ERROR
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown\n"_sv);
    }
}

void    LOG_ERROR
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown\n"_sv);
    }
}

void    LOG_ERROR
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown\n"_sv);
    }
}

void    LOG_CRITICAL_ERROR
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::CRITICAL_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown\n"_sv);
    }
}

void    LOG_CRITICAL_ERROR
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::CRITICAL_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown\n"_sv);
    }
}

void    LOG_CRITICAL_ERROR
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::CRITICAL_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown\n"_sv);
    }
}

void    LOG_CRITICAL_ERROR
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::CRITICAL_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown\n"_sv);
    }
}

void    LOG_PAYLOAD
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::PAYLOAD,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: unknown\n"_sv);
    }
}

void    LOG_PAYLOAD
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::move(aMessage)),
            GpLogLevel::PAYLOAD,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: unknown\n"_sv);
    }
}

void    LOG_PAYLOAD
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::PAYLOAD,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: unknown\n"_sv);
    }
}

void    LOG_PAYLOAD
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(std::u8string(aMessage)),
            GpLogLevel::PAYLOAD,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_PAYLOAD]: unknown\n"_sv);
    }
}

void    LOG_EXCEPTION
(
    const std::exception&   aException,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(GpExceptionUtils::SToString(aException, aSourceLocation)),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown\n"_sv);
    }
}

void    LOG_EXCEPTION
(
    const std::exception&   aException,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(GpExceptionUtils::SToString(aException, aSourceLocation)),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown\n"_sv);
    }
}

void    LOG_EXCEPTION
(
    const GpException&      aException,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(GpExceptionUtils::SToString(aException)),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown\n"_sv);
    }
}

void    LOG_EXCEPTION
(
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>
            (
                GpExceptionUtils::SToString
                (
                    u8"Unknown exception"_sv,
                    aSourceLocation,
                    GpExceptionUtils::ExceptionType::STD,
                    std::nullopt
                ).fullMessage
            ),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown\n"_sv);
    }
}

void    LOG_EXCEPTION
(
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>
            (
                GpExceptionUtils::SToString
                (
                    u8"Unknown exception"_sv,
                    aSourceLocation,
                    GpExceptionUtils::ExceptionType::STD,
                    std::nullopt
                ).fullMessage
            ),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown\n"_sv);
    }
}

void    LOG_EXCEPTION
(
    const GpException&      aException,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation
) noexcept
{
    try
    {
        GpLog::S().Logout
        (
            MakeCSP<GpLogElementMsgStr>(GpExceptionUtils::SToString(aException)),
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_EXCEPTION]: unknown\n"_sv);
    }
}

//------------------------------------- GpMarkTraceTS -------------------------------------
void    LOG_DEBUG
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
            GpLogLevel::DEBUG,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown\n"_sv);
    }
}

void    LOG_DEBUG
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
            GpLogLevel::DEBUG,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_DEBUG]: unknown\n"_sv);
    }
}

void    LOG_INFO
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
            GpLogLevel::INFO,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown\n"_sv);
    }
}

void    LOG_INFO
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
            GpLogLevel::INFO,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_INFO]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_INFO]: unknown\n"_sv);
    }
}

void    LOG_WARNING
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
            GpLogLevel::WARNING,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown\n"_sv);
    }
}

void    LOG_WARNING
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
            GpLogLevel::WARNING,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_WARNING]: unknown\n"_sv);
    }
}

void    LOG_ERROR
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
            GpLogLevel::ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown\n"_sv);
    }
}

void    LOG_ERROR
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
            GpLogLevel::ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_ERROR]: unknown\n"_sv);
    }
}

void    LOG_CRITICAL_ERROR
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
            GpLogLevel::CRITICAL_ERROR,
            GpLogMode::CHAIN_END,
            GpUUID::CE_Zero(),
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown\n"_sv);
    }
}

void    LOG_CRITICAL_ERROR
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
            GpLogLevel::CRITICAL_ERROR,
            GpLogMode::ADD_TO_CHAIN,
            aChainId,
            aSourceLocation
        );
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: "_sv + e.what() + "\n"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr("[LOG_CRITICAL_ERROR]: unknown\n"_sv);
    }
}

}//GPlatform
