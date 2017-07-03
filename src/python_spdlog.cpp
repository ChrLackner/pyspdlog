
#include "pyspdlog.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace pyspdlog
{
  LoggingHandler loggers;

  void Exportspdlog(py::module m)
  { 
    py::enum_<spd::level::level_enum>
      (m,"LOGGING_LEVEL")
      .value("DEBUG",spd::level::debug)
      .value("TRACE",spd::level::trace)
      .value("INFO", spd::level::info)
      .value("WARNING", spd::level::warn)
      .value("ERROR", spd::level::err)
      .value("CRITICAL", spd::level::critical)
      .value("OFF", spd::level::off)
      .export_values()
      ;
  
    py::class_<spd::sinks::sink, shared_ptr<spd::sinks::sink>>
      (m, "Sink", "spd sink")
      .def("SetLevel", &spd::sinks::sink::set_level)
      ;
    py::class_<spd::logger,shared_ptr<spd::logger>>
      (m, "Logger", "spd logger")
      .def(py::init<const string&, shared_ptr<spd::sinks::sink>>())
      .def("__init__", [] (spd::logger* instance, const string& name, py::list asinks)
           {
             auto sinks = std::vector<shared_ptr<spd::sinks::sink>>();
             for (auto pysink : asinks)
               sinks.push_back(py::cast<shared_ptr<spd::sinks::sink>>(pysink));
             new (instance) spd::logger(name,std::begin(sinks),std::end(sinks));
           })
      .def("SetLevel", &spd::logger::set_level)
      .def("debug", (void (spd::logger::*)(const string&)) &spd::logger::debug)
      .def("trace", (void (spd::logger::*)(const string&)) &spd::logger::trace)
      .def("info", (void (spd::logger::*)(const string&)) &spd::logger::info)
      .def("warn", (void (spd::logger::*)(const string&)) &spd::logger::warn)
      .def("error", (void (spd::logger::*)(const string&)) &spd::logger::error)
      .def("critical", (void (spd::logger::*)(const string&)) &spd::logger::critical)
      .def("SetPattern", &spd::logger::set_pattern)
      ;

    m.def("simple_file_sink", [](const string& filename, bool multithreaded)
          {
            std::remove(filename.c_str());
            shared_ptr<spd::sinks::sink> sink;
            if(multithreaded)
              sink = make_shared<spd::sinks::simple_file_sink_mt>(filename);
            else
              sink = make_shared<spd::sinks::simple_file_sink_st>(filename);
            sink->set_level(spd::level::debug);
            return sink;
          });
    m.def("console_sink", [](bool multithreaded)
          {
            shared_ptr<spd::sinks::sink> sink;
            if (multithreaded)
              sink = make_shared<spd::sinks::ansicolor_stdout_sink_mt>();
            else
              sink = make_shared<spd::sinks::ansicolor_stdout_sink_st>();
            return sink;
          });
  
    m.def("SetLogger", [] (const string & name, shared_ptr<spd::logger> log)
          {
            loggers.setLogger(name,log);
          });
  }

}

PYBIND11_MODULE(libpyspdlog,m)
{
  pyspdlog::Exportspdlog(m);
}