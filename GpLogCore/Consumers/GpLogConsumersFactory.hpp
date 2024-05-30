#pragma once

#include <GpLog/GpLogCore/Consumers/GpLogConsumerFactory.hpp>
#include <GpLog/GpLogCore/Consumers/GpLogConsumerConfigDesc.hpp>
#include <GpLog/GpLogCore/Consumers/GpLogConsumersFactoryProcessor.hpp>

#include <GpCore2/GpUtils/Types/Containers/GpDictionary.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumersFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumersFactory)
    CLASS_DD(GpLogConsumersFactory)

    using ProcessorsT = GpDictionary<boost::container::small_flat_map<std::string, GpLogConsumersFactoryProcessor::SP, 8, std::less<>>>;

public:
                                GpLogConsumersFactory       (void) noexcept;
    virtual                     ~GpLogConsumersFactory      (void) noexcept;

    void                        AddDefaultProcessorConsole  (void);
    void                        AddDefaultProcessorFile     (void);
    void                        AddProcessor                (GpLogConsumersFactoryProcessor::SP aProcessor);

    GpLogConsumerFactory::SP    FactoryFromCfg              (std::string_view               aName,
                                                             const GpLogConsumerConfigDesc& aCfgDesc,
                                                             GpByteSerializer::SP           aFormatter) const;
protected:
    ProcessorsT                 iProcessors;
};

}// namespace GPlatform
