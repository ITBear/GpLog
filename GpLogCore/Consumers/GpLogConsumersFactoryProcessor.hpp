#pragma once

#include "GpLogConsumerFactory.hpp"
#include "GpLogConsumerConfigDesc.hpp"

namespace GPlatform {

class GpLogConsumersFactoryProcessor
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpLogConsumersFactoryProcessor)
    CLASS_DD(GpLogConsumersFactoryProcessor)

protected:
    inline                              GpLogConsumersFactoryProcessor  (std::u8string aName) noexcept;

public:
    virtual                             ~GpLogConsumersFactoryProcessor (void) noexcept = default;

    std::u8string_view                  Name                            (void) const noexcept {return iName;}

    virtual GpLogConsumerFactory::SP    Process                         (GpByteSerializer::SP           aFormatter,
                                                                         const GpLogConsumerConfigDesc& aCfgDesc) const = 0;

private:
    const std::u8string                 iName;
};

GpLogConsumersFactoryProcessor::GpLogConsumersFactoryProcessor (std::u8string aName) noexcept:
iName(std::move(aName))
{
}

}//namespace GPlatform
