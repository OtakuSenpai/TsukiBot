LIST:-
----

* [Packages Required](#packages-required)
* [How to compile](#how-to-compile)
  * [Linux Subsystems](#linux-subsystems)
  * [Windows System](#window-system) 

# Packages required

You hav to download the LibSDL2 and LibSDL2 Net development packages. Plus you also have to get the shared library packages for both LibSDL2 and LibSDL2-net. You will also need the cmake packages for your system to
build the bot. Also for debugging,you need to get LibSdl2 Net debugging package. The make package is for those who don't already have the make utility in their posix system. Also Cmake should be above version 3.0.
As of writing this, this bot uses the following libraries and tools:-

* LibSDL2
* LibSDL2 Net
* CMake(greater than or equal too 3.0)
* Make (for posix environments)
* MSVC or MinGW (for windows environment)


# How to Compile:

First,try this(assuming you are using cli,or else for Windows use TortoiseGit or something similar):-

```
git clone https://github.com/OtakuSenpai/TsukiBot.git

```


## Linux Subsystems:

For Ubuntu or Debian,run this command(package names may change with updates):

```
sudo aptitude install libsdl2-2.0-0 libsdl2-net-2.0-0 libsdl2-dev libsdl2-net-dev cmake libsdl2-net-dbg make

```

For Fedora and its dependents,run this command:

```
yum install SDL2 SDL2-debuginfo SDL2-devel SDL2_net SDL2_net-debuginfo SDL2_net-devel cmake make

```
For Slackware,follow these commands in a terminal emulator:-

```
wget https://github.com/sbopkg/sbopkg/releases/download/0.38.1/sbopkg-0.38.1-noarch-1_wsr.tgz
installpkg sbopkg-0.38.1-noarch-1_wsr.tgz
sbopkg

```

SboPkg is a package manger like synaptic.You open it up,then search for the following and install:-

1) Sdl2(devel,shared libs,debug if your debugging too)
2) Sdl2 net(devel,shared libs,debug if your debugging too)
3) Cmake
4) Make

Now, in the directory which is named TsukiBot, type this command:

```
git clone https://github.com/OtakuSenpai/TryxPS.git
```

Now type these commands:

```
cd TryxPS/
cmake CmakeLists.txt
make
cd ..
```

Now, in the TsukiBot directory, type this command:

```
./compile.sh
```

It's a small script that creates a build directory and makes the project there.
You will find your bin file in the build directory.

## Windows System:

For Windows,you have to get the required LibSDL2 packages from this two links:-
1) https://www.libsdl.org/download-2.0.php
2) https://www.libsdl.org/projects/SDL_net/

Then, after extracting them to a "said" directory,add that directory to your path from Settings.
Here's some useful links on it,

1)https://superuser.com/questions/949560/how-do-i-set-system-environment-variables-in-windows-10

2)https://superuser.com/questions/502358/easier-way-to-change-environment-variables-in-windows-8

3)https://stackoverflow.com/questions/23400030/windows-7-add-path

Also for Cmake,check this links,

1)https://cmake.org/install/

2)https://stackoverflow.com/questions/9878225/using-cmake-on-windows-for-c

A lil googling helps too 😄

Then you have to add another library,which is a plugin system I made during my summer vacations of 2017. It's name is Tryx Plugin System, and it's licensed under MIT License.

Type this inside the "TsukiBot" folder(again,if you are on Windows use TortoiseGit):-

```
git clone https://github.com/OtakuSenpai/TryxPS.git

```
Now,in the folder which contains TryxPS,run this two commands,

```
cmake CMakeLists.txt
make

```

Now,go back one directory and run this commands from the directory containing TsukiBot(remember,the TryxPS folder must be inside the directory containing TsukiBot),

```
mkdir build && cd build/
cmake ..
make
cp bin/tsukibot tsukibot

```

Your executable should be inside the "build" directory of "TsukiBot" folder. Now enjoy ;) !!
