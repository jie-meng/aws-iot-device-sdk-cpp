cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(APP_NAME AWSIOTUser)
project(${APP_NAME})

add_executable(${APP_NAME} main.cpp)

if(WIN32)
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/../../build/archive/Debug)
else()
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/../../build/lib)
endif()

find_library(AWS_IOT_DEVICE NAMES aws-iot-device HINTS ${LIB_PATH})
find_library(AWS_IOT_SDK NAMES aws-iot-sdk-cpp HINTS ${LIB_PATH})

target_link_libraries(${APP_NAME} ${AWS_IOT_DEVICE} ${AWS_IOT_SDK})
