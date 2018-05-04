cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(aws-iot-cpp-samples CXX)

######################################
# Section : Disable in-source builds #
######################################

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt and CMakeFiles folder.")
endif ()

########################################
# Section : Common Build setttings #
########################################
# Set required compiler standard to standard c++11. Disable extensions.
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Configure Compiler flags
if (UNIX AND NOT APPLE)
    # Prefer pthread if found
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    set(CUSTOM_COMPILER_FLAGS "-fno-exceptions -Wall -Werror")
elseif (APPLE)
    set(CUSTOM_COMPILER_FLAGS "-fno-exceptions -Wall -Werror")
elseif (WIN32)
    set(CUSTOM_COMPILER_FLAGS "/W4")
    add_definitions(-DDLL_EXPORT)
endif ()

################################
# Target : Build AWSDevice #
################################
set(IOT_CLIENT iot-client)

# Add Target
add_library(${IOT_CLIENT} "${PROJECT_SOURCE_DIR}/IOTClientWrapper.cpp;${PROJECT_SOURCE_DIR}/IOTClient.cpp;${PROJECT_SOURCE_DIR}/../../common/ConfigCommon.cpp")

# Add Target specific includes
target_include_directories(${IOT_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/../../common)
target_include_directories(${IOT_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR})

# Configure Threading library
find_package(Threads REQUIRED)

# Add SDK includes
target_include_directories(${IOT_CLIENT} PUBLIC ${CMAKE_BINARY_DIR}/${DEPENDENCY_DIR}/rapidjson/src/include)
target_include_directories(${IOT_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/../../include)

target_link_libraries(${IOT_CLIENT} PUBLIC "Threads::Threads")
target_link_libraries(${IOT_CLIENT} PUBLIC ${SDK_TARGET_NAME})

# Copy Json config file
add_custom_command(TARGET ${IOT_CLIENT} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy ${PROJECT_SOURCE_DIR}/../../common/SampleConfig.json $<TARGET_FILE_DIR:${IOT_CLIENT}>/config/SampleConfig.json)
set_property(TARGET ${IOT_CLIENT} APPEND_STRING PROPERTY COMPILE_FLAGS ${CUSTOM_COMPILER_FLAGS})

# Gather list of all .cert files in "/cert"
add_custom_command(TARGET ${IOT_CLIENT} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory ${PROJECT_SOURCE_DIR}/../../certs $<TARGET_FILE_DIR:${IOT_CLIENT}>/certs)

if (MSVC)
    target_sources(${IOT_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/../../common/ConfigCommon.hpp)
    source_group("Header Files\\Samples\\IOTClient" FILES ${PROJECT_SOURCE_DIR}/../../common/ConfigCommon.hpp)
    source_group("Source Files\\Samples\\IOTClient" FILES ${PROJECT_SOURCE_DIR}/../../common/ConfigCommon.cpp)

    target_sources(${IOT_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/IOTClient.hpp)
    source_group("Header Files\\Samples\\IOTClient" FILES ${PROJECT_SOURCE_DIR}/IOTClient.hpp)
    source_group("Source Files\\Samples\\IOTClient" FILES ${PROJECT_SOURCE_DIR}/IOTClient.cpp)

    target_sources(${IOT_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/IOTClientWrapper.h)
    source_group("Header Files\\Samples\\IOTClient" FILES ${PROJECT_SOURCE_DIR}/IOTClientWrapper.h)
    source_group("Source Files\\Samples\\IOTClient" FILES ${PROJECT_SOURCE_DIR}/IOTClientWrapper.cpp)
endif ()

#########################
# Add Network libraries #
#########################

set(NETWORK_WRAPPER_DEST_TARGET ${IOT_CLIENT})
include(${PROJECT_SOURCE_DIR}/../../network/CMakeLists.txt.in)
