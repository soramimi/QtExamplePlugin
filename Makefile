


all:
	cd QtPluginGenerator; make

clean:
	rm _* -fr
	rm MyProjectPlugin/_* -fr
	cd QtPluginGenerator; make clean

install:
	cd QtPluginGenerator; make install
	rm /var/lib/soramimi.jp/MyProjectPlugin -fr
	mkdir -p /var/lib/soramimi.jp/
	cp -a MyProjectPlugin /var/lib/soramimi.jp/

