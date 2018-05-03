cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(APP_NAME aws-iot-device)
project(${APP_NAME})

add_library(${APP_NAME} SHARED AWSIOTDevice.cpp)

if(WIN32)
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/../../build/archive/Debug)
    set(OPENSSL_LIB_PATH D:/programs/OpenSSL-Win32/lib)

    add_definitions(-DDLL_EXPORT)

    find_library(IOT_CLIENT iot-client HINTS ${LIB_PATH})
    find_library(AWS_IOT_SDK NAMES aws-iot-sdk-cpp HINTS ${LIB_PATH})
    find_library(SSL NAMES libssl HINTS ${OPENSSL_LIB_PATH})
    find_library(CRYPTO NAMES libcrypto HINTS ${OPENSSL_LIB_PATH})

    target_link_libraries(${APP_NAME} ${SSL} ${CRYPTO} ${AWS_IOT_DEVICE} ${AWS_IOT_SDK})
else()
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/../../build/archive)
    set(OPENSSL_LIB_PATH /usr/local/opt/openssl/lib)

    find_library(IOT_CLIENT NAMES iot-client HINTS ${LIB_PATH})
    find_library(AWS_IOT_SDK NAMES aws-iot-sdk-cpp HINTS ${LIB_PATH})
    find_library(SSL NAMES ssl HINTS ${OPENSSL_LIB_PATH})
    find_library(CRYPTO NAMES crypto HINTS ${OPENSSL_LIB_PATH})

    target_link_libraries(${APP_NAME} -Wl,-all_load ${IOT_CLIENT} ${AWS_IOT_SDK} ${SSL} ${CRYPTO} resolv)
endif()
