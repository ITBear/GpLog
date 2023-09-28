TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 0
VER_MIN		    = 1
VER_PAT		    = 0
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=2b0b8014-10cc-4d14-9adf-b9a43193003b
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
DEFINES		   += GP_LOG_CORE_LIBRARY
PACKET_NAME     = GpLogCore
DIR_LEVEL       = ./../..

include(../../../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
}

os_linux{
}
#------------------------------- LIBS END ----------------------------------

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
    GpLogCore_global.hpp \
    GpLogExecutor.hpp \
    GpLogLevel.hpp \
    GpLogMarkTS.hpp \
    GpLogMarkTraceTS.hpp \
    GpLogMode.hpp \
    GpLogQueue.hpp \
    GpLogRunnable.hpp
