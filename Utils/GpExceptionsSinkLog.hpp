#pragma once

#include "../GpLogBuilder.hpp"

#if defined(GP_USE_EXCEPTIONS)

namespace GPlatform{

class GPLOG_API GpExceptionsSinkLog final: public  GpExceptionsSink
{
public:
                                GpExceptionsSinkLog     (void) noexcept = default;
                                GpExceptionsSinkLog     (const GpExceptionsSinkLog&) = delete;
                                GpExceptionsSinkLog     (GpExceptionsSinkLog&&) = delete;
                                ~GpExceptionsSinkLog    (void) noexcept = default;

    virtual void                OnSink                  (std::string_view       aMsg,
                                                         const SourceLocationT& aLocation) noexcept override final;
};

}//GPlatform

#endif//#if defined(GP_USE_EXCEPTIONS)
