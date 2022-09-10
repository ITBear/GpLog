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
	error("Unknown OS. Set CONFIG+=... one of values: os_linux, os_android, os_ios, os_windows, os_macx, os_browser, os_baremetal")
}

CONFIG += ordered
