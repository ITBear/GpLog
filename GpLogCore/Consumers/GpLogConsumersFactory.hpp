#pragma once

#include <GpLog/GpLogCore/Consumers/GpLogConsumerFactory.hpp>
#include <GpLog/GpLogCore/Consumers/GpLogConsumerConfigDesc.hpp>
#include <GpLog/GpLogCore/Consumers/GpLogConsumersFactoryProcessor.hpp>

#include <GpCore2/GpUtils/Types/Containers/GpSharedMap.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogConsumersFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogConsumersFactory)
    CLASS_DD(GpLogConsumersFactory)

    using ProcessorsT = GpSharedMap<boost::container::small_flat_map<std::string, GpLogConsumersFactoryProcessor::SP, 16, std::less<>>>;

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
