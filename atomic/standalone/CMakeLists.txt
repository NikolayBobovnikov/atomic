cmake_minimum_required (VERSION 3.8)

# ---- Add source files ----
# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")


# ---- Standalone executable ----
add_executable(${PipelineStadnalone} ${headers} ${sources} "include/cli_options.h" "source/cli_options.cpp")
set_target_properties(${PipelineStadnalone} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PipelineStadnalone} PRIVATE ${PipelineLibrary})
target_include_directories(${PipelineStadnalone} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src/include/")
target_include_directories(${PipelineStadnalone} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/extern/")

# Update library submodules
find_package(Git)
if(Git_FOUND)
  message("Git found: ${GIT_EXECUTABLE}")
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive OUTPUT_VARIABLE GIT_OUTPUT)
  message("Initializing git submodules: ${GIT_OUTPUT}")
endif()

# library for CLI options
add_subdirectory(extern/cxxopts)
target_include_directories(${PipelineStadnalone} PUBLIC cxxopts)
target_link_libraries(${PipelineStadnalone} PUBLIC cxxopts)

# library for YAML for storing settings configuration file
add_subdirectory(extern/yaml-cpp)
target_include_directories(${PipelineStadnalone} PUBLIC yaml-cpp)
target_link_libraries(${PipelineStadnalone} PUBLIC yaml-cpp)
