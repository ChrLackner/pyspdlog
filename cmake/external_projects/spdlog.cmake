find_program(GIT_EXECUTABLE git)
ExternalProject_Add(
  project_spdlog
  PREFIX ${CMAKE_BINARY_DIR}/spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG 4371092309e999052513b109dc68f7a260153681
  TIMEOUT 10
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )


# Expose required variable (SPDLOG_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(project_spdlog source_dir)
set(SPDLOG_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for spdlog")
