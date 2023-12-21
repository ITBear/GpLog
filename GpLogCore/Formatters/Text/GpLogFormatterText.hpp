#pragma once

#include "../../GpLogLevel.hpp"

#include <GpCore2/GpUtils/Streams/GpByteSerializer.hpp>
#include <GpCore2/GpUtils/Types/Units/SI/GpUnitsSI_Time.hpp>

namespace GPlatform {

class GpLogElementMsg;

class GP_LOG_CORE_API GpLogFormatterText final: public GpByteSerializer
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogFormatterText)
    CLASS_DD(GpLogFormatterText)

public:
                            GpLogFormatterText  (void) noexcept = default;
    virtual                 ~GpLogFormatterText (void) noexcept override final;

    virtual void            Serialize           (const GpAny&   aObject,
                                                 GpByteWriter&  aWriter) const override final;

private:
    void                    WriteLevel          (const GpLogLevel::EnumT    aLevel,
                                                 GpByteWriter&              aWriter) const;
    void                    WriteUnixTS         (const unix_ts_ms_t         aUnixTS,
                                                 GpByteWriter&              aWriter) const;
    void                    WriteSteadyTS       (const microseconds_t       aSteadyTS,
                                                 GpByteWriter&              aWriter) const;
    std::u8string           GenMessage          (const GpLogElementMsg&     aMessage) const;

private:
    static const std::array<std::u8string, GpLogLevel::SCount()>    sLevels;
};

}//namespace GPlatform
