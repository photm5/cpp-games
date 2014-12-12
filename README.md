# cpp-games

#### A packman game repo I left here for historical purposes

This repository is abandoned. I am reimplementing the game in [a different
repository][new-packman].

[new-packman]: https://github.com/firecoders/packman

## template

This Repository uses [my c++ project template][cpp-template]

[cpp-template]: https://github.com/shak-mar/cpp-template

## history

I started this repository with nothing particular in mind, I just wanted to play
around with SFML. But then I had the idea of making a packman game, which is
what I did.

Later on, I developed [2D-engine][2D-engine], a C++ 2D game development library
collection. I think it is a lot better than what you can find in the `system/`
and `library/` folders of this repo. So I decided to port packman onto it, and
abandoned this repo.

[2D-engine]: https://github.com/firecoders/2D-engine

## try it out!

#### requirements

* SFML 2.1
* python 3
* a gcc version that doesn't have problems with looser throw specifiers (eg
  `4.9.2`)

I only tried this out on [arch linux][arch-linux].

[arch-linux]: https://www.archlinux.org/

Download it by cloning the repository:

```sh
git clone https://github.com/shak-mar/cpp-games.git
```

or just download a [tarfile][tarfile] or [zipfile][zipfile].

[tarfile]: https://github.com/shak-mar/cpp-games/archive/master.tar.gz
[zipfile]: https://github.com/shak-mar/cpp-games/archive/master.zip

Build and run it with my build setup:

```sh
./build.py @build_and_run packman
```

You will end up in a splashscreen (a 16x16 yellow placeholder :D), press space
to continue into the actual game.

The level you will end up in is not that impressive and fun at all. To change
it, just edit [application/packman/res/levels/example.txt][example-level]. It
should be pretty self-explanatory.

[example-level]: https://github.com/shak-mar/cpp-games/blob/master/application/packman/res/levels/example.txt
