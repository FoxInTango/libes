DEPEND_TARGETS += libast.recursive
ECHO_TARGETS += libast.echo
libast.recursive:
	@echo SUPER_MAKE_DIR=/volumes/llama/home/alpine/libraries/libes/               >> /volumes/llama/home/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/volumes/llama/home/alpine/libraries/libes/.make >> /volumes/llama/home/alpine/libraries/libast/.make/super
	cd /volumes/llama/home/alpine/libraries/libast/ && make recursive && make install
	-rm /volumes/llama/home/alpine/libraries/libast/.make/super
libast.echo:
	@echo SUPER_MAKE_DIR=/volumes/llama/home/alpine/libraries/libes/               >> /volumes/llama/home/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/volumes/llama/home/alpine/libraries/libes/.make >> /volumes/llama/home/alpine/libraries/libast/.make/super
	cd /volumes/llama/home/alpine/libraries/libast/ && make echo
	-rm /volumes/llama/home/alpine/libraries/libast/.make/super
