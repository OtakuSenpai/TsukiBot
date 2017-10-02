TsukiBot - A hand made C++ IRC bot!
-----------------------------------

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0)

[TsukiBot](https://github.com/OtakuSenpai/TsukiBot) is my second attempt at making a C++ IRC bot. Currently this bot joins a channel on Freenode and accepts commands to join additional channels,ping others plus give coffee,and ofc moo!!!

I plan to make a plugin system for this bot to do things like show weather,make jokes or serve tea,do some AI shit,remind people of things,google,show youtube links,give the appropriate description of links,sing songs at the appropriate moments,etc.
As they say,one at a time 😉

How to Compile
--------------

First create a folder,and from that folder,try this(assuming you are using cli,or else for Windows use TortoiseGit or something similar):-

```
git clone https://github.com/OtakuSenpai/TsukiBot.git

```

As of writing this, this bot uses the following libraries and tools:- 

1) LibSDL2
2) LibSDL2 Net
3) CMake(greater than or equal too 3.7)
4) Make (for posix environments)


 You hav to download the LibSDL2 and LibSDL2 Net development packages. Plus you also have to get the shared library packages for both LibSDL2 and LibSDL2-net. You will also need the cmake packages for your system to 
build the bot. Also for debugging,you need to get LibSdl2 Net debugging package. The make package is for those who don't already have the make utility in their posix system. Also Cmake should be above version 3.7.


For Ubuntu or Debian,run this command:

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
1)Sdl2(devel,shared libs,debug if your debugging too)
2)Sdl2 net(devel,shared libs,debug if your debugging too)
3)Cmake
4)Make

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

Create a new folder,name it "TryxPS",one inside the other folder,and inside that new folder("TryxPS"),type this(again,if you are on Windows use TortoiseGit):-

```
git pull -v https://github.com/OtakuSenpai/TryxPS.git

```
Now,in the folder which contains TryxPS,run this two commands,

```
cmake CMakeLists.txt
make

```

Now,go back one directory and run this commands from the directory containing TsukiBot(remember,the TryxPS folder must be inside the directory containing TsukiBot),

```
cmake CMakeLists.txt
make

```

Your executable should be inside the bin directory of TsukiBot folder. Now enjoy ;) !!

Notes
-----

1) The main code of the bot is ready, I just have to implement the plugins now. Things like SSL and proxies will be done in v0.01.
2) Don't use the compile.sh script to compile,use cmake. That script is way outdated. Though the gdb-compile.sh script uses cmake to do the dirty job.
3) This bot was only meant to be used on the Freenode network. Additional servers,if required,will be added in later versions.
4) More will be added on notice. 😜

License
-------

```

 Distributed under the Mozilla Public License, Version 3.0.
    (See accompanying file [`LICENSE`](./LICENSE) or copy at
         https://www.mozilla.org/en-US/MPL/2.0/)

```
