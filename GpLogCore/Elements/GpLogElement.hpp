#pragma once

#include "GpLogElementMsg.hpp"
#include "../GpLogMode.hpp"
#include "../../../GpCore2/GpUtils/Types/Units/SI/GpUnitsSI_Time.hpp"

namespace GPlatform {

class GpLogElement
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_COPY(GpLogElement)
    CLASS_DD(GpLogElement)

public:
    inline                      GpLogElement    (const unix_ts_ms_t         aUnixTS,
                                                 const microseconds_t       aSteadyTS,
                                                 const GpLogLevel::EnumT    aLevel,
                                                 const GpLogMode::EnumT     aMode,
                                                 GpLogElementMsg::CSP       aMessage) noexcept;
    inline                      GpLogElement    (GpLogElement&& aElement) noexcept;
                                ~GpLogElement   (void) noexcept = default;

    GpLogElement&               operator=       (GpLogElement&& aElement) noexcept = delete;

    unix_ts_ms_t                UnixTS          (void) const noexcept {return iUnixTS;}
    microseconds_t              SteadyTS        (void) const noexcept {return iSteadyTS;}
    GpLogLevel::EnumT           Level           (void) const noexcept {return iLevel;}
    GpLogMode::EnumT            Mode            (void) const noexcept {return iMode;}
    const GpLogElementMsg&      Message         (void) const {return iMessage.V();}

private:
    const unix_ts_ms_t          iUnixTS;
    const microseconds_t        iSteadyTS;
    const GpLogLevel::EnumT     iLevel;
    const GpLogMode::EnumT      iMode;
    GpLogElementMsg::CSP        iMessage;
};

GpLogElement::GpLogElement
(
    const unix_ts_ms_t          aUnixTS,
    const microseconds_t        aSteadyTS,
    const GpLogLevel::EnumT     aLevel,
    const GpLogMode::EnumT      aMode,
    GpLogElementMsg::CSP        aMessage

) noexcept:
iUnixTS(aUnixTS),
iSteadyTS(aSteadyTS),
iLevel(aLevel),
iMode(aMode),
iMessage(std::move(aMessage))
{
}

GpLogElement::GpLogElement (GpLogElement&& aElement) noexcept:
iUnixTS(std::move(aElement.iUnixTS)),
iSteadyTS(std::move(aElement.iSteadyTS)),
iLevel(std::move(aElement.iLevel)),
iMode(std::move(aElement.iMode)),
iMessage(std::move(aElement.iMessage))
{
}

}//namespace GPlatform
