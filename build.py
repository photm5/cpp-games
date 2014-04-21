########## imports ##########

import sys
import pathlib

# enable modules from the .build folder to be imported
directory = pathlib.Path()
sys.path.append ( str(directory) + "/.build" )

from base_classes import *
from config import *

########## classes ##########

def get_dependencies (component_root_folder):
    global DEPENDENCIES

    if not component_root_folder.exists():
        print ("A component is targeted but doesn't exist!")
        print ("Maybe the dependency tree is incorrect?")
        print ("component path: " + str(component_root_folder))
        sys.exit(1)

    try:
        return DEPENDENCIES[component_root_folder]
    except KeyError:
        print ("A component is missing in the dependency tree!")
        print ("Add it in .build/config.py")
        print ("component path: " + str(component_root_folder))
        sys.exit(1)

def get_custom_options (component_root_folder):
    global CUSTOM_OPTIONS

    if not component_root_folder.exists():
        print ("A component is targeted but doesn't exist!")
        print ("Maybe the dependency tree is incorrect?")
        print ("component path: " + str(component_root_folder))
        sys.exit(1)

    try:
        return CUSTOM_OPTIONS[component_root_folder]
    except KeyError:
        return ""

class Component:
    def __init__ (self, component_root_folder):
        global SOURCE_FOLDER
        global BINARY_FOLDER

        self.root_folder = component_root_folder
        self.dependencies = []
        self.targets = []

        self.is_application = ( self.root_folder.parent == APPLICATION_FOLDER )

        dependency_folders = get_dependencies(self.root_folder)
        for dependency_folder in dependency_folders:
            self.dependencies.append(get_component(dependency_folder)) 

        include_folders = []
        include_folders.append("-I.")

        if ADD_OWN_INCLUDEPATH:
            include_folders.append("-I" + str(self.root_folder / HEADER_FOLDER))

        if ADD_DEPENDENT_INCLUDEPATH:
            for component in self.dependencies:
                include_folders.append("-I" + str(component.root_folder / HEADER_FOLDER))

        self.include_options = " ".join(include_folders)

        has_main = False

        source_folder = self.root_folder / SOURCE_FOLDER
        for source_file_path in list(source_folder.glob("**/*.cpp")):
            if not (self.is_application and source_file_path.name == MAIN_SOURCE_NAME):
                binary_file_path = pathlib.PurePath(str(self.root_folder / BINARY_FOLDER) + "/" + source_file_path.stem + ".o")

                extra_options = self.include_options + " " + get_custom_options(self.root_folder)
                self.targets.append(compiled_object_factory(source_file_path, binary_file_path, extra_options))
            else:
                has_main = True

        if has_main:
            source_file_path = source_folder / MAIN_SOURCE_NAME
            print(source_file_path)
            executable_file_path = pathlib.PurePath(str(self.root_folder / BINARY_FOLDER) + "/" + MAIN_EXEC_NAME)

            source_targets = [Target(source_file_path)]
            for component in self.dependencies + [self]:
                source_targets.extend(component.targets)

            extra_options = self.include_options + " " + get_custom_options(self.root_folder)
            self.targets.append(compiled_executable_factory(source_targets, executable_file_path, extra_options))

    def check_mustbemade (self):
        for dependency in self.dependencies:
            if dependency.check_mustbemade():
                return True
        for target in self.targets:
            if target.check_mustbemade():
                return True
        return False

    def make (self):
        for dependency in self.dependencies:
            if dependency.check_mustbemade():
                dependency.make()
        for target in self.targets:
            if target.check_mustbemade():
                target.make()

########## build setup ##########

components = { }

def get_component (path_to_component):
    try:
        return components[path_to_component]
    except KeyError:
        return Component(path_to_component)

def make_application (name):
    application = get_component(APPLICATION_FOLDER / name)
    application.make()

def run_application (name):
    run_command("./" + str(APPLICATION_FOLDER / name / BINARY_FOLDER / MAIN_EXEC_NAME))

def clean ():
    for binary_folder in ROOT_FOLDER.glob("**/" + BINARY_FOLDER):
        run_command("rm " + str(binary_folder) + "/*")

########## argv parsing ##########

USAGE = """ usage: python """ + sys.argv[0] + """ <target>
For more information, use python """ + sys.argv[0] + """ @help """

def print_help ():
    print("usage: python " + sys.argv[0] + " <target>")
    print("<target> can be the name of an application you want to compile,")
    print("or one of these special targets starting with @:")
    print("@help: display this help message")
    print("@clean: delete all build output files")
    print("@create_application: create an application folder as needed for the build setup")
    print("@create_system: create a system folder as needed for the build setup")
    print("@create_library: create a library folder as needed for the build setup")
    print("@build_and_run: run an application and build it if nessesary")
    print("@run: run an application")
    print()
    print("you can also create an overlay python script at .build/overlay.py")
    print("in there, you can overwrite anything that is defined in the build setup scripts.")
    print("just read through the scripts to see what you want to change :D")
    print("this is useful because you can add it to your .gitignore file.")

class Creator:
    def __init__ (self, folder):
        self.folder = folder

    def __call__ (self):
        try:
            component_name = sys.argv[2]
        except IndexError:
            print("This special target needs an extra argument: the name of the component to create.")
            sys.exit(2)
        component_folder = self.folder / component_name
        run_command("mkdir -p " + str(component_folder / SOURCE_FOLDER))
        run_command("mkdir -p " + str(component_folder / HEADER_FOLDER))
        run_command("mkdir -p " + str(component_folder / BINARY_FOLDER))
        print("Don't forget to add the component to the dependencies tree, even if it does not have any.")

def make_run_from_argv ():
    try:
        component_name = sys.argv[2]
    except IndexError:
        print("This special target needs an extra argument: the name of the component to create.")
        sys.exit(2)
    make_application(component_name)
    run_application(component_name)

def run_from_argv ():
    try:
        component_name = sys.argv[2]
    except IndexError:
        print("This special target needs an extra argument: the name of the component to create.")
        sys.exit(2)
    run_application(component_name)

SPECIAL_TARGETS = {
    "@help" : print_help,
    "@clean" : clean,
    "@create_application" : Creator(APPLICATION_FOLDER),
    "@create_system" : Creator(SYSTEM_FOLDER),
    "@create_library" : Creator(LIBRARY_FOLDER),
    "@build_and_run" : make_run_from_argv,
    "@run" : run_from_argv
}

def parse_argv (argv):
    if len(argv) < 2:
        print(USAGE)
        sys.exit(2)
    target_arg = argv[1]
    if target_arg[0] == "@":
        try:
            SPECIAL_TARGETS[target_arg]()
        except KeyError:
            print(USAGE)
            sys.exit(2)
    else:
        make_application(target_arg)

########## importing overlay ##########

try:
    from overlay import *
except ImportError:
    pass

########## main entry point ##########

if __name__ == "__main__":
    parse_argv(sys.argv)
