include(CMakeForceCompiler)

macro(SET_COMPILER_DBG_RLZ_FLAG flag value)
    set(${flag}_DEBUG "${${flag}_DEBUG} ${value}")
    set(${flag}_RELEASE "${${flag}_RELEASE} ${value}")
#enable this if for debugging
if (0)
 message("flag = ${flag}")
 message("value = ${value}")
 message("MY_C_FLAGS_RELEASE2 = ${CMAKE_C_FLAGS_RELEASE}")
endif(0) # comment end
endmacro(SET_COMPILER_DBG_RLZ_FLAG)

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_CXX_FLAGS "")

########### COMPILER FLAGS  ###########
#
#######################################

########### DEBUG ###########

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-D__STARTUP_CLEAR_BSS")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-Wall")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-mfloat-abi=hard")
# Floating point support

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-mthumb")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-fno-common")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-ffunction-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-fdata-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-ffreestanding")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-fno-builtin")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-mapcs")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_ASM_FLAGS "-std=c99")

# Debug specific
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
if (PAL_GCOV_SUPPORT)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0  -fprofile-arcs -ftest-coverage")
endif ()

# Board specific

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-Wall")
# Board specific
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-m32")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-MMD")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-MP")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-fno-common")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-ffunction-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-fdata-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-ffreestanding")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-fno-builtin")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "-std=gnu99")


########### Release specific ###########
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
######################################

########### LINKER FLAGS  ###########
#
#
#####################################

########### DEBUG ###########
# Debug specific
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")
if (PAL_GCOV_SUPPORT)
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g -O0 -lgcov -fprofile-arcs")
endif ()

########### RELEASE ###########

SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-m32")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wall")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-fno-common")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-ffunction-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-fdata-sections")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-ffreestanding")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-fno-builtin")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Xlinker")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "--gc-sections")

if (PAL_MEMORY_STATISTICS)
	SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap=malloc")
	SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap=free")
	SET_COMPILER_DBG_RLZ_FLAG (CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap=calloc")
	add_definitions("-DPAL_MEMORY_STATISTICS")
endif()

# This is because of mbedTLS is removing all debug and release compilation flags
# but keeping the global common flags so need to set all of them... no harm is done
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} @${CMAKE_SOURCE_DIR}/include_file.txt")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} @${CMAKE_SOURCE_DIR}/include_file.txt")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_C_FLAGS "@${CMAKE_SOURCE_DIR}/include_file.txt")
SET_COMPILER_DBG_RLZ_FLAG (CMAKE_CXX_FLAGS "@${CMAKE_SOURCE_DIR}/include_file.txt")

message(STATUS "BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
