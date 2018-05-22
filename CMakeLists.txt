
cmake_minimum_required(VERSION 3.0)

project(pyspdlog)
set(pyspdlog_VERSION 0.1)

find_package(NGSolve CONFIG REQUIRED
  HINTS $ENV{NETGENDIR}/.. /opt/netgen/ /Applications/Netgen.app/Contents/Resources/CMake C:/netgen
  )

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

include(ExternalProject)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/external_projects/spdlog.cmake)
include_directories(${SPDLOG_INCLUDE_DIR})

# install the spdlog headers along with the pyspdlog header
install(DIRECTORY ${SPDLOG_INCLUDE_DIR} DESTINATION pyspdlog/include)

add_subdirectory(src)
add_subdirectory(python)


include(CTest)
add_subdirectory(tests)
