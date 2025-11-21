#include <GpLog/GpLogCore/GpLogCoreLib.hpp>
#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>

GP_STATIC_INITIALIZER_IMPL(GpLogCore)
GP_LIB_REGISTRATOR(GpLogCoreLib)

void    GpLogCore_StaticInitializer::OnInitialize (void)
{
    GpLogCoreLib::SRegisterSelf();
}
