#pragma once

#include "Consumers/GpLogConsumers.hpp"
#include "Elements/GpLogElementMsg.hpp"
#include "GpLogConfigDesc.hpp"
#include "GpLogExecutor.hpp"
#include "GpLogChain.hpp"


namespace GPlatform {

class GPLOG_API GpLogger
{
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogger)
    CLASS_TAG(THREAD_SAFE)

public:
    using CategoryLevelsT = GpMap<std::string, GpLogLevel, std::less<>>;

public:
                            GpLogger            (void) noexcept;
                            ~GpLogger           (void) noexcept;

    static GpLogger&        S                   (void) noexcept {return sLogger;}

    void                    StartFromConfig     (const GpLogConfigDesc& aCfgDesc);
    void                    Stop                (void);

    void                    Log                 (GpLogElementMsg::CSP           aMessage,
                                                 const GpLogLevel::EnumT        aLevel,
                                                 std::string&&                  aCategory,
                                                 const GpUUID&                  aChainId,
                                                 const GpLogConsumeMode::EnumT  aConsumeMode);

    void                    EndChain            (const GpUUID&  aChainId);

private:
    GpLogExecutor::SP       iLogExecutor;
    GpLogLevel::EnumT       iDefaultLevel   = GpLogLevel::INFO;
    CategoryLevelsT         iCategoryLevels;

    static GpLogger         sLogger;
};

}//namespace GPlatform
