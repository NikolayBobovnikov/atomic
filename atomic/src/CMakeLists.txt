cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# ---- Create library ----

add_library(${PipelineLibrary} ${headers} ${sources} "include/pipeline_config.h" "source/pipeline_config.cpp")
set_target_properties(${PipelineLibrary} PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PipelineLibrary} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PipelineLibrary} PROPERTY CXX_STANDARD 17)
endif()