
pybind11_add_module(libpyspdlog.so SHARED python_spdlog.cpp)

add_dependencies(libpyspdlog.so project_spdlog)


include(GenerateExportHeader)
generate_export_header(libpyspdlog.so)

install(TARGETS libpyspdlog.so EXPORT PyspdlogTargets
  LIBRARY DESTINATION pyspdlog
  INCLUDES DESTINATION pyspdlog/include)

install(FILES pyspdlog.hpp
  DESTINATION
  pyspdlog/include
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogConfigVersion.cmake"
  VERSION ${pyspdlog_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT PyspdlogTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogTargets.cmake"
  NAMESPACE pyspdlog::
  )

configure_file(../cmake/PyspdlogConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogConfig.cmake"
  COPYONLY
  )

set(ConfigPackageLocation cmake/pyspdlog)
install(EXPORT PyspdlogTargets
  FILE PyspdlogTargets.cmake
  NAMESPACE pyspdlog::
  DESTINATION ${ConfigPackageLocation})

install(FILES ../cmake/PyspdlogConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/pyspdlog/PyspdlogConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation}
  )
