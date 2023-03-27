cmake_minimum_required (VERSION 3.8)

project(
  server
  VERSION 1.0
  LANGUAGES CXX
)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# ---- Add source files ----
# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc")

# sqlite git 
#execute_process(COMMAND ${GIT_EXECUTABLE} submodule add https://github.com/SRombauts/SQLiteCpp.git extern/sqlite OUTPUT_VARIABLE GIT_OUTPUT)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive OUTPUT_VARIABLE GIT_OUTPUT)
add_subdirectory(extern/sqlite_orm)

add_executable(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../common/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/extern/sqlite_orm/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${ProtoIncludeDir})

target_link_libraries(${PROJECT_NAME}
    grpc_proto
    sqlite_orm::sqlite_orm
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
