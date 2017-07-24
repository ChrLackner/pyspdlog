
#include "pyspdlog.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace pyspdlog
{
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
      .def("debug", [](spd::logger& self, py::args args)
           {
             string st = "";
             for (auto arg : args)
               st += py::str(arg);
             self.debug(st);
           })
      .def("trace", [](spd::logger& self, py::args args)
           {
             string st = "";
             for (auto arg : args)
               st += py::str(arg);
             self.trace(st);
           })
      .def("info", [](spd::logger& self, py::args args)
           {
             string st = "";
             for (auto arg : args)
               st += py::str(arg);
             self.info(st);
           })
      .def("warn", [](spd::logger& self, py::args args)
           {
             string st = "";
             for (auto arg : args)
               st += py::str(arg);
             self.warn(st);
           })
      .def("error", [](spd::logger& self, py::args args)
           {
             string st = "";
             for (auto arg : args)
               st += py::str(arg);
             self.error(st);
           })
      .def("critical", [](spd::logger& self, py::args args)
           {
             string st = "";
             for (auto arg : args)
               st += py::str(arg);
             self.critical(st);
           })
      .def("SetPattern", (void (spd::logger::*)(const string&)) &spd::logger::set_pattern)
      .def("flush", &spd::logger::flush)
      ;

    py::class_<LoggedClass, shared_ptr<LoggedClass>>
      (m, "LoggedClass")
      .def("SetLogger", &LoggedClass::SetLogger)
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
  }

}

PYBIND11_PLUGIN(libpyspdlog)
{
  py::module m("libpyspdlog");
  pyspdlog::Exportspdlog(m);
  return m.ptr();
}
