#pragma once

#include "GpLogConsumerFactory.hpp"
#include "GpLogConsumerConfigDesc.hpp"
#include "GpLogConsumersFactoryProcessor.hpp"
#include "../../../GpCore2/GpUtils/Types/Containers/GpDictionary.hpp"

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumersFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumersFactory)
    CLASS_DD(GpLogConsumersFactory)

    using ProcessorsT = GpDictionary<std::u8string, GpLogConsumersFactoryProcessor::SP>;

public:
                                GpLogConsumersFactory       (void) noexcept = default;
    virtual                     ~GpLogConsumersFactory      (void) noexcept = default;

    void                        AddDefaultProcessorConsole  (void);
    void                        AddDefaultProcessorFile     (void);
    void                        AddProcessor                (GpLogConsumersFactoryProcessor::SP aProcessor);

    GpLogConsumerFactory::SP    FactoryFromCfg              (std::u8string_view             aName,
                                                             const GpLogConsumerConfigDesc& aCfgDesc,
                                                             GpByteSerializer::SP           aFormatter) const;
protected:
    ProcessorsT                 iProcessors;
};

}//namespace GPlatform
