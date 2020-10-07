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
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -Wno-shadow -Wno-format")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -std=gnu99 -fno-delete-null-pointer-checks -fno-peephole2")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -fno-strict-aliasing -fshort-enums")

if (CONFIG_BOARD_vc7300BMTR)
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/board/vc7300BMTR")
endif()

set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/common")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/periph")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/hal")
set(WISUN_COMMON_CFLAGS "${WISUN_COMMON_CFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/wisun/mcu/vc7300a/ARM/cmsis")

# WISUN bootloader ----------------------------------------------------------------------

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

# ---------------------------------------------------------------------------------------

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

#set(PLATFORM_LIBS_SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/dummy.c
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

#add_library(PLATFORM_LIBS STATIC ${PLATFORM_LIBS_SRCS})

set(PLATFORM_LIBS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy.c
)

add_library(PLATFORM_LIBS STATIC ${PLATFORM_LIBS_SRCS})

add_library(wisun_bootloader STATIC ${WISUN_BOOTLOADER_SRCS})
set_target_properties(wisun_bootloader PROPERTIES COMPILE_FLAGS ${WISUN_BOOTLOADER_CFLAGS})

set(PLATFORM_LIBS_list
    wisun_bootloader
)

add_dependencies(PLATFORM_LIBS ${PLATFORM_LIBS_list})

target_link_libraries(PLATFORM_LIBS -Wl,--whole-archive ${PLATFORM_LIBS_list} -Wl,--no-whole-archive)
