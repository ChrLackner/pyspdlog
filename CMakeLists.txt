
cmake_minimum_required(VERSION 3.0)

project(pyspdlog)
set(pyspdlog_VERSION 0.1)

# ccache
if(USE_CCACHE)
  find_program(CCACHE_FOUND ccache)
  if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
  endif(CCACHE_FOUND)
endif(USE_CCACHE)

# OpenMP
find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# Python
find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

# check if CMAKE_INSTALL_PREFIX is set by user, if not install in python dir
message("Python install dir = ${PYTHON_INSTALL_DIR}")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${PYTHON_INSTALL_DIR} CACHE PATH "Install dir" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

include(ExternalProject)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/external_projects/spdlog.cmake)
include_directories(${SPDLOG_INCLUDE_DIR})

add_subdirectory(external_dependencies/pybind11)
add_subdirectory(src)
add_subdirectory(python)



include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif(BUILD_TESTING)
