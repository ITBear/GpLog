TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 0
VER_MIN		    = 1
VER_PAT		    = 0
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=8176e0bd-42b4-4679-8a7e-95985e001e73
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
DEFINES		   += GP_LOG_GRAYLOG_LIBRARY
PACKET_NAME     = GpLogGraylog
DIR_LEVEL       = ./../..

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
    GpLogConsumerGraylogFactory.cpp

HEADERS += \
    GpLogConsumerGraylog.hpp \
    GpLogConsumerGraylogConfigDesc.hpp \
    GpLogConsumerGraylogFactory.hpp \
    GpLogGraylog.hpp \
    GpLogGraylog_global.hpp
