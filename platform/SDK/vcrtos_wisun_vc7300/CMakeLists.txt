cmake_minimum_required (VERSION 3.5)
SET(CMAKE_SYSTEM_NAME Generic)

ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR})

#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/include)
#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/include/cmsis)
#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source)
#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius)

#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/include)
#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source)

#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos)
#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/porting/wisun)
#ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/porting/mbed-client-pal)

set(WISUN_COMMON_CFLAGS "-include ${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/autoconf.h")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -include ${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/param.h")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -Wall -Werror -Wno-missing-field-initializers -Wno-pragmas -Wno-pointer-sign -Wno-switch")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -Wno-type-limits -Wno-unused-parameter -Wno-sign-compare -Wno-logical-op")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -Wno-shadow -Wno-format -Wno-old-style-declaration -Wno-empty-body")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -std=gnu99 -fno-delete-null-pointer-checks -fno-peephole2")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -fno-strict-aliasing -fshort-enums")

set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common")

if (CONFIG_BOARD_vc7300BMTR)
set(WISUN_BOARD vc7300BMTR)
endif()

if (CONFIG_RADIO_centauriB3)
set(WISUN_RADIO centauriB3)
endif()

set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/${WISUN_BOARD}")

set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/ARM/cmsis")

set(WISUN_BOOTLOADER_CFLAGS "${WISUN_COMMON_CFLAGS} -Wno-unused-variable -Wno-unused-but-set-variable")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/xmodem")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/easylzma/src")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/easylzma/src/easylzma")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/easylzma/src/pavlov")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -DMCU_USE_VC7300A")
if (CONFIG_BOARD_vc7300BMTR)
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -DBOARD_USE_VC7300BMTR")
endif()
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -DRADIO_USE_CENTAURIB3")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -DSYSTEM_USE_CONTIKI")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -USOC_DEBUG")
set(WISUN_BOOTLOADER_CFLAGS "${WISUN_BOOTLOADER_CFLAGS} -DHAL_UART_SEND_NO_TIMEOUT")


set(WISUN_BOOTLOADER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/system.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/tick.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/xmodem/xmodem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/easylzma/src/lzma_header.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/easylzma/src/pavlov/Alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/bootloader/easylzma/src/pavlov/LzmaDec.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common/crc16_ccitt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common/spi_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common/urque.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcana.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vccrypt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcdma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcgpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vci2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vciso7816.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vckeyscan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcmisc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcnvic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcpmu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcpwm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcrtc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcsfio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcsystick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vctim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcuart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcwdt.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_ota.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_spiflash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_spisram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_nvic.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/ARM/startup/vc7300a_bootloader.s
)

set(WISUN_MAIN_CFLAGS "${WISUN_COMMON_CFLAGS}")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DMCU_USE_VC7300A")
if (CONFIG_BOARD_vc7300BMTR)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DBOARD_USE_VC7300BMTR")
endif()
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DRADIO_USE_CENTAURIB3")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DPLC_USE_UNKNOWN")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DSYSTEM_USE_CONTIKI")

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DSW_VERSION=0xdeadbeef")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DSW_DATE=0xdeadbeef")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DSW_TIME=0xdeadbeef")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DSW_BRANCH=abcd")

if (CONFIG_RADIO_centauriB3)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/centauriB3")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/centauriB3/firmware")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/centauriB3/firmware/phy")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCSR_ACCESS=")
endif()

if (CONFIG_BUILD_APP_vcapps)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/apps/vcapps")
endif()

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/config")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver")

if (CONFIG_RADIO_centauriB3)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/centauriB3")
endif()

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/main")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/misc")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/dev")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/llsec")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rime")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/loader")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI=1")

if (CONFIG_BOARD_vc7300BMTR)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI_TARGET_vc7300BMTR=1")
endif()

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DAUTOSTART_ENABLE")

# core/net/wisun
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DNETSTACK_CONF_WITH_WISUN=1")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun")

# security/wolfssl
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DWOLFSSL_USER_SETTINGS")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/IDE/GCC-ARM/Header")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -Wno-cpp -Wno-unused-variable -Wno-format")

if (CONFIG_CONTIKI_WITH_IPV6)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DNETSTACK_CONF_WITH_IPV6=1")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/multicast")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip")
endif()

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI_CONF_WITH_VCAPP=1")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI_CONF_WITH_SHELL=1")

# system util apps

# config tool
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool")

# shell
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/core")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands")

# vc_forwarder
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_forwarder")

# vc_QgdwUart
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_QgdwUart")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_qgdw")

# vc_sysResAL
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL_evHandler")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL_shell")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL_shell/res/shellCmd")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_sysResAL")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_sysResAL/vc_sysResAL_evHandler")

# vc_timerUart
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_timerUart")

# vertexcom_coap
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vertexcom_coap")

# vertexcom_dlms
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_dlms")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vertexcom_dlms")

# vertexcom_qgdw_1376_2
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2")

# vertexcom_slip
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_slip")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vertexcom_slip")

# telnetd
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/telnetd")

# unit_test_framework
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework")

# common vcapps related include directories
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res")

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_sysResAL")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_timerUart")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vertexcom_slip")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vertexcom_dlms")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_qgdw")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_sysResAL/vc_sysResAL_evHandler")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vc_pktHandler")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/include/middleware/vc_lib/vertexcom_coap")

set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DPROJECT_CONF_H='\"vc_projectConf.h\"'")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DUSE_CONFIG_TOOL")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI_WITH_VMEM=1")
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI_WITH_VC_APP_REAPP=1")

if (CONFIG_CONTIKI_WITH_COAP)
set(WISUN_MAIN_CFLAGS "${WISUN_MAIN_CFLAGS} -DCONTIKI_CONF_WITH_VC_APP_COAPHANDLER=1")
endif()

set(WISUN_MAIN_MCU_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common/crc16_ccitt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common/spi_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common/urque.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcana.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vccrypt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcdma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcgpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vci2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vciso7816.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vckeyscan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcmisc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcnvic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcpmu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcpwm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcrtc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcsfio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcsystick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vctim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcuart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph/vcwdt.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_ota.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_spiflash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_spisram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_nvic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_crypto.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_dying_gasp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_cmp_cnt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_event.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_nvic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_misc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_pmu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_pwm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_systick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_wdt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal/hal_rtc.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/ARM/startup/vc7300a_main.s
)

set(WISUN_MAIN_BOARD_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/backtrace.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/board.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/debug-io.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/err_dump.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/extheap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/heap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/i2c_eeprom.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/instrument.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/interrupt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/radio_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/system.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/common/uart.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/lfs/lfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/lfs/lfs_util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/lfs/vc_lfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/lfs/vc_lfs_heap.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/${WISUN_BOARD}/debug-io.c
)

set(WISUN_MAIN_RADIO_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/radio.c
)

set(WISUN_MAIN_RADIO_FIRMWARE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_cfg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_cmd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_mac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_prober.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/centauri_timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/cmdlog.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/vtprober.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/phy/phy_irq_fix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/phy/TransceiverCsr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/phy/TransceiverFun.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/phy/TransceiverInit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/radio/${WISUN_RADIO}/firmware/phy/TransceiverMain.c
)

set(WISUN_MAIN_SYSTEM_COMMON_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/version.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/shell.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/cmdhist.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_centauri.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_sysinfo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_fault.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_lfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_platform.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_prober.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_tool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/shell_commands.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/argpars.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/getopt_r.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/ablend.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/ber.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/dbgflg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/hop.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/romchk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/centrgchk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/stress.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/physta.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/ptngen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/sq.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/scope.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/trav.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/stuck.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/rfvnt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/prcssvnt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/topcmd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/chkfrm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/phyregrdtst.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/ber/udpsnd.c
)

if (CONFIG_DEBUG_PKTLEN)
list(APPEND WISUN_MAIN_SYSTEM_COMMON_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/diag/dpktlen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/diag/dmem.c
)
endif()

if (CONFIG_DIAG_IC_TEST)
list(APPEND WISUN_MAIN_SYSTEM_COMMON_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_iso7816.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_pwm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_pmu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_rtc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_sdio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/common/shell/commands/sc_ictest.c
)
endif()

set(WISUN_MAIN_SYSTEM_CORE_SYS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/arg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/autostart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/compower.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/ctimer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/energest.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/etimer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/mt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/process.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/procinit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/rtimer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/stimer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/sys/timer.c
)

set(WISUN_MAIN_SYSTEM_CORE_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/aes-128.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/assert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/ccm-star.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/crc16.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/gcr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/ifft.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/hash_list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/me.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/me_tabs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/memb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/mmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/vmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/petsciiconv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/print-stats.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/random.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/ringbuf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/ringbuf16.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/ringbufindex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/sensors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/settings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/trickle-timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/bitmap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/lib/base64.c
)

set(WISUN_MAIN_SYSTEM_CORE_NET_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/link-stats.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/linkaddr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/nbr-table.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/net-debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/netstack.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/packetbuf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/queuebuf.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/llsec/nullsec.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac/frame802154.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac/frame802154e-ie.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac/framer-802154.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac/mac.c
)

if (NOT CONFIG_CONTIKI_WITH_WISUN_MAC)
list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac/csma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/mac/nullrdc.c
)
endif()

if (CONFIG_CONTIKI_WITH_IPV6)

if (CONFIG_UIP_CONF_TCP)
list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip/tcp-socket.c
)
endif()

list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip/tcpip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip/udp-socket.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip/uip-debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip/uip-udp-packet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ip/uiplib.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/sicslowpan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/uip-ds6-nbr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/uip-ds6-route.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/uip-ds6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/uip-icmp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/uip-nd6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/uip6.c
)

if (CONFIG_CONTIKI_WITH_MPL)
list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/ipv6/multicast/mpl-wisun.c
)
endif()

list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-dag-root.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-dag.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-ext-header.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-icmp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-mrhof.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-nbr-policy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-ns.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl-timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/rpl/rpl.c
)

endif() # if (CONFIG_CONTIKI_WITH_IPV6)



set(WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/ntp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/dh1cf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/framewisun-ie.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun-packet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisunrdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun-state.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/framer-wisun.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/lookup3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun-mac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun-queue.c
)

if (CONFIG_WISUN_DUAL_MODE)
list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun_dual.c
)
endif()

list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/dhcp6c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/dhcp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/dhcp6r.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun-rpl.c
)

if (CONFIG_WISUN_ROOT)
list(APPEND WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/dhcp6s.c
)
endif()

set(WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/sec_other.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/eapol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/eapol_key.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/eapol_eap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/eapol_relay.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun_sec.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun_crypt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/wisun_tls.c
)

set(WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_NAS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/nas.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/core/net/wisun/md5.c
)

set(WISUN_MAIN_SYSTEM_DRIVER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/clock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/ethernet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/log_output.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/node-id.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/rtimer-arch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/sq_process.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/topcmd_process.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/trav_process.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/uart-meter-arch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/uart-txdma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/vc_sniffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/vcshell-iface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/watchdog.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/${WISUN_RADIO}/adap_cca.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/driver/${WISUN_RADIO}/contiki-radio.c
)

set(WISUN_MAIN_SYSTEM_MAIN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/main/vc_main.c
)

set(WISUN_MAIN_SYSTEM_MISC_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/misc/sys_hook.c
)

set(WISUN_MAIN_SYSTEM_SECURITY_WOFLSSL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/bio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/crl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/internal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/keys.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/ocsp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/sniffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/ssl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/tls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/tls13.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/src/wolfio.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/aes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/arc4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/asm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/asn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/async.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/blake2b.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/camellia.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/chacha.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/chacha20_poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/cmac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/coding.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/compress.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/cpuid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/curve25519.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/des3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/dh.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/dsa.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/ecc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/ecc_fp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/ed25519.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/error.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/evp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/fe_low_mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/fe_operations.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/ge_low_mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/ge_operations.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/hash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/hc128.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/hmac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/idea.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/integer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/logging.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/md2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/md4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/md5.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/misc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/pkcs12.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/pkcs7.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/pwdbased.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/rabbit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/random.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/ripemd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/rsa.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/sha.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/sha256.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/sha3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/sha512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/signature.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/sp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/srp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/tfm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/wc_encrypt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/wc_port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/wolfevent.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/security/wolfssl-3.13.0/wolfcrypt/src/wolfmath.c
)

set(WISUN_MAIN_SYSTEM_UTILS_CONFIG_TOOL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_csma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_rpl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_wisun.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_dhcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_sys.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_sec.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_filter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_mpl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/shell_config.c
)

if (CONFIG_WISUN_DUAL_MODE)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_CONFIG_TOOL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/config_tool/config_tool_dualmode.c
)
endif()

set(WISUN_MAIN_SYSTEM_UTILS_SHELL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/netstack_shell_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/core/shell.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/core/serial-shell.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-ps.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-ping6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-coap-gen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-led.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-rpl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-nbr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-msend.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-udp-gen.c
)

if (CONFIG_WISUN_ROOT)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_SHELL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-pntest_tool.c
)
endif()

if (CONFIG_UIP_CONF_TCP)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_SHELL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/shell/commands/shell-tcp-gen.c
)
endif()

set(WISUN_MAIN_SYSTEM_UTILS_VC_FORWARDER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_forwarder/vc_forwarder.c
)

set(WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/res/sysResRpl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/res/sysResLinkStats.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/res/sysResPlatInfo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/res/sysResIpv6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/res/sysResNet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL_evHandler/vc_sysResAL_evHandler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL_evHandler/res/evHandler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/vc_sysResAL_mem/vc_sysResAL_mem.c
)

if (CONFIG_WISUN_ROOT)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_sysResAL/res/sysResDhcp6.c
)
endif()

set(WISUN_MAIN_SYSTEM_UTILS_VC_TIMERUART_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vc_timerUart/vc_timerUart.c
)

set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_COAP_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-observe.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-transactions.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-separate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-observe-client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-engine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/rest-engine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-res-well-known-core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_coap/er-coap-block1.c
)

set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_DLMS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_dlms/vertexcom_dlms.c
)

set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_QGDW_1376_2_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2/vertexcom_qgdw_contiki.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2/afn_qgdw1376_2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2/discovery.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2/fn_gdw1376_2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2/parse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_qgdw_1376_2/qgdw_adaption_layer.c
)

set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_SLIP_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/vertexcom_slip/vertexcom_slip.c
)

set(WISUN_MAIN_SYSTEM_UTILS_TELNETD_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/telnetd/telnetd.c
)

set(WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/vc_unittest.c
)

if (CONFIG_UNITTEST_DRIVER)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unittests/unittest_driver.c
)
endif()

if (CONFIG_UNITTEST_API)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unittests/unittest_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unit_test/unittest_timeruart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unit_test/unittest_udp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unit_test/unittest_tcp.c
)
endif()

if (CONFIG_UNITTEST_HAL)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unittests/unittest_hal.c
)
endif()

if (CONFIG_UNITTEST_WISUN)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unittests/unittest_wisun.c
)
endif()

if (CONFIG_UNITTEST_SYS_NET)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/unit_test_framework/unittests/unittest_sysnet.c
)
endif()

set(WISUN_MAIN_SYSTEM_UTILS_COAP_RESOURCE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdLinkTableNum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdLinkTable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdSysInfo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdPeripheralInfo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdEvHandler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdfwUpgrade.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdShellHandler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/vc_app_coapHandler.c
)

if (CONFIG_WISUN_ROOT)
list(APPEND WISUN_MAIN_SYSTEM_UTILS_COAP_RESOURCE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdJoinedTableNum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdJoinedTable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdRoutingTableNum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdRoutingTable.c
)
else()
list(APPEND WISUN_MAIN_SYSTEM_UTILS_COAP_RESOURCE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/coap_resource/res/vcCmdParentInfo.c
)
endif()

set(WISUN_MAIN_SYSTEM_UTILS_ATCMD_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/at_command/atcmd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/at_command/atcmd_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/system/contiki/utils/at_command/atcmd_res.c
)

if (CONFIG_BUILD_APP_vcapps)
set(WISUN_MAIN_APPS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/apps/vcapps/vcapps.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wisun/apps/vcapps/ws_customer_certs.c
)
endif()

#set(VCDRIVERS_COMMON_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/stdiobase.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/syscalls.c
#)

#set(VCDRIVERS_CPU_PERIPH_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius/cpu.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius/vectors.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius/periph/gpio.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius/periph/irq.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius/periph/tim.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcdrivers/source/sirius/periph/uart.c
#)

#set(VCRTOS_CORE_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/instance.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/msg.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/mutex.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/thread.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/rmutex.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/sema.c
#)

#set(VCRTOS_CORE_API_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/instance_api.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/msg_api.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/mutex_api.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/mutex_timeout_api.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/thread_api.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/event_api.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/core/api/heap_api.cpp
#)

#set(VCRTOS_UTILS_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/utils/isrpipe.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/utils/ringbuffer.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/utils/heap.cpp
#)

#set(VCRTOS_CLI_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/cli/cli.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/cli/cli_uart.cpp
#)

#set(VCRTOS_ZTIMER_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/ztimer/core.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/ztimer/overhead.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos/source/ztimer/util.c
#)

#set(PORTING_VCRTOS_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/cortexm.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/cpu_arch.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/kernel_init.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/stdiobase_arch.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/thread_arch.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/commands.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/ztimer_periph.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/assert_failure.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/porting/vcrtos/simple_malloc.c
#)

#add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
#add_definitions(-DVCRTOS_PROJECT_CONFIG_FILE="vcrtos-project-config.h")
#add_definitions(-DVCRTOS_VERSION="${VCSOFTWARE_OS_VER}")

#add_library(vcdrivers_common STATIC ${VCDRIVERS_COMMON_SRCS})
#add_library(vcdrivers_cpu_periph STATIC ${VCDRIVERS_CPU_PERIPH_SRCS})
#add_library(vcrtos_core STATIC ${VCRTOS_CORE_SRCS})
#add_library(vcrtos_core_api STATIC ${VCRTOS_CORE_API_SRCS})
#add_library(vcrtos_utils STATIC ${VCRTOS_UTILS_SRCS})
#add_library(vcrtos_cli STATIC ${VCRTOS_CLI_SRCS})
#add_library(vcrtos_ztimer STATIC ${VCRTOS_ZTIMER_SRCS})
#add_library(porting_vcrtos STATIC ${PORTING_VCRTOS_SRCS})

add_library(wisun_main_mcu STATIC ${WISUN_MAIN_MCU_SRCS})
set_target_properties(wisun_main_mcu PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_board STATIC ${WISUN_MAIN_BOARD_SRCS})
set_target_properties(wisun_main_board PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_radio STATIC ${WISUN_MAIN_RADIO_SRCS})
set_target_properties(wisun_main_radio PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_radio_firmware STATIC ${WISUN_MAIN_RADIO_FIRMWARE_SRCS})
set_target_properties(wisun_main_radio_firmware PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_common STATIC ${WISUN_MAIN_SYSTEM_COMMON_SRCS})
set_target_properties(wisun_main_system_common PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_core_sys STATIC ${WISUN_MAIN_SYSTEM_CORE_SYS_SRCS})
set_target_properties(wisun_main_system_core_sys PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_core_lib STATIC ${WISUN_MAIN_SYSTEM_CORE_LIB_SRCS})
set_target_properties(wisun_main_system_core_lib PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_core_net STATIC ${WISUN_MAIN_SYSTEM_CORE_NET_SRCS})
set_target_properties(wisun_main_system_core_net PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_core_net_wisun STATIC ${WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SRCS})
set_target_properties(wisun_main_system_core_net_wisun PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

if (CONFIG_CONTIKI_WITH_WISUN_SECURITY)
add_library(wisun_main_system_core_net_wisun_sec STATIC ${WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_SRCS})
set_target_properties(wisun_main_system_core_net_wisun_sec PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})
if (CONFIG_CONTIKI_WITH_WISUN_NAS)
add_library(wisun_main_system_core_net_wisun_sec_nas STATIC ${WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_NAS_SRCS})
set_target_properties(wisun_main_system_core_net_wisun_sec_nas PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})
endif()
endif()

add_library(wisun_main_system_driver STATIC ${WISUN_MAIN_SYSTEM_DRIVER_SRCS})
set_target_properties(wisun_main_system_driver PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_main STATIC ${WISUN_MAIN_SYSTEM_MAIN_SRCS})
set_target_properties(wisun_main_system_main PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_misc STATIC ${WISUN_MAIN_SYSTEM_MISC_SRCS})
set_target_properties(wisun_main_system_misc PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

if (CONFIG_CONTIKI_WITH_WISUN_SECURITY)
add_library(wisun_main_system_security_wolfssl STATIC ${WISUN_MAIN_SYSTEM_SECURITY_WOFLSSL_SRCS})
set_target_properties(wisun_main_system_security_wolfssl PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})
endif()

add_library(wisun_main_system_utils_config_tool STATIC ${WISUN_MAIN_SYSTEM_UTILS_CONFIG_TOOL_SRCS})
set_target_properties(wisun_main_system_utils_config_tool PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_shell STATIC ${WISUN_MAIN_SYSTEM_UTILS_SHELL_SRCS})
set_target_properties(wisun_main_system_utils_shell PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vc_forwarder STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_FORWARDER_SRCS})
set_target_properties(wisun_main_system_utils_vc_forwarder PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vc_sysresal STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SRCS})
set_target_properties(wisun_main_system_utils_vc_sysresal PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vc_timeruart STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_TIMERUART_SRCS})
set_target_properties(wisun_main_system_utils_vc_timeruart PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vertexcom_coap STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_COAP_SRCS})
set_target_properties(wisun_main_system_utils_vertexcom_coap PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vertexcom_dlms STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_DLMS_SRCS})
set_target_properties(wisun_main_system_utils_vertexcom_dlms PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vertexcom_qgdw_1376_2 STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_QGDW_1376_2_SRCS})
set_target_properties(wisun_main_system_utils_vertexcom_qgdw_1376_2 PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_system_utils_vertexcom_slip STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_SLIP_SRCS})
set_target_properties(wisun_main_system_utils_vertexcom_slip PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

if (CONFIG_UIP_CONF_TCP)
add_library(wisun_main_system_utils_telnetd STATIC ${WISUN_MAIN_SYSTEM_UTILS_TELNETD_SRCS})
set_target_properties(wisun_main_system_utils_telnetd PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})
endif()

if (CONFIG_UNITTEST_FRAMEWORK)
add_library(wisun_main_system_utils_unittest_framework STATIC ${WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS})
set_target_properties(wisun_main_system_utils_unittest_framework PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})
endif()

if (CONFIG_CONTIKI_WITH_COAP)
add_library(wisun_main_system_utils_coap_resource STATIC ${WISUN_MAIN_SYSTEM_UTILS_COAP_RESOURCE_SRCS})
set_target_properties(wisun_main_system_utils_coap_resource PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})
endif()

add_library(wisun_main_system_utils_atcmd STATIC ${WISUN_MAIN_SYSTEM_UTILS_ATCMD_SRCS})
set_target_properties(wisun_main_system_utils_atcmd PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

add_library(wisun_main_apps STATIC ${WISUN_MAIN_APPS_SRCS})
set_target_properties(wisun_main_apps PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

set(PLATFORM_LIBS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy.c
)

add_library(PLATFORM_LIBS STATIC ${PLATFORM_LIBS_SRCS})

set(PLATFORM_BOOTLOADER_LIBS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy.c
)

add_library(PLATFORM_BOOTLOADER_LIBS STATIC ${PLATFORM_BOOTLOADER_LIBS_SRCS})

add_library(wisun_bootloader STATIC ${WISUN_BOOTLOADER_SRCS})
set_target_properties(wisun_bootloader PROPERTIES COMPILE_FLAGS ${WISUN_BOOTLOADER_CFLAGS})

set(PLATFORM_BOOTLOADER_LIBS_list
    wisun_bootloader
)

add_dependencies(PLATFORM_BOOTLOADER_LIBS ${PLATFORM_BOOTLOADER_LIBS_list})

target_link_libraries(PLATFORM_BOOTLOADER_LIBS -Wl,--whole-archive ${PLATFORM_BOOTLOADER_LIBS_list} -Wl,--no-whole-archive)

set(PLATFORM_LIBS_list
    wisun_main_mcu
    wisun_main_board
    wisun_main_radio
    wisun_main_radio_firmware
    wisun_main_system_common
    wisun_main_system_core_sys
    wisun_main_system_core_lib
    wisun_main_system_core_net
    wisun_main_system_core_net_wisun
    wisun_main_system_driver
    wisun_main_system_main
    wisun_main_system_misc
    wisun_main_system_utils_config_tool
    wisun_main_system_utils_shell
    wisun_main_system_utils_vc_forwarder
    wisun_main_system_utils_vc_sysresal
    wisun_main_system_utils_vc_timeruart
    wisun_main_system_utils_vertexcom_coap
    wisun_main_system_utils_vertexcom_dlms
    wisun_main_system_utils_vertexcom_qgdw_1376_2
    wisun_main_system_utils_vertexcom_slip
    wisun_main_system_utils_atcmd
    wisun_main_apps
)

if (CONFIG_CONTIKI_WITH_COAP)
list(APPEND PLATFORM_LIBS_list
    wisun_main_system_utils_coap_resource
)
endif()

if (CONFIG_UNITTEST_FRAMEWORK)
list(APPEND PLATFORM_LIBS_list
    wisun_main_system_utils_unittest_framework
)
endif()

if (CONFIG_UIP_CONF_TCP)
list(APPEND PLATFORM_LIBS_list
    wisun_main_system_utils_telnetd
)
endif()

if (CONFIG_CONTIKI_WITH_WISUN_SECURITY)
list(APPEND PLATFORM_LIBS_list
    wisun_main_system_core_net_wisun_sec
    wisun_main_system_security_wolfssl
)
if (CONFIG_CONTIKI_WITH_WISUN_NAS)
list(APPEND PLATFORM_LIBS_list
    wisun_main_system_core_net_wisun_sec_nas
)
endif()
endif()

add_dependencies(PLATFORM_LIBS ${PLATFORM_LIBS_list})

target_link_libraries(PLATFORM_LIBS -Wl,--whole-archive ${PLATFORM_LIBS_list} -Wl,--no-whole-archive)
