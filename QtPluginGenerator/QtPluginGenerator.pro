
QT = core gui widgets
TEMPLATE = app
TARGET = QtPluginGenerator

DESTDIR = $$PWD/_bin

SOURCES += main.cpp \
	MainWindow.cpp \
	joinpath.cpp

FORMS += \
	MainWindow.ui

HEADERS += \
	MainWindow.h \
	joinpath.h
