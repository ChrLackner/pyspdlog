include("${CMAKE_CURRENT_LIST_DIR}/PyspdlogTargets.cmake")

set(PYSPDLOG_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/pyspdlog/include ${CMAKE_INSTALL_PREFIX}/pyspdlog/include/spdlog)
set(PYSPDLOG_LIBRARIES ${CMAKE_INSTALL_PREFIX}/pyspdlog/libpyspdlog.so)
