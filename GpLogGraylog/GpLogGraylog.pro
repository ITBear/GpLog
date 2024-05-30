# ----------- Config -----------
TEMPLATE        = lib
#CONFIG        += staticlib
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=8176e0bd-42b4-4679-8a7e-95985e001e73
PACKET_NAME     = GpLogGraylog
DEFINES        += GP_LOG_GRAYLOG_LIBRARY
_VER_MAJ        = 2
_VER_MIN        = 1
_VER_PAT        = 5
DIR_LEVEL       = ./../..

include($$DIR_LEVEL/../QtGlobalPro.pri)

# ----------- Libraries -----------
os_windows{
	LIBS += -lGpLogCore$$TARGET_POSTFIX
	LIBS += -lGpReflection$$TARGET_POSTFIX
	LIBS += -lGpUtils$$TARGET_POSTFIX
}

os_linux{
}

# ----------- Sources and headers -----------
SOURCES += \
    GpLogConsumerGraylog.cpp \
    GpLogConsumerGraylogConfigDesc.cpp \
    GpLogConsumerGraylogFactory.cpp \
    GpLogGraylogLib.cpp

HEADERS += \
    GpLogConsumerGraylog.hpp \
    GpLogConsumerGraylogConfigDesc.hpp \
    GpLogConsumerGraylogFactory.hpp \
    GpLogGraylogLib.hpp \
    GpLogGraylog_global.hpp
