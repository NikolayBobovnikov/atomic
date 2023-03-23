# CMakeList.txt : CMake project for IdManager, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# ---- Project ----

# Note: update this to your new project's name and version
project(
  pipeline
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

set(PipelineLibrary ${PROJECT_NAME}.lib)
set(PipelineStadnalone ${PROJECT_NAME})


add_subdirectory (src) 
add_subdirectory (test)
add_subdirectory (standalone)
enable_testing ()
