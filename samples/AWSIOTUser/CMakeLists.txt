cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(APP_NAME AWSIOTUser)
project(${APP_NAME})

add_executable(${APP_NAME} main.cpp)

if(WIN32)
    find_library(AWS_IOT_DEVICE aws-iot-device HINTS ${PROJECT_SOURCE_DIR}/../AWSIOTDevice/Debug)
else()
    find_library(AWS_IOT_DEVICE aws-iot-device HINTS ${PROJECT_SOURCE_DIR}/../AWSIOTDevice)
endif()

target_link_libraries(${APP_NAME} ${AWS_IOT_DEVICE})
