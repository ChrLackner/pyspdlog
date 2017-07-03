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

  class LoggingHandler
  {
  private:
    shared_ptr<spd::logger> nullLogger;
    map<string,shared_ptr<spd::logger>> loggers;
  public:
    LoggingHandler()
    {
      nullLogger = make_shared<spd::logger>("nullLogger",make_shared<spd::sinks::null_sink_st>());
    }
    shared_ptr<spd::logger> getLogger(const string & name) const
    {
      auto it = loggers.find(name);
      if(it == loggers.end())
        return nullLogger;
      return it->second;
    }

    void setLogger(string name, shared_ptr<spd::logger> log)
    {
      loggers[name] = log;
    }
  };

  extern LoggingHandler loggers;
}

#endif // __FILE_PYSPDLOG_HPP
