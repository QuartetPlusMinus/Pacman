cmake_minimum_required(VERSION 3.3)

project(Pacman)

include_directories("${PROJECT_BINARY_DIR}")

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(PROTO_PATH "${CMAKE_SOURCE_DIR}/Proto")
set(SERVICE_PROTO "${PROTO_PATH}/service.proto")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})

set(SERVICE_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/service.pb.cc")
set(SERVICE_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/service.pb.h")
set(SERVICE_GRPC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/service.grpc.pb.cc")
set(SERVICE_GRPC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/service.grpc.pb.h")
add_custom_command(
        OUTPUT "${SERVICE_PB_H_FILE}"
        "${SERVICE_PB_CPP_FILE}"
        "${SERVICE_GRPC_PB_H_FILE}"
        "${SERVICE_GRPC_PB_CPP_FILE}"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS "--proto_path=${PROTO_PATH}"
        "--cpp_out=${GENERATED_PROTOBUF_PATH}"
        "${SERVICE_PROTO}"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS "--proto_path=${PROTO_PATH}"
        "--grpc_out=${GENERATED_PROTOBUF_PATH}"
        "--plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin"
        "${SERVICE_PROTO}"
)
set(GENERATED_PROTOBUF_FILES ${SERVICE_PB_H_FILE} ${SERVICE_PB_CPP_FILE}
        ${SERVICE_GRPC_PB_H_FILE} ${SERVICE_GRPC_PB_CPP_FILE})

include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

set(CMAKE_PREFIX_PATH "/home/murt/Qt/5.10.0/gcc_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
#set(SOURCE_FILES main.cpp mainwindow.h mainwindow.cpp)



set(CLIENT_FILES Client/main.cpp Client/PlayerConnectionClient.cpp Client/GameLoop.cpp Client/Ghost.cpp Client/Pacman.cpp Client/BeingView.cpp Client/TileMap.cpp Client/TileMap.h Client/mainwindow.h Client/mainwindow.cpp)
set(SERVER_FILES Server/main.cpp Server/PlayerConnectionServer.cpp Server/BaseBeing.cpp Server/Ghost.cpp Server/Pacman.cpp Server/MapManager.cpp Server/Client.h Server/GameRoom.h )

# Define sources and executable
set(EXECUTABLE_NAME "pacman")

add_executable(pacman ${CLIENT_FILES} ${GENERATED_PROTOBUF_FILES} ${SOURCE_FILES})
add_executable(pacman_server ${SERVER_FILES} ${GENERATED_PROTOBUF_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} )
endif()
target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets Qt5::Core)