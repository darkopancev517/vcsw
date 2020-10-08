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
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -Wno-shadow -Wno-format -Wno-old-style-declaration")
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

#set(WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_SRCS)

#set(WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_NAS_SRCS)

#set(WISUN_MAIN_SYSTEM_DRIVER_SRCS)

#set(WISUN_MAIN_SYSTEM_MAIN_SRCS)

#set(WISUN_MAIN_SYSTEM_MISC_SRCS)

#set(WISUN_MAIN_SYSTEM_SECURITY_WOFLSSL_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_CONFIG_TOOL_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_SHELL_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VC_FORWARDER_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VC_QGDWUART_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SHELL_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VC_TIMERUART_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_COAP_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_DLMS_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_QGDW_1376_2_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_SLIP_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_TELNETD_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_COAP_RESOURCE_SRCS)

#set(WISUN_MAIN_SYSTEM_UTILS_ATCMD_SRCS)

#set(WISUN_MAIN_APPS_SRCS)

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

#add_library(wisun_main_system_core_net_wisun_sec STATIC ${WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_SRCS})
#set_target_properties(wisun_main_system_core_net_wisun_sec PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_core_net_wisun_sec_nas STATIC ${WISUN_MAIN_SYSTEM_CORE_NET_WISUN_SEC_NAS_SRCS})
#set_target_properties(wisun_main_system_core_net_wisun_sec_nas PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_driver STATIC ${WISUN_MAIN_SYSTEM_DRIVER_SRCS})
#set_target_properties(wisun_main_system_driver PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_main STATIC ${WISUN_MAIN_SYSTEM_MAIN_SRCS})
#set_target_properties(wisun_main_system_main PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_misc STATIC ${WISUN_MAIN_SYSTEM_MISC_SRCS})
#set_target_properties(wisun_main_system_misc PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_security_wolfssl STATIC ${WISUN_MAIN_SYSTEM_SECURITY_WOFLSSL_SRCS})
#set_target_properties(wisun_main_system_security_wolfssl PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_config_tool STATIC ${WISUN_MAIN_SYSTEM_UTILS_CONFIG_TOOL_SRCS})
#set_target_properties(wisun_main_system_utils_config_tool PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_shell STATIC ${WISUN_MAIN_SYSTEM_UTILS_SHELL_SRCS})
#set_target_properties(wisun_main_system_utils_shell PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vc_forwarder STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_FORWARDER_SRCS})
#set_target_properties(wisun_main_system_utils_vc_forwarder PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vc_qgdwuart STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_QGDWUART_SRCS})
#set_target_properties(wisun_main_system_utils_vc_qgdwuart PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vc_sysresal STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SRCS})
#set_target_properties(wisun_main_system_utils_vc_sysresal PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vc_sysresal_shell STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_SYSRESAL_SHELL_SRCS})
#set_target_properties(wisun_main_system_utils_vc_sysresal_shell PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vc_timeruart STATIC ${WISUN_MAIN_SYSTEM_UTILS_VC_TIMERUART_SRCS})
#set_target_properties(wisun_main_system_utils_vc_timeruart PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vertexcom_coap STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_COAP_SRCS})
#set_target_properties(wisun_main_system_utils_vertexcom_coap PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vertexcom_dlms STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_DLMS_SRCS})
#set_target_properties(wisun_main_system_utils_vertexcom_dlms PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vertexcom_qgdw_1376_2 STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_QGDW_1376_2_SRCS})
#set_target_properties(wisun_main_system_utils_vertexcom_qgdw_1376_2 PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_vertexcom_slip STATIC ${WISUN_MAIN_SYSTEM_UTILS_VERTEXCOM_SLIP_SRCS})
#set_target_properties(wisun_main_system_utils_vertexcom_slip PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_telnetd STATIC ${WISUN_MAIN_SYSTEM_UTILS_TELNETD_SRCS})
#set_target_properties(wisun_main_system_utils_telnetd PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_unittest_framework STATIC ${WISUN_MAIN_SYSTEM_UTILS_UNITTEST_FRAMEWORK_SRCS})
#set_target_properties(wisun_main_system_utils_unittest_framework PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_coap_resource STATIC ${WISUN_MAIN_SYSTEM_UTILS_COAP_RESOURCE_SRCS})
#set_target_properties(wisun_main_system_utils_coap_resource PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_system_utils_atcmd STATIC ${WISUN_MAIN_SYSTEM_UTILS_ATCMD_SRCS})
#set_target_properties(wisun_main_system_utils_atcmd PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

#add_library(wisun_main_apps STATIC ${WISUN_MAIN_APPS_SRCS})
#set_target_properties(wisun_main_apps PROPERTIES COMPILE_FLAGS ${WISUN_MAIN_CFLAGS})

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
)

add_dependencies(PLATFORM_LIBS ${PLATFORM_LIBS_list})

target_link_libraries(PLATFORM_LIBS -Wl,--whole-archive ${PLATFORM_LIBS_list} -Wl,--no-whole-archive)
