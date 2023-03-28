# CMakeList.txt : CMake project for IdManager, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# ---- Project ----

# Note: update this to your new project's name and version
project(
  task2
  VERSION 1.0
  LANGUAGES CXX
)

# ---- gRPC & Protobuf ----
# Curently works with globally installed gRPC.
# In case of using loca installation, need to set paths for cmake find_package
# set(GRPC_INSTALL_DIR "/home/nick/home/projects/edu/cpp/grpc/cmake/build/lib/.local")
# list(APPEND CMAKE_PREFIX_PATH ${GRPC_INSTALL_DIR})

# Find the gRPC and protobuf packages
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
include(cmake/common.cmake)


# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Update library submodules ----
find_package(Git)
if(NOT Git_FOUND)
message(
  FATAL_ERROR
    "Git not found."
)
endif()

# Proto file
set(ProtoName employee)
get_filename_component(hw_proto "protos/${ProtoName}.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${ProtoName}.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${ProtoName}.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${ProtoName}.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${ProtoName}.grpc.pb.h")
add_custom_command(
      OUTPUT "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# grpc_proto lib
add_library(grpc_proto
  ${grpc_srcs}
  ${grpc_hdrs}
  ${proto_srcs}
  ${proto_hdrs})
target_link_libraries(grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Include generated *.pb.h files
set(ProtoIncludeDir "${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# ---- Include subprojects ----
add_subdirectory (client) 
add_subdirectory (server)
#enable_testing ()
