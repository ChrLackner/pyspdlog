#ifndef __FILE_PYSPDLOG_HPP
#define __FILE_PYSPDLOG_HPP

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/file_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace pyspdlog
{
  namespace spd = spdlog;
  using namespace std;

  class LoggedClass
  {
  protected:
    shared_ptr<spd::logger> log;
  public:
    LoggedClass(string name)
    {
      log = make_shared<spd::logger>(name, make_shared<spd::sinks::ansicolor_stdout_sink_mt>());
    }
    LoggedClass(shared_ptr<spd::logger> alog) : log(alog) { ; }
    void SetLogger(shared_ptr<spd::logger> alog) { log = alog; }
  };
}

#endif // __FILE_PYSPDLOG_HPP
