import pathlib
import sys
import os

from base_classes import *

ROOT_FOLDER = pathlib.Path()

APPLICATION_FOLDER = ROOT_FOLDER / "application"
SYSTEM_FOLDER      = ROOT_FOLDER / "system"
LIBRARY_FOLDER     = ROOT_FOLDER / "library"

SOURCE_FOLDER = "src"
HEADER_FOLDER = "inc" # headers visible to other components
BINARY_FOLDER = "bin"

MAIN_SOURCE_NAME = "main.cpp"
MAIN_EXEC_NAME = "executable"

ADD_DEPENDENT_INCLUDEPATH = False
ADD_OWN_INCLUDEPATH = True

# Add the dependencies here. Example:
# DEPENDENCIES = {
#     APPLICATION_FOLDER / "game" : [
#         SYSTEM_FOLDER / "engine",
#         LIBRARY_FOLDER / "events"
#     ],
#     SYSTEM_FOLDER / "game" : [
#         LIBRARY_FOLDER / "events"
#     ]
# }
DEPENDENCIES = {
}

CUSTOM_OPTIONS = {
}

def run_command (command):
    print("running command: " + command)
    return os.system(command)

def compiled_object_factory (source_path, output_path, extra_options):
    def compile_object (sources, output_path):
        exit_code = run_command("g++ " + sources + " " + extra_options + " -c -o " + output_path)
        if exit_code != 0:
            sys.exit(exit_code)

    source_targets = [ Target(source_path) ]
    return CompiledObject(source_targets, output_path, compile_object)

def compiled_executable_factory (source_targets, output_path, extra_options):
    def compile_executable (sources, output_path):
        exit_code = run_command("g++ " + sources + " " + extra_options + " -o " + output_path)
        if exit_code != 0:
            sys.exit(exit_code)

    return CompiledObject(source_targets, output_path, compile_executable)

from overlay import *
