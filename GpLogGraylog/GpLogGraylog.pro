TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 2
VER_MIN		    = 1
VER_PAT		    = 4
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=8176e0bd-42b4-4679-8a7e-95985e001e73
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
PACKET_NAME     = GpLogGraylog
DIR_LEVEL       = ./../..

DEFINES		   += GP_LOG_GRAYLOG_LIBRARY
DEFINES        += "GP_CURRENT_LIB_VER_MAJ=\\\"$$VER_MAJ\\\""
DEFINES        += "GP_CURRENT_LIB_VER_MIN=\\\"$$VER_MIN\\\""
DEFINES        += "GP_CURRENT_LIB_VER_PAT=\\\"$$VER_PAT\\\""
DEFINES        += "GP_CURRENT_LIB_PACKET_NAME=\\\"$$PACKET_NAME\\\""

include(../../../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
}

os_linux{
}
#------------------------------- LIBS END ----------------------------------

SOURCES += \
    GpLogConsumerGraylog.cpp \
    GpLogConsumerGraylogConfigDesc.cpp \
    GpLogConsumerGraylogFactory.cpp \
    GpLogGraylog.cpp

HEADERS += \
    GpLogConsumerGraylog.hpp \
    GpLogConsumerGraylogConfigDesc.hpp \
    GpLogConsumerGraylogFactory.hpp \
    GpLogGraylog.hpp \
    GpLogGraylog_global.hpp
