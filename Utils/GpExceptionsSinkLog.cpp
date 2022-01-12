#include "GpExceptionsSinkLog.hpp"

#if defined(GP_USE_EXCEPTIONS)

#include <iostream>

namespace GPlatform{

void    GpExceptionsSinkLog::OnSink
(
    std::string_view        aMsg,
    const SourceLocationT&  aLocation
) noexcept
{
    try
    {
        SourceLocationT     l   = aLocation;
        const std::string   msg = "[GpExceptionsSinkLog::SSink]:"_sv
                                  + " what '"_sv + aMsg + "'"_sv
                                  + ", sinked in file '"_sv + l.file_name() + "'"_sv
                                  + ", line "_sv + l.line()
                                  + ", function "_sv + l.function_name();

        if (GpTaskFiber::SIsIntoFiber())
        {
            GP_LOG_INFO(msg, GPlatform::GpTaskFiber::SGuid());
        } else
        {
            GP_LOG_INFO(msg);
        }
    } catch (const std::exception& e)
    {
        std::cerr << "[GpExceptionsSinkLog::OnSink]: exception '"_sv << e.what() << "'"_sv << std::endl;
    } catch (...)
    {
        std::cerr << "[GpExceptionsSinkLog::OnSink]: uknown exception"_sv << std::endl;
    }
}

}//GPlatform

#endif//#if defined(GP_USE_EXCEPTIONS)
