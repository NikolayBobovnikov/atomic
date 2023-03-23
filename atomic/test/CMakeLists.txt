cmake_minimum_required (VERSION 3.8)

# ---- Add source files ----
# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")



# ---- Testing binary ----
add_executable(cpp_test ${headers} ${sources})
set_target_properties(cpp_test PROPERTIES CXX_STANDARD 17)
target_include_directories(cpp_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src/include/")
target_link_libraries(cpp_test PRIVATE ${PipelineLibrary})

# define tests
add_test(
  NAME cpp_test
  COMMAND $<TARGET_FILE:cpp_test>
  )
