cmake_minimum_required(VERSION 3.3)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Pacman)

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
#configure_file(
        #"config.h.in"
 #       "${PROJECT_BINARY_DIR}/Client/config.h"
#)
include_directories("${PROJECT_BINARY_DIR}")

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(PROTO_PATH "${CMAKE_SOURCE_DIR}/Proto")
set(HELLOWORLD_PROTO "${PROTO_PATH}/service.proto")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})

set(HELLOWORLD_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/service.pb.cc")
set(HELLOWORLD_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/service.pb.h")
set(HELLOWORLD_GRPC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/service.grpc.pb.cc")
set(HELLOWORLD_GRPC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/service.grpc.pb.h")
add_custom_command(
        OUTPUT "${HELLOWORLD_PB_H_FILE}"
        "${HELLOWORLD_PB_CPP_FILE}"
        "${HELLOWORLD_GRPC_PB_H_FILE}"
        "${HELLOWORLD_GRPC_PB_CPP_FILE}"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS "--proto_path=${PROTO_PATH}"
        "--cpp_out=${GENERATED_PROTOBUF_PATH}"
        "${HELLOWORLD_PROTO}"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS "--proto_path=${PROTO_PATH}"
        "--grpc_out=${GENERATED_PROTOBUF_PATH}"
        "--plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin"
        "${HELLOWORLD_PROTO}"
)
set(GENERATED_PROTOBUF_FILES ${HELLOWORLD_PB_H_FILE} ${HELLOWORLD_PB_CPP_FILE}
        ${HELLOWORLD_GRPC_PB_H_FILE} ${HELLOWORLD_GRPC_PB_CPP_FILE})

include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

set(CLIENT_FILES Client/main.cpp Client/PlayerConnectionClient.cpp Client/GameLoop.cpp Client/Ghost.cpp Client/Pacman.cpp Client/BeingView.cpp)
set(SERVER_FILES Server/main.cpp Server/PlayerConnectionServer.cpp Server/BaseBeing.cpp Server/Ghost.cpp Server/Pacman.cpp Server/MapManager.cpp Server/Client.h Server/GameRoom.h)

# Define sources and executable
set(EXECUTABLE_NAME "pacman")

add_executable(pacman ${CLIENT_FILES} ${GENERATED_PROTOBUF_FILES})
add_executable(pacman_server ${SERVER_FILES} ${GENERATED_PROTOBUF_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)