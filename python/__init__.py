
from pyspdlog.libpyspdlog import *
import os,shutil

def CreateThreadLogFiles(logfile):
    """Create seperate logfiles for each thread, the thread number must be the first column in the
    logfile."""

    filename = "".join(logfile.split(".")[:-1])
    extension = logfile.split(".")[-1]
    if os.path.exists(filename + "_thread"):
        shutil.rmtree(filename + "_thread")
    os.mkdir(filename + "_thread")
    with open(logfile,'r') as f:
        for line in f:
            threadnr = line.split(" ")[0]
            with open(filename + "_thread/" + threadnr + "." + extension,"a") as fw:
                print(line[:-1],file=fw)
