set(unittest-includes ${unittest-includes}
)

set(unittest-sources
)

set(unittest-test-sources
    src/core/list/test_list.cpp
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPROJECT_CORE_CONFIG_FILE='\"core-unittest-config.h\"'")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROJECT_CORE_CONFIG_FILE='\"core-unittest-config.h\"'")
