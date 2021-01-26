
QT = core

CONFIG(release,debug|release):TARGET = myprojectplugin
CONFIG(debug,debug|release):TARGET = myprojectplugind
TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$PWD/_bin

unix:LIBS += -ldl
win32:LIBS += -lole32 -loleaut32

HEADERS += \
	src/MyProject.h \
	src/MyProjectInterface.h \
	src/MyProjectPlugin.h
SOURCES += \
	src/MyProject.cpp \
	src/MyProjectInterface.cpp \
	src/MyProjectPlugin.cpp

DISTFILES += \
	myprojectplugin.json
