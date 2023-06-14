#include "GpLogTaskFiberBase.hpp"
#include "GpLog.hpp"

namespace GPlatform {

GpLogTaskFiberBase::~GpLogTaskFiberBase (void) noexcept
{
    try
    {
        GpLog::S().EndChain(Guid());
    } catch (const GpException& e)
    {
        GpStringUtils::SCerr(u8"[GpLogTaskFiberBase::~GpLogTaskFiberBase]: exception: "_sv + e.what());
    } catch (const std::exception& e)
    {
        GpStringUtils::SCerr(u8"[GpLogTaskFiberBase::~GpLogTaskFiberBase]: exception: "_sv + e.what());
    } catch (const boost::context::detail::forced_unwind&)
    {
        GpStringUtils::SCerr(u8"[GpLogTaskFiberBase::~GpLogTaskFiberBase]: exception: boost::context::detail::forced_unwind"_sv);
    } catch (...)
    {
        GpStringUtils::SCerr(u8"[GpLogTaskFiberBase::~GpLogTaskFiberBase]: unknown exception"_sv);
    }
}

}//namespace GPlatform
