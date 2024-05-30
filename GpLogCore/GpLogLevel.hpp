#pragma once

#include "GpLogCore_global.hpp"
#include <GpCore2/GpUtils/Types/Enums/GpEnum.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringOps.hpp>

namespace GPlatform {

GP_ENUM(GP_LOG_CORE_API, GpLogLevel,
    L_DEBUG,
    L_INFO,
    L_WARNING,
    L_ERROR,
    L_CRITICAL_ERROR
);

}// namespace GPlatform
