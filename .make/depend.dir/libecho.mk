DEPEND_TARGETS += libecho.build
ECHO_TARGETS += libecho.echo
libecho.build:
	@echo SUPER_MAKE_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/               >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/.make >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/.make/super
	cd /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/ && make && make install
	-rm /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/.make/super
libecho.echo:
	@echo SUPER_MAKE_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/               >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/.make >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/.make/super
	cd /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/ && make echo
	-rm /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libecho/.make/super
