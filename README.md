TsukiBot - A hand made C++ IRC bot!
-----------------------------------

This bot is my second attempt at making a C++ IRC bot. Currently this bot joins a channel on Freenode and accepts commands to
join additional channels.

I plan to make a plugin system for this bot to do things like show weather,make jokes or serve tea,mock someone,sing songs 
at the appropriate moments,etc.

Libraries Used
--------------

Currently this bot uses LibSDL2-net headers to connect to the server.You have to add to the library path any latest libsdl2-net source. 

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
