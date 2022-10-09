#pragma once

#include "../GpLogCore_global.hpp"

#if defined(GP_USE_MULTITHREADING)
#if defined(GP_USE_MULTITHREADING_FIBERS)

namespace GPlatform {

class GP_LOG_CORE_API GpLogTaskFiberBase: public GpTaskFiberBase
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogTaskFiberBase)
    CLASS_DD(GpLogTaskFiberBase)

protected:
    inline                      GpLogTaskFiberBase      (std::string aName) noexcept;

public:
    virtual                     ~GpLogTaskFiberBase     (void) noexcept override;
};

GpLogTaskFiberBase::GpLogTaskFiberBase (std::string aName) noexcept:
GpTaskFiberBase(std::move(aName))
{
}

}//namespace GPlatform

#endif//#if defined(GP_USE_MULTITHREADING_FIBERS)
#endif//#if defined(GP_USE_MULTITHREADING)
