
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

include(ExternalProject)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/external_projects/spdlog.cmake)
include_directories(${SPDLOG_INCLUDE_DIR})

# install the spdlog headers along with the pyspdlog header
install(DIRECTORY ${SPDLOG_INCLUDE_DIR} DESTINATION pyspdlog/include)

find_program(GIT_COMMAND git REQUIRED)
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/pybind11)
  execute_process(COMMAND ${GIT_COMMAND} clone https://github.com/pybind/pybind11.git pybind11
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()
execute_process(COMMAND ${GIT_COMMAND} -c advice.detachedHead=false checkout fe0cf8b73b8e068c205e062c779eb694b194d6b4
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11_build)

add_subdirectory(src)
add_subdirectory(python)


include(CTest)
add_subdirectory(tests)
