

pybind11_add_module(libpyspdlog SHARED python_spdlog.cpp)
set_target_properties(libpyspdlog PROPERTIES SUFFIX ".so")


add_dependencies(libpyspdlog project_spdlog)


include(GenerateExportHeader)
generate_export_header(libpyspdlog)

install(TARGETS libpyspdlog EXPORT PyspdlogTargets
  LIBRARY DESTINATION pyspdlog
  INCLUDES DESTINATION pyspdlog/include)

install(FILES pyspdlog.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/libpyspdlog_export.h
  DESTINATION
  pyspdlog/include
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogConfigVersion.cmake"
  VERSION ${pyspdlog_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

configure_file(../cmake/PyspdlogConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogConfig.cmake"
  COPYONLY
  )

set(ConfigPackageLocation pyspdlog/cmake)

export(EXPORT PyspdlogTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogTargets.cmake"
  )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogTargets.cmake"
  DESTINATION ${ConfigPackageLocation})

install(FILES ../cmake/PyspdlogConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation}
  )

