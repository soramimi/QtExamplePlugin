

all:
	mkdir _build; cd _build; QT_SELECT=5 qmake ../QtPluginGenerator.pro; make -j8

clean:
	rm _bin -fr
	rm _build -fr

install:
	install _bin/QtPluginGenerator /usr/local/bin/
