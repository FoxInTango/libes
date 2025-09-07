DEPEND_TARGETS += libast.recursive
ECHO_TARGETS += libast.echo
libast.recursive:
	@echo SUPER_MAKE_DIR=/home/lidali/alpine/libraries/libes/               >> /home/lidali/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/home/lidali/alpine/libraries/libes/.make >> /home/lidali/alpine/libraries/libast/.make/super
	cd /home/lidali/alpine/libraries/libast/ && make recursive && make install
	-rm /home/lidali/alpine/libraries/libast/.make/super
libast.echo:
	@echo SUPER_MAKE_DIR=/home/lidali/alpine/libraries/libes/               >> /home/lidali/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/home/lidali/alpine/libraries/libes/.make >> /home/lidali/alpine/libraries/libast/.make/super
	cd /home/lidali/alpine/libraries/libast/ && make echo
	-rm /home/lidali/alpine/libraries/libast/.make/super
