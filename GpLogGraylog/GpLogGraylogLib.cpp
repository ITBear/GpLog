#include <GpLog/GpLogGraylog/GpLogGraylogLib.hpp>
#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>

GP_STATIC_INITIALIZER_IMPL(GpLogGraylog)
GP_LIB_REGISTRATOR(GpLogGraylogLib)

void    GpLogGraylog_StaticInitializer::OnInitialize (void)
{
    GpLogGraylogLib::SRegisterSelf();
}
