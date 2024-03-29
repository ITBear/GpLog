#pragma once

#include "GpLogLevel.hpp"
#include "GpLogMode.hpp"
#include "GpLogExecutor.hpp"
#include "Elements/GpLogElementMsg.hpp"
#include "Elements/GpLogElementMsgStr.hpp"
#include "Elements/GpLogElementMsgStrFn.hpp"
#include "Elements/GpLogElementMsgMarkTraceTS.hpp"
#include "Consumers/GpLogConsumers.hpp"
#include "Config/GpLogConfigDesc.hpp"

#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>

namespace GPlatform{

GP_DECLARE_LIB(GP_LOG_CORE_API, GpLogCoreLib)

class GP_LOG_CORE_API GpLog
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLog)
    CLASS_DD(GpLog)

public:
    inline                  GpLog           (void) noexcept;
    virtual                 ~GpLog          (void) noexcept;

    static void             SInit           (void);
    static void             SClear          (void);
    static GpLog&           S               (void) {return sInstance.Vn();}

    void                    StartDefault    (void);
    void                    StartFromConfig (const GpLogConfigDesc&         aConfigDesc,
                                             const GpLogConsumersFactory&   aConsumersFactory);
    void                    Start           (const GpLogConsumerFactory::C::Vec::SP&    aConsumerFactories,
                                             const GpLogLevel::EnumT                    aMinLevel,
                                             const seconds_t                            aFlushPeriod);
    void                    Stop            (void);

    inline void             Logout          (GpLogElementMsg::CSP       aMessage,
                                             const GpLogLevel::EnumT    aLevel,
                                             const GpLogMode::EnumT     aMode,
                                             const GpUUID&              aChainId,
                                             const SourceLocationT&     aSourceLocation);

    inline void             EndChain        (const GpUUID&  aChainId);

private:
    GpLogQueue              iLogQueue;
    GpLogExecutor           iLogExecutor;
    GpLogLevel::EnumT       iMinLevel   = GpLogLevel::INFO;

    static GpLog::SP        sInstance;
};

GpLog::GpLog (void) noexcept:
iLogExecutor(iLogQueue)
{
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
    if (int(aLevel) < int(iMinLevel))
    {
        return;
    }

    GpLogElement logElement
    (
        GpDateTimeOps::SUnixTS_ms(),
        GpDateTimeOps::SSteadyTS_us() - GpDateTimeOps::SSteadyTS_us_AtAppStart(),
        aLevel,
        aMode,
        std::move(aMessage)
    );

    iLogQueue.AddElement(aChainId, std::move(logElement));
}

void    GpLog::EndChain (const GpUUID& aChainId)
{
    iLogQueue.EndChain(aChainId);
}

//------------------------------------- Sys info -------------------------------------
GP_LOG_CORE_API void    LOG_SYS_INFO
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_SYS_INFO
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

//------------------------------------- Text -------------------------------------
GP_LOG_CORE_API void    LOG_END_CHAIN
(
    const GpUUID& aChainId
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::u8string           aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::u8string           aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::u8string_view      aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::u8string_view      aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    const std::exception&   aException,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    const std::exception&   aException,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    const GpException&      aException,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    const GpException&      aException,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

//------------------------------------- GpMarkTraceTS -------------------------------------
GP_LOG_CORE_API void    LOG_DEBUG
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;


GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    GpLogMarkTraceTS&&      aMarkTraceTS,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

}//GPlatform
