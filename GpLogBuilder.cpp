#include "GpLogBuilder.hpp"

namespace GPlatform {

void    GpLogBuilder::Out (void)
{
    GpLogger::S().Log
    (
        std::move(iMessage),
        iLevel,
        std::move(iCategory),
        iChainId,
        iConsumeMode
    );
}

void    GpLogBuilder::SEndChain (const GpUUID& aChainId)
{
    GpLogger::S().EndChain(aChainId);
}

}//namespace GPlatform
