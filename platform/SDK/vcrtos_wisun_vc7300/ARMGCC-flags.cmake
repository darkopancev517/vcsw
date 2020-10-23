macro(SET_COMPILER_DBG_RLZ_FLAG flag value)
        SET(${flag}_DEBUG "${${flag}_DEBUG} ${value}")
        SET(${flag}_RELEASE "${${flag}_RELEASE} ${value}")
if (0)
 message("flag = ${flag}")
 message("value = ${value}")
 message("MY_C_FLAGS_RELEASE2 = ${CMAKE_C_FLAGS_RELEASE}")
endif()
endmacro(SET_COMPILER_DBG_RLZ_FLAG)

macro(SET_COMPILER_DBG_RLZ_COMMON_FLAG flag value)
        SET(${flag}_DEBUG "${${flag}_DEBUG} ${${value}_DEBUG}")
        SET(${flag}_RELEASE "${${flag}_RELEASE} ${${value}_RELEASE}")
endmacro(SET_COMPILER_DBG_RLZ_COMMON_FLAG)

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_CXX_FLAGS "")

#SET(CMAKE_FLAGS_COMMON_DEBUG "-DDEBUG -g -Og")
SET(CMAKE_FLAGS_COMMON_DEBUG "-g -Os")
SET(CMAKE_FLAGS_COMMON_RELEASE "-g -Os")

SET(CMAKE_COMPILE_FLAGS_BASIS "-mcpu=cortex-m3 -mthumb -mno-unaligned-access -ffunction-sections -fdata-sections -Wall -MMD -MP")

### Set ASM flags ###
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "${CMAKE_COMPILE_FLAGS_BASIS}")
SET_COMPILER_DBG_RLZ_COMMON_FLAG (CMAKE_ASM_FLAGS CMAKE_FLAGS_COMMON)

### Set C/C++ flags ###
message("${CMAKE_SOURCE_DIR}/include_file.txt")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "@${CMAKE_SOURCE_DIR}/include_file.txt")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_CXX_FLAGS "@${CMAKE_SOURCE_DIR}/include_file.txt")

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_COMPILE_FLAGS_BASIS}")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_COMPILE_FLAGS_BASIS}")
SET_COMPILER_DBG_RLZ_COMMON_FLAG (CMAKE_C_FLAGS CMAKE_FLAGS_COMMON)
SET_COMPILER_DBG_RLZ_COMMON_FLAG (CMAKE_CXX_FLAGS CMAKE_FLAGS_COMMON)

### Set common linker flags ###
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-g -Os -Xlinker --gc-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m3 -mthumb -mno-unaligned-access --specs=nano.specs -static")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_calloc_r")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,memset -Wl,--wrap,memcpy")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,printf -fno-builtin-printf")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,sprintf -fno-builtin-sprintf")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,snprintf -fno-builtin-snprintf")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,vsnprintf -fno-builtin-vsnprintf")

