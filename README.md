TsukiBot - A hand made C++ IRC bot!
-----------------------------------

This bot is my second attempt at making a C++ IRC bot. Currently this bot joins a channel on Freenode and accepts commands to join additional channels,plus give tea.

I plan to make a plugin system for this bot to do things like show weather,make jokes or serve tea,mock someone,sing songs at the appropriate moments,etc.

How to Compile
--------------

First create a folder,and from that folder,try this(assuming you are using cli,or else for Windows use TortoiseGit or something similar):-

```
git pull -v https://github.com/OtakuSenpai/TsukiBot.git
```

As of writing this, this bot uses LibSDL2-net headers to connect to the server.

If your on linux,you hav to download the LibSDL2 and LibSDL2-net development packages. Plus you 
also have to get the shared library packages for both LibSDL2 and LibSDL2-net. You will also need the cmake packages for your system to build the bot.

For Ubuntu or Debian,run this command:

```
sudo aptitude install libsdl2-2.0-0 libsdl2-net-2.0-0 libsdl2-dev libsdl2-net-dev cmake

```
For Windows,you have to get the required LibSDL2 packages from this two links:-
1) https://www.libsdl.org/download-2.0.php
2) https://www.libsdl.org/projects/SDL_net/

Then, after extracting them to a "said" directory,add that directory to your path from Settings.
Here's some useful link on it, 

1) https://superuser.com/questions/949560/how-do-i-set-system-environment-variables-in-windows-10 (For Win10)
2)https://superuser.com/questions/502358/easier-way-to-change-environment-variables-in-windows-8 (For Win8)
3)https://stackoverflow.com/questions/23400030/windows-7-add-path (For Win7)
 
Also for Cmake,check this links,

1)https://cmake.org/install/
2)https://stackoverflow.com/questions/9878225/using-cmake-on-windows-for-c

A lil googling helps too ;)

Then you have to add another library,which is a plugin system I made during my summer vacations of 2017. It's name is Tryx Plugin System, and it's licensed under MIT License.

Create a new folder,one inside the other folder,and inside that new folder,type this(again,if you are on Windows use TortoiseGit):-

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

Your executable should be inside the bin directory of TsukiBot folder.Now enjoy ;) !!

Future Possibilities
--------------------

Currently the bot is in its primary stages,I could like to make the project into a Bot framework where I can just inherit from the Bot class and make a customised bot for myself.

```
class MyBot: public Bot{
public:
   MyBot(){}
   ~MyBot(){}
   //now the functions to do various stuff
   ...
```
However,such ideas have to wait for a bit since I won't be working on the code for a two months(till June,2017).But the possibilities with this project remain.

License
-------
```

 Distributed under the Mozilla Public License, Version 3.0.
    (See accompanying file LICENSE_1_0.txt or copy at
         https://www.mozilla.org/en-US/MPL/2.0/)

```
