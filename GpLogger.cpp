#include "GpLogger.hpp"
#include "Consumers/GpLogConsumerConfigBuilder.hpp"

namespace GPlatform {

GpLogger    GpLogger::sLogger;

GpLogger::GpLogger (void) noexcept
{
}

GpLogger::~GpLogger (void) noexcept
{
}

void    GpLogger::StartFromConfig (const GpLogConfigDesc& aCfgDesc)
{
    THROW_GPE_COND
    (
        iLogExecutor.IsNULL(),
        "Log already configured"_sv
    );

    iDefaultLevel   = aCfgDesc.default_level.Value();

    for (auto&[k, v]: aCfgDesc.category_levels)
    {
        iCategoryLevels[k] = GpLogLevel::SFromString(v);
    }

    iLogExecutor = MakeSP<GpLogExecutor>();
    iLogExecutor->Start(GpLogConsumerConfigBuilder::SFromConfig(aCfgDesc.consumers));
}

void    GpLogger::Stop (void)
{
    THROW_GPE_COND
    (
        iLogExecutor.IsNotNULL(),
        "Log not configured"_sv
    );

    iLogExecutor->RequestStop();
    iLogExecutor->Join();
}

void    GpLogger::Log
(
    GpLogElementMsg::CSP            aMessage,
    const GpLogLevel::EnumT         aLevel,
    std::string&&                   aCategory,
    const GpUUID&                   aChainId,
    const GpLogConsumeMode::EnumT   aConsumeMode
)
{
    const auto iter = iCategoryLevels.find(aCategory);

    std::string         category;
    GpLogLevel::EnumT   maxLevel;

    if (iter == iCategoryLevels.end())
    {
        category = std::string("default"_sv);
        maxLevel = iDefaultLevel;
    } else
    {
        category = std::move(aCategory);
        maxLevel = iter->second.Value();
    }

    if (int(aLevel) < int(maxLevel))
    {
        return;
    }

    GpTaskFiber::SP currentTask = GpTaskFiber::SCurrentTask();

    GpLogElement logElement
    (
        GpDateTimeOps::SUnixTS_ms(),
        GpDateTimeOps::SSteadyTS_us() - GpDateTimeOps::SSteadyTS_us_AtAppStart(),
        std::this_thread::get_id(),
        currentTask.IsNotNULL() ? std::string(currentTask->Name()) : std::string(""_sv),
        aLevel,
        std::move(category),
        std::move(aMessage),
        aConsumeMode
    );

    iLogExecutor->AddElement(aChainId, std::move(logElement));
}

void    GpLogger::EndChain (const GpUUID& aChainId)
{
    iLogExecutor->EndChain(aChainId);
}

}//namespace GPlatform
