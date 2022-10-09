#include "GpLogTaskFiberBase.hpp"
#include "GpLog.hpp"

namespace GPlatform {

GpLogTaskFiberBase::~GpLogTaskFiberBase (void) noexcept
{
    try
    {
        GpLog::S().EndChain(Guid());
    } catch (...)
    {
        //NOP
    }
}

}//namespace GPlatform
