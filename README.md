TsukiBot - A hand made C++ IRC bot!
-----------------------------------

This bot is my second attempt at making a C++ IRC bot. Currently this bot joins a channel on Freenode and accepts commands to join additional channels,plus give tea.

I plan to make a plugin system for this bot to do things like show weather,make jokes or serve tea,do some AI shit,remind people of things,google,show youtube links,give the appropriate description of links,sing songs at the appropriate moments,etc.
As they say,one at a time ;-)

How to Compile
--------------

First create a folder,and from that folder,try this(assuming you are using cli,or else for Windows use TortoiseGit or something similar):-

```
git pull -v https://github.com/OtakuSenpai/TsukiBot.git
```

As of writing this, this bot uses LibSDL2-net headers to connect to the server.

If your on linux,you hav to download the LibSDL2 and LibSDL2-net development packages. Plus you 
also have to get the shared library packages for both LibSDL2 and LibSDL2-net. You will also need the cmake packages for your system to 
build the bot. Also for debugging,you need to get "libsdl2-net-dbg" package. The make package is for those who don't already have the make utility in
their system.

For Ubuntu or Debian,run this command:

```
sudo aptitude install libsdl2-2.0-0 libsdl2-net-2.0-0 libsdl2-dev libsdl2-net-dev cmake libsdl2-net-dbg make

```
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

A lil googling helps too ;)

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
3) More will be added on notice.

License
-------
```

 Distributed under the Mozilla Public License, Version 3.0.
    (See accompanying file LICENSE_1_0.txt or copy at
         https://www.mozilla.org/en-US/MPL/2.0/)

```
