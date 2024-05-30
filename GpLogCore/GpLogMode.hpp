#pragma once

#include "GpLogCore_global.hpp"

#include <GpCore2/GpUtils/Types/Enums/GpEnum.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringOps.hpp>

namespace GPlatform {

GP_ENUM(GP_LOG_CORE_API, GpLogMode,
    ADD_TO_CHAIN,
    CHAIN_END
);

}// namespace GPlatform
