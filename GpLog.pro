TEMPLATE = subdirs

os_linux {
	SUBDIRS += \
		./GpLogCore \
		./GpLogGraylog
} else:os_android {
	SUBDIRS += \
		./GpLogCore \
		./GpLogGraylog
} else:os_ios {
	SUBDIRS += \
		./GpLogCore \
		./GpLogGraylog
} else:os_windows {
	SUBDIRS += \
		./GpLogCore \
		./GpLogGraylog
} else:os_macx {
	SUBDIRS += \
		./GpLogCore \
		./GpLogGraylog
} else:os_browser {
	SUBDIRS +=
} else {
    error("Unknown OS")
}

CONFIG += ordered
