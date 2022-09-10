#include "GpLogConsumerConsole.hpp"

#include <iostream>

namespace GPlatform {

GpLogConsumerConsole::~GpLogConsumerConsole (void) noexcept
{
}

void	GpLogConsumerConsole::Consume (GpLogChain::CSP aLogChain)
{
	const GpLogChain& logChain = aLogChain.V();

	iTmpBuffer.resize(4096);
	GpByteWriterStorageByteArray	dataStorage(iTmpBuffer);
	GpByteWriter					dataWriter(dataStorage);

	Formatter().Serialize
	(
		std::make_any<std::reference_wrapper<const GpLogChain>>(logChain),
		dataWriter
	);

	dataWriter.ShrinkToFit();

	std::cout << GpSpanPtrByteR(iTmpBuffer).AsStringView();
	std::cout.flush();
}

void	GpLogConsumerConsole::OnFlush (void) noexcept
{
	std::cout.flush();
}

}//namespace GPlatform
