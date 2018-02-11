deps_config := \
	/home/lhb/lhb/esp32/example/esp-idf/components/app_trace/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/aws_iot/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/bt/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/esp32/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/ethernet/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/fatfs/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/freertos/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/heap/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/libsodium/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/log/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/lwip/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/mbedtls/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/openssl/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/pthread/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/spi_flash/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/spiffs/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/tcpip_adapter/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/wear_levelling/Kconfig \
	/home/lhb/lhb/esp32/example/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/lhb/lhb/esp32/example/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/lhb/lhb/esp32/example/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/lhb/lhb/esp32/example/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
