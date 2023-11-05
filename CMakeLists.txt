cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    threading
    VERSION 0.1.0
    DESCRIPTION "Threading libraries benchmark"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(TBB REQUIRED)

# ---- Declare library ----
add_library(
    threading_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    threading_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(threading_lib PUBLIC cxx_std_20)

# ---- Declare executable ----
add_executable(threading_exe source/main.cpp)
add_executable(threading::exe ALIAS threading_exe)

set_property(TARGET threading_exe PROPERTY OUTPUT_NAME threading)

target_compile_features(threading_exe PRIVATE cxx_std_20)

target_link_libraries(threading_exe PRIVATE threading_lib TBB::tbb)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT threading_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of threading"
  )
endif()

include(cmake/dev-mode.cmake)
