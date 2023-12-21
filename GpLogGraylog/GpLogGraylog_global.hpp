#pragma once

#include <GpCore2/GpUtils/Macro/GpMacroImportExport.hpp>

#if defined(GP_LOG_GRAYLOG_LIBRARY)
    #define GP_LOG_GRAYLOG_API GP_DECL_EXPORT
#else
    #define GP_LOG_GRAYLOG_API GP_DECL_IMPORT
#endif
