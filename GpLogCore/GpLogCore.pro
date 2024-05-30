# ----------- Config -----------
TEMPLATE        = lib
#CONFIG        += staticlib
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=2b0b8014-10cc-4d14-9adf-b9a43193003b
PACKET_NAME     = GpLogCore
DEFINES        += GP_LOG_CORE_LIBRARY
_VER_MAJ        = 2
_VER_MIN        = 1
_VER_PAT        = 5
DIR_LEVEL       = ./../..

include($$DIR_LEVEL/../QtGlobalPro.pri)

# ----------- Libraries -----------
os_windows{
	LIBS += -lGpReflection$$TARGET_POSTFIX
	LIBS += -lGpUtils$$TARGET_POSTFIX
}

os_linux{
}

# ----------- Sources and headers -----------
SOURCES += \
    Config/GpLogConfigDesc.cpp \
    Consumers/Console/GpLogConsumerConsole.cpp \
    Consumers/Console/GpLogConsumerConsoleConfigDesc.cpp \
    Consumers/Console/GpLogConsumerConsoleFactory.cpp \
    Consumers/Console/GpLogConsumersFactoryProcessorConsole.cpp \
    Consumers/File/GpLogConsumerFile.cpp \
    Consumers/File/GpLogConsumerFileConfigDesc.cpp \
    Consumers/File/GpLogConsumerFileFactory.cpp \
    Consumers/File/GpLogConsumersFactoryProcessorFile.cpp \
    Consumers/GpLogConsumerConfigDesc.cpp \
    Consumers/GpLogConsumersFactory.cpp \
    Elements/GpLogElementMsgMarkTraceTS.cpp \
    Elements/GpLogElementMsgStr.cpp \
    Elements/GpLogElementMsgStrFn.cpp \
    Formatters/Text/GpLogFormatterText.cpp \
    Formatters/Text/GpLogFormatterTextFactory.cpp \
    GpLog.cpp \
    GpLogCoreLib.cpp \
    GpLogExecutor.cpp \
    GpLogLevel.cpp \
    GpLogMode.cpp \
    GpLogQueue.cpp \
    GpLogRunnable.cpp

HEADERS += \
    Config/GpLogConfigDesc.hpp \
    Consumers/Console/GpLogConsumerConsole.hpp \
    Consumers/Console/GpLogConsumerConsoleConfigDesc.hpp \
    Consumers/Console/GpLogConsumerConsoleFactory.hpp \
    Consumers/Console/GpLogConsumersFactoryProcessorConsole.hpp \
    Consumers/File/GpLogConsumerFile.hpp \
    Consumers/File/GpLogConsumerFileConfigDesc.hpp \
    Consumers/File/GpLogConsumerFileFactory.hpp \
    Consumers/File/GpLogConsumersFactoryProcessorFile.hpp \
    Consumers/GpLogConsumer.hpp \
    Consumers/GpLogConsumerConfigDesc.hpp \
    Consumers/GpLogConsumerFactory.hpp \
    Consumers/GpLogConsumers.hpp \
    Consumers/GpLogConsumersFactory.hpp \
    Consumers/GpLogConsumersFactoryProcessor.hpp \
    Elements/GpLogElement.hpp \
    Elements/GpLogElementMsg.hpp \
    Elements/GpLogElementMsgMarkTraceTS.hpp \
    Elements/GpLogElementMsgStr.hpp \
    Elements/GpLogElementMsgStrFn.hpp \
    Elements/GpLogElements.hpp \
    Formatters/GpLogFormatters.hpp \
    Formatters/Text/GpLogFormatterText.hpp \
    Formatters/Text/GpLogFormatterTextElementMsgMarkTraceTS.hpp \
    Formatters/Text/GpLogFormatterTextElementMsgStr.hpp \
    Formatters/Text/GpLogFormatterTextElementMsgStrFn.hpp \
    Formatters/Text/GpLogFormatterTextFactory.hpp \
    GpLog.hpp \
    GpLogChain.hpp \
    GpLogCore.hpp \
    GpLogCoreLib.hpp \
    GpLogCore_global.hpp \
    GpLogExecutor.hpp \
    GpLogLevel.hpp \
    GpLogMarkTS.hpp \
    GpLogMarkTraceTS.hpp \
    GpLogMode.hpp \
    GpLogQueue.hpp \
    GpLogRunnable.hpp
