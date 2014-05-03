# Packman Repository

## Template

This Repository uses [my c++ project template][cpp-template]

[cpp-template]: github.com/shak-mar/cpp-template

## Packman

I started this repository with nothing particular in mind, I just wanted to play
around with SFML. But then I had the idea of making a packman game, which is
what I did. Now this is my packman repository, but I might add some other games
later.

Download it by running

    $ git clone --depth 1 https://github.com/shak-mar/cpp-games

You need to create some missing folders, git doesn't store them because they are
empty. You can do it with my build setup:

    $ python build.py @create_application packman
    $ python build.py @create_system gamelogic
    $ python build.py @create_system GUI

Build and run it with my build setup:

    $ python build.py @build_and_run packman

You will end up in a splashscreen (currently a 16x16 yellow placeholder :D),
press space to continue into the actual game.
