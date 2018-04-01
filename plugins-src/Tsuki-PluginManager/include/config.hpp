///////////////////////////////////////////////////////////////////////////////////
// TsukiBot IRC Bot made by Avra Neel Chakraborty                                //
//                                                                               //
// Copyright (c) 2018 Avra Neel Chakraborty                                      //
//                                                                               //
// This Source Code Form is subject to the terms of the Mozilla Public           //
// License, v. 2.0. If a copy of the MPL was not distributed with this           //
// file, You can obtain one at http://mozilla.org/MPL/2.0/.                      //
//                                                                               //
// The above copyright notice and this permission notice shall be included in    //
// all copies or substantial portions of the Software.                           //
///////////////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "BasePlugin.hpp"

//Platform recognition

#if defined WIN32 || defined _WIN32 
   #define TSUKI_WIN32 1
#else
   #define TSUKI_LINUX 1
#endif

//----------------------------------------------------------------------------//

//Decides whether to import symbols from a dll or export to a dll.
//TRYX_SOURCE and TRYX_STATICLIB must be defined in the source files to make
//the actual exporting or importing work.                                     

//The macro code is basically checking whether you statically linked
//the library or not. Otherwise, it checks whether to import or
//export functions for usage.

#if defined _WIN32 
   #ifdef TSUKI_STATICLIB
      #define TSUKI_API
   #else
      //Define this in the derived plugin 
      #ifdef TSUKI_SOURCE 
         //If we are building the DLL,export the symbols tagged like this
         //Add this before a symbol to be exported
         #define TSUKI_API_EXP __declspec(dllexport)
         //This sets the name of the new plugin dll
         #define TSUKI_DECL_PLUGIN(x) extern "C"{__declspec(dllexport) \
            Tsuki::BasePlugin* makePlugin(){ return new x;}}
         //Add this in the source file of the derived plugin
         #define SET_PLUGIN_VERS(x) extern "C"{__declspec(dllexport) \
            const char * getPluginVers(){ return x;}}
         //Add this in the source file of the derived plugin
         #define SET_PLUGIN_NAME(x) extern "C"{__declspec(dllexport) \
            const char * getPluginName(){ return x;}}
         //Add this in the source file of the derived plugin
         #define SET_PLUGIN_TYPE(x) extern "C"{__declspec(dllexport) \
            const char * getPluginType(){ return x;}}   
      #else
      // If we are consuming the DLL, import the symbols tagged like this
         #define TSUKI_API_IMP __declspec(dllimport)
      #endif
   #endif
#elif defined __GNUC__  
   #if defined TSUKI_STATICLIB
      #define TSUKI_API  
   #else
      #if defined TSUKI_SOURCE
         #define TSUKI_API_EXP __attribute__((visibility("default")))
         #define TSUKI_DECL_PLUGIN(x) extern "C"{__attribute__((visibility("default"))) \
            Tsuki::BasePlugin* makePlugin(){ return new x; }}
         #define SET_PLUGIN_VERS(x) extern "C"{__attribute__((visibility("default"))) \
             const char * getPluginVers(){ return x;}}
         #define SET_PLUGIN_NAME(x) extern "C"{__attribute__((visibility("default"))) \
             const char * getPluginName(){ return x;}}
         #define SET_PLUGIN_TYPE(x) extern "C"{__attribute__((visibility("default"))) \
            const char * getPluginType(){ return x;}}      
      #else
         #define TSUKI_API_IMP __attribute__ ((visibility ("default")))
      #endif
   #endif
 #else
   #error Unknown compiler, please implement shared library macros!!!             
#endif   
      
//----------------------------------------------------------------------------//

#endif // CONFIG_HPP
