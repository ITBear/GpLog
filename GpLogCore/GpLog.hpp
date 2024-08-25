#pragma once

#include <GpLog/GpLogCore/GpLogLevel.hpp>
#include <GpLog/GpLogCore/GpLogMode.hpp>
#include <GpLog/GpLogCore/GpLogExecutor.hpp>

#include <GpLog/GpLogCore/Elements/GpLogElementMsg.hpp>
#include <GpLog/GpLogCore/Elements/GpLogElementMsgStr.hpp>
#include <GpLog/GpLogCore/Elements/GpLogElementMsgStrFn.hpp>
#include <GpLog/GpLogCore/Elements/GpLogElementMsgMarkTraceTS.hpp>
#include <GpLog/GpLogCore/Config/GpLogConfigDesc.hpp>
//#include <GpLog/GpLogCore/Consumers/GpLogConsumers.hpp>
//#include "Consumers/GpLogConsumers.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLog
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLog)
    CLASS_DD(GpLog)

public:
                                GpLog           (void) noexcept;
    virtual                     ~GpLog          (void) noexcept;

    static void                 SInit           (void);
    static void                 SClear          (void);
    static GpLog&               S               (void) {return sInstance.Vn();}
    static GpLogLevel::EnumT    SLevel          (void) noexcept {return sLevel;}
    static void                 SSetLevel       (GpLogLevel::EnumT aLevel) noexcept {sLevel = aLevel;}

    void                        StartDefault    (void);
    void                        StartFromConfig (const GpLogConfigDesc&         aConfigDesc,
                                                 GpLogLevel::EnumT              aExtLevelValue,
                                                 const GpLogConsumersFactory&   aConsumersFactory);
    void                        Start           (const GpLogConsumerFactory::C::Vec::SP&    aConsumerFactories,
                                                 GpLogLevel::EnumT                          aLevel,
                                                 seconds_t                                  aFlushPeriod);
    void                        Stop            (void);
    void                        Flush           (void);

    void                        Logout          (GpLogElementMsg::CSP   aMessage,
                                                 GpLogLevel::EnumT      aLevel,
                                                 GpLogMode::EnumT       aMode,
                                                 const GpUUID&          aChainId,
                                                 const SourceLocationT& aSourceLocation);

    void                        EndChain        (const GpUUID& aChainId);

private:
    GpLogQueue                  iLogQueue;
    GpLogExecutor               iLogExecutor;

    static GpLogLevel::EnumT    sLevel;
    static GpLog::SP            sInstance;
};

//------------------------------------- Sys info -------------------------------------
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
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_DEBUG
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_INFO
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_WARNING
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_ERROR
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::string             aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::string             aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::string_view        aMessage,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_CRITICAL_ERROR
(
    std::string_view        aMessage,
    const GpUUID&           aChainId,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    std::string_view        aPrefix,
    const GpException&      aException,
    const SourceLocationT&  aSourceLocation = SourceLocationT::current()
) noexcept;

GP_LOG_CORE_API void    LOG_EXCEPTION
(
    std::string_view        aPrefix,
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
    const GpLogMarkTraceTS& aMarkTraceTS,
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

}// namespace GPlatform
