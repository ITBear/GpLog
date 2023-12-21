#pragma once

#include "../../GpLogCore_global.hpp"

#include <GpCore2/GpUtils/Streams/GpByteSerializerFactory.hpp>

namespace GPlatform {

class GP_LOG_CORE_API GpLogFormatterTextFactory final: public GpByteSerializerFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpLogFormatterTextFactory)
    CLASS_DD(GpLogFormatterTextFactory)

public:
                                        GpLogFormatterTextFactory   (void) noexcept = default;
    virtual                             ~GpLogFormatterTextFactory  (void) noexcept override final = default;

    virtual GpByteSerializer::SP        NewInstance                 (void) const override final;
};

}//namespace GPlatform
