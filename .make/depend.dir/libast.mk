DEPEND_TARGETS += libast.recursive
ECHO_TARGETS += libast.echo
libast.recursive:
	@echo SUPER_MAKE_DIR=/Users/lidali/alpine/libraries/libes/               >> /Users/lidali/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/Users/lidali/alpine/libraries/libes/.make >> /Users/lidali/alpine/libraries/libast/.make/super
	cd /Users/lidali/alpine/libraries/libast/ && /Applications/Xcode.app/Contents/Developer/usr/bin/make recursive && /Applications/Xcode.app/Contents/Developer/usr/bin/make install
	-rm /Users/lidali/alpine/libraries/libast/.make/super
libast.echo:
	@echo SUPER_MAKE_DIR=/Users/lidali/alpine/libraries/libes/               >> /Users/lidali/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/Users/lidali/alpine/libraries/libes/.make >> /Users/lidali/alpine/libraries/libast/.make/super
	cd /Users/lidali/alpine/libraries/libast/ && /Applications/Xcode.app/Contents/Developer/usr/bin/make echo
	-rm /Users/lidali/alpine/libraries/libast/.make/super
