# Copyright (c) 2022 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

include(${MBED_PATH}/tools/cmake/app.cmake)

project(left)

add_subdirectory(${MBED_PATH})

add_executable(left
    main.cpp
)
target_compile_definitions(left PUBLIC LEFT=1)
target_link_libraries(left mbed-os mbed-netsocket mbed-events)

mbed_set_post_build(left)

project(right)

add_executable(right
    main.cpp
)
target_compile_definitions(right PUBLIC RIGHT=1)
target_link_libraries(right mbed-os mbed-netsocket mbed-events)

mbed_set_post_build(right)

project(battery_monitor)

set(MBED_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os
    CACHE INTERNAL "")
set(MBED_CONFIG_PATH
    ${CMAKE_CURRENT_BINARY_DIR}
    CACHE INTERNAL "")
set(APP_TARGET mros2-mbed)

#include(${MBED_PATH}/tools/cmake/app.cmake)

add_subdirectory(${MBED_PATH})

# if(DEFINED ENV{APPNAME})
#  set(APP_NAME $ENV{APPNAME})
#else()
#  set(APP_NAME "echoreply_string")
#endif()
#message(STATUS "APP_NAME=${APP_NAME}")

#execute_process(COMMAND git submodule update --init --recursive
#                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mros2)
#add_library(mros2 INTERFACE)
#add_subdirectory(mros2)

#set(RTPS_CONFIG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_executable(battery_monitor
    battery_monitor.cpp
)
target_link_libraries(battery_monitor mbed-os mbed-netsocket mbed-events)

mbed_set_post_build(battery_monitor)

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()