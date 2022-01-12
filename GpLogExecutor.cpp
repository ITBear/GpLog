#include "GpLogExecutor.hpp"

namespace GPlatform {

GpLogExecutor::GpLogExecutor (void) noexcept
{
}

GpLogExecutor::~GpLogExecutor (void) noexcept
{
}

void    GpLogExecutor::Start (const GpLogConsumerFactory::C::Vec::SP& aConsumerFactories) noexcept
{
    //Start thread
    iCondVar = MakeSP<GpConditionVar>();

    //Create executor
    iRunnable = MakeSP<GpLogRunnable>(iCondVar, aConsumerFactories);

    //Run
    iThread.Run(iRunnable);
}

void    GpLogExecutor::RequestStop (void) noexcept
{
    std::scoped_lock lock(iLock);

    iThread.RequestStop();
}

void    GpLogExecutor::Join (void) noexcept
{
    std::scoped_lock lock(iLock);

    iThread.Join();
}

void    GpLogExecutor::WakeupAll (void) noexcept
{
    iCondVar.Vn().WakeupAll();
}

void    GpLogExecutor::WakeupOne (void) noexcept
{
    iCondVar.Vn().WakeupOne();
}

void    GpLogExecutor::AddElement
(
    const GpUUID&   aChainId,
    GpLogElement&&  aLogElement
)
{
    iRunnable->AddElement(aChainId, std::move(aLogElement));
}

void    GpLogExecutor::EndChain (const GpUUID& aChainId)
{
    iRunnable->EndChain(aChainId);
}

}//namespace GPlatform
