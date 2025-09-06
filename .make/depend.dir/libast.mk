DEPEND_TARGETS += libast.recursive
ECHO_TARGETS += libast.echo
libast.recursive:
	@echo SUPER_MAKE_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/               >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/.make >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/.make/super
	cd /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/ && make recursive && make install
	-rm /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/.make/super
libast.echo:
	@echo SUPER_MAKE_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/               >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libes/.make >> /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/.make/super
	cd /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/ && make echo
	-rm /mnt/d/CORE_WEB_SYSTEM_WEB/alpine/libraries/libast/.make/super
