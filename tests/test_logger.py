import pytest
from pyspdlog import *


def test_logger():
    file_sink = simple_file_sink("debug.out",False)
    con_sink = console_sink(True)
    logger = Logger("Geometry", [file_sink,con_sink])
    logger.SetPattern("%v")
    logger.SetLevel(LOGGING_LEVEL.DEBUG)
    file_sink.SetLevel(LOGGING_LEVEL.DEBUG)
    con_sink.SetLevel(LOGGING_LEVEL.INFO)
    SetLogger("Geometry",logger)
    logger.info("Hi")
    logger.debug("debug")
    logger.flush()
    with open("debug.out","r") as f:
        assert f.readline() == "Hi\n"
        assert f.readline() == "debug\n"

if __name__ == "__main__":
    test_logger()
