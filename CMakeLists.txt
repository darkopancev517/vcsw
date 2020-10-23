include(CMakeForceCompiler)

cmake_minimum_required (VERSION 3.5)
set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR})
ADD_GLOBALDIR(${CMAKE_CURRENT_SOURCE_DIR}/source)

set(VCSOFTWARE_COMMON_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
)

if(VCSOFTWARE_SDK MATCHES vcrtos_wisun_vc7300)
    SET(VCRTOS_WISUN_BOOTLOADER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/source/dummy_bootloader.c)

    add_definitions(-DVCRTOS_PROJECT_CONFIG_FILE="vcrtos-project-config.h")
    add_definitions(-DVCRTOS_VERSION="${VCSOFTWARE_OS_VER}")

    CREATE_TEST_LIBRARY(vcrtos_wisun_bootloader "${VCRTOS_WISUN_BOOTLOADER_SRCS}" "")

    # wisun bootloader linker script preprocessing
    add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/vcrtos_wisun_bootloader.ld
        COMMAND ${CMAKE_C_COMPILER}
        -E -P ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/mcu/vc7300a/ARM/linker/vc7300a_bootloader.ld.S
        -include ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/include/autoconf.h
        -include ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/include/param.h
        -o ${PROJECT_BINARY_DIR}/vcrtos_wisun_bootloader.ld
        VERBATIM
    )
    add_custom_target(vcrtos_wisun_bootloader_linker ALL DEPENDS ${PROJECT_BINARY_DIR}/vcrtos_wisun_bootloader.ld)
    add_dependencies(vcrtos_wisun_bootloader PLATFORM_BOOTLOADER_LIBS vcrtos_wisun_bootloader_linker)
    target_link_libraries(vcrtos_wisun_bootloader PLATFORM_BOOTLOADER_LIBS)

    SET(VCRTOS_WISUN_MAIN_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/source/dummy_main.c)

    CREATE_TEST_LIBRARY(vcrtos_wisun_main "${VCRTOS_WISUN_MAIN_SRCS}" "")

    # wisun main linker script preprocessing
    add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/vcrtos_wisun_main.ld
        COMMAND ${CMAKE_C_COMPILER}
        -E -P ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/mcu/vc7300a/ARM/linker/vc7300a_main.ld.S
        -include ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/include/autoconf.h
        -include ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/include/param.h
        -I${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun
        -o ${PROJECT_BINARY_DIR}/vcrtos_wisun_main.ld
        VERBATIM
    )
    add_custom_target(vcrtos_wisun_main_linker ALL DEPENDS ${PROJECT_BINARY_DIR}/vcrtos_wisun_main.ld)
    add_dependencies(vcrtos_wisun_main PLATFORM_LIBS vcrtos_wisun_main_linker)
    target_link_libraries(vcrtos_wisun_main PLATFORM_LIBS)

    # create compressed version of vcrtos_wisun_main.bin
    add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin.lzma
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/tools/easylzma/Linux/x86_64/elzma -k -s 65536 -v -f ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin && mv ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin.lzma ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.tmp && touch ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.magic && printf "vtxc" >> ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.magic && cat ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.magic ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.tmp > ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin.lzma && rm ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.magic ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.tmp
        COMMENT "create compressed version of vcrtos_wisun_main.bin"
        VERBATIM
    )
    add_custom_target(vcrtos_wisun_main_compressed ALL DEPENDS
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin.lzma
    )

    # padding vcrtos_wisun_bootloader.bin to 16K
    add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_16K.bin
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/platform/SDK/vcrtos_wisun_vc7300/wisun/tools/scripts/padding_bootloader.sh ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader.bin ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_padding.bin && cat ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader.bin ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_padding.bin > ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_16K.bin && rm ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_padding.bin
        COMMENT "padding vcrtos_wisun_bootloader.bin to 16KB"
        VERBATIM
    )
    add_custom_target(vcrtos_wisun_bootloader_16K ALL DEPENDS
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader.bin
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_16K.bin
    )

    # combine vcrtos_wisun_bootloader_16K.bin with vcrtos_wisun_main.bin

    if (CONFIG_WISUN_ROOT)
        set(WISUN_DEVICE_ROLE ROOT)
    else()
        set(WISUN_DEVICE_ROLE NODE)
    endif()

    add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_${WISUN_DEVICE_ROLE}.bin
        COMMAND cat ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_16K.bin ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin > ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_${WISUN_DEVICE_ROLE}.bin
        COMMENT "combine bootloader and main image as vcrtos_wisun_${WISUN_DEVICE_ROLE}.bin"
        VERBATIM
    )

    add_custom_target(vcrtos_wisun_${WISUN_DEVICE_ROLE} ALL DEPENDS
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_bootloader_16K.bin
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_main.bin
        ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/vcrtos_wisun_${WISUN_DEVICE_ROLE}.bin
    )

    # TODO: build firmware upgrade image

endif()

if(VCSOFTWARE_SDK MATCHES freertos_vc7300)
    SET(FREERTOS_VC7300_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/freertos_vc7300.c
    )

    add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
    add_definitions(-DVCDRIVERS_VERSION="${VCSOFTWARE_OS_VER}")

    CREATE_TEST_LIBRARY(freertos_vc7300 "${FREERTOS_VC7300_SRCS}" "")
    add_dependencies(freertos_vc7300 PLATFORM_LIBS)
    target_link_libraries(freertos_vc7300 PLATFORM_LIBS)
endif()

if(VCSOFTWARE_SDK MATCHES bare_vc7300)
    SET(BARE_VC7300_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/bare_vc7300.c
    )

    add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
    add_definitions(-DVCDRIVERS_VERSION="${VCSOFTWARE_OS_VER}")

    CREATE_TEST_LIBRARY(bare_vc7300 "${BARE_VC7300_SRCS}" "")
    add_dependencies(bare_vc7300 PLATFORM_LIBS)
    target_link_libraries(bare_vc7300 PLATFORM_LIBS)
endif()

if(VCSOFTWARE_SDK MATCHES vcrtos_contiki_linux)
    set(VCRTOS_CONTIKI_LINUX_SRCS
        ${VCSOFTWARE_COMMON_SRCS}
        ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos_contiki_linux.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos_processes.c
    )

    add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
    add_definitions(-DVCRTOS_PROJECT_CONFIG_FILE="vcrtos-project-config.h")
    add_definitions(-DVCRTOS_VERSION="${VCSOFTWARE_OS_VER}")

    add_definitions(-DMAC_CONF_WITH_CSMA=1)
    add_definitions(-DNETSTACK_CONF_WITH_IPV6=1)
    add_definitions(-DROUTING_CONF_RPL_CLASSIC=1)

    CREATE_TEST_LIBRARY(vcrtos_contiki_linux "${VCRTOS_CONTIKI_LINUX_SRCS}" "")
    add_dependencies(vcrtos_contiki_linux PLATFORM_LIBS)
    target_link_libraries(vcrtos_contiki_linux PLATFORM_LIBS)
endif()

if(VCSOFTWARE_SDK MATCHES vcrtos_contiki_vc7300)
    set(VCRTOS_CONTIKI_VC7300_SRCS
        ${VCSOFTWARE_COMMON_SRCS}
        ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos_contiki_vc7300.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos_processes.c
    )

    add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
    add_definitions(-DVCRTOS_PROJECT_CONFIG_FILE="vcrtos-project-config.h")
    add_definitions(-DVCRTOS_VERSION="${VCSOFTWARE_OS_VER}")

    add_definitions(-DMAC_CONF_WITH_CSMA=1)
    add_definitions(-DNETSTACK_CONF_WITH_IPV6=1)
    add_definitions(-DROUTING_CONF_RPL_CLASSIC=1)

    CREATE_TEST_LIBRARY(vcrtos_contiki_vc7300 "${VCRTOS_CONTIKI_VC7300_SRCS}" "")
    add_dependencies(vcrtos_contiki_vc7300 PLATFORM_LIBS)
    target_link_libraries(vcrtos_contiki_vc7300 PLATFORM_LIBS)
endif()

if(VCSOFTWARE_SDK MATCHES vcrtos_vc7300)
    set(VCRTOS_VC7300_SRCS
        ${VCSOFTWARE_COMMON_SRCS}
        ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos_vc7300.cpp
    )

    add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
    add_definitions(-DVCRTOS_PROJECT_CONFIG_FILE="vcrtos-project-config.h")
    add_definitions(-DVCRTOS_VERSION="${VCSOFTWARE_OS_VER}")

    CREATE_TEST_LIBRARY(vcrtos_vc7300 "${VCRTOS_VC7300_SRCS}" "")
    add_dependencies(vcrtos_vc7300 PLATFORM_LIBS)
    target_link_libraries(vcrtos_vc7300 PLATFORM_LIBS)
endif()

if (VCSOFTWARE_SDK MATCHES vcrtos_linux)
    set(VCRTOS_LINUX_SRCS
        ${VCSOFTWARE_COMMON_SRCS}
        ${CMAKE_CURRENT_SOURCE_DIR}/vcrtos_linux.cpp
    )

    add_definitions(-DVCDRIVERS_PROJECT_CONFIG_FILE="vcdrivers-project-config.h")
    add_definitions(-DVCRTOS_PROJECT_CONFIG_FILE="vcrtos-project-config.h")
    add_definitions(-DVCRTOS_VERSION="${VCSOFTWARE_OS_VER}")

    CREATE_TEST_LIBRARY(vcrtos_linux "${VCRTOS_LINUX_SRCS}" "")
    add_dependencies(vcrtos_linux PLATFORM_LIBS)
    target_link_libraries(vcrtos_linux PLATFORM_LIBS)
endif()

ADDSUBDIRS()
