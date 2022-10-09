#pragma once

#include "../GpLogLevel.hpp"

namespace GPlatform {

class GpLogElementMsg
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogElementMsg)
    CLASS_DD(GpLogElementMsg)

    enum class TypeT
    {
        STR,
        TRACE_TS
    };

protected:
    inline              GpLogElementMsg     (const TypeT aType) noexcept;

public:
    virtual             ~GpLogElementMsg    (void) noexcept = default;

    TypeT               Type                (void) const noexcept {return iType;}

private:
    const TypeT         iType;
};

GpLogElementMsg::GpLogElementMsg (const TypeT aType) noexcept:
iType(aType)
{
}

}//namespace GPlatform
