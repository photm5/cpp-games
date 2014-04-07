# C++ Project Template

## Directory Layout

This Repository is a template for C++ repositories that I want to make.
The directory layout is made to contain multiple applications in one repository,
so they can share library code.

The layout is divided in three layers:

1. The `library` layer:
   Here are the components that do very general things,
   like move Events around.

2. The `system` layer:
   The components that do most of the project-specific things,
   for example the game engine.

3. The `application` layer:
   The components that are executable,
   when your `system` layer contains a game engine,
   in here might be the actual game you make with it.

Of course, the components can depend on each other:

+ Components of the `application` layer
  can depend on components of all layers.

+ Components of the `system` layer
  can depend on components of the `system` and `library` layer.

+ Components of the `library` layer
  can depend on components of the `library` layer.

## Build setup

To support the layout, this repository contains a build setup
(written in python) that can handle it.

It was built with the intention to be used from the command line,
but you can wrap it for use in an IDE. (I didn't try it yet :D)

To try out if it works, run the command

    $ python build.py @help
    usage: python build.py <target>
    <target> can be the name of an application you want to compile,
    or one of these special targets starting with @:
    @help: display this help message
    @clean: delete all build output files
    @create_application: create an application folder as needed for the build setup
    @create_system: create a system folder as needed for the build setup
    @create_library: create a library folder as needed for the build setup
    @build_and_run: run an application and build it if nessesary
    @run: run an application

    you can also create an overlay python script at .build/overlay.py
    in there, you can overwrite anything that is defined in the build setup scripts.
    just read through the scripts to see what you want to change :D
    this is useful because you can add it to your .gitignore file.

I hope it is self explanatory :D

## Compiling

The script uses g++ as a default, but you can configure it to your needs in `.build/config.py`
To try if compiling works, you can follow this example:

    $ python build.py @create_application hello_world
    running command: mkdir -p application/hello_world/src
    running command: mkdir -p application/hello_world/inc
    running command: mkdir -p application/hello_world/bin
    Don't forget to add the component to the dependencies tree, even if it does not have any.
    $ ls * */*
    build.py  README.md

    application:
    hello_world

    application/hello_world:
    bin  inc  src

We now need to add it in the dependencies tree in `.build/config.py`, change it to:

``` python
DEPENDENCIES = {
    APPLICATION_FOLDER / "hello_world" : []
}
```

Yes, I know, `hello_world` has no dependencies,
but this step helps you to not forget adding dependencies.

Now edit the file `application/hello_world/src/main.cpp`:
    
``` c++
#include <iostream>

int main () {
    std::cout << "Hello World!" << std::endl;
}
```

And run these commands to compile and run it:

    $ python build.py hello_world
    running command: g++ application/hello_world/src/main.cpp -I. -Iapplication/hello_world/inc -o application/hello_world/bin/executable
    $ python build.py @run hello_world
    running command: ./application/hello_world/bin/executable
    Hello World!

Or just this single one:
    
    $ python build.py @build_and_run hello_world
    running command: g++ application/hello_world/src/main.cpp -I. -Iapplication/hello_world/inc -o application/hello_world/bin/executable
    running command: ./application/hello_world/bin/executable
    Hello World!

## Configuration

You can modify some configuration settings in `.build/config.py`.
In there, you need to change the dependency tree,
so it resembles the dependencies between your components.
An Example, also shown in `.build/config.py`:

``` python
DEPENDENCIES = {
    APPLICATION_FOLDER / "game" : [
        SYSTEM_FOLDER / "engine",
        LIBRARY_FOLDER / "events"
    ],
    SYSTEM_FOLDER / "game" : [
        LIBRARY_FOLDER / "events"
    ]
}
```

You can create an overlay script at `.build/overlay.py`.
In there, you can re-write the build setup scripts.

For example, to print the commands that would be executed instead of running them,
put this in your `.build/overlay.py` file:

``` python
def run_command (command):
    print("not running command: " + command)
```
