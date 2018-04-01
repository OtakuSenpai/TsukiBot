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

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#define TSUKI_SOURCE 1

#include "config.hpp"
#include "sharedlib.hpp"

#include <string>
#include <functional>

namespace Tsuki {

  // Representation of a plugin
  class Plugin {
    public: 
       
       //Signature for the plugin's registration function
       typedef BasePlugin* (*PluginFactoryFunc)();
       //Signature to query for plugin texts
       typedef const char* (*Plugin_TextFunc)();
       
       // Parameterized ctor to load a plugin dll and initiate it inside
       // the class object.Used as the primary way of loading plugins
       // Parameters are:-
       // SharedLib::Handle handle - A handle which is passed from the 
       // Kernal class.It helps in loading the function pointers.
       // std::string& filename - The filename to the dynamic library.
       Plugin(SharedLib::Handle& handle,const std::string &filename);
       
       // Copy ctor for constructing a plugin from one that has already 
       // been loaded.Required to provide correct semantics for storing 
       // plugins in an STL map container.
       Plugin(const Plugin &other);
       Plugin(const Plugin* other);
       
       // Unloads the plugin, unloading its library when no more 
       // references to it exist.
       ~Plugin() {}

       // Gets a text function handle from the dynamic library and 
       // returns it. If found then returns it,else returns nullptr.
       Plugin::Plugin_TextFunc getTextData(SharedLib::Handle handle,
                                          const char* funcname,
                                          const std::string& filename);
       
       // Gets a PluginInterface object from the dynamic library.
       // If found,then returns it,else returns nullptr.
       Plugin::PluginFactoryFunc getNewPlugin(SharedLib::Handle handle,
                                              const char* funcname,
                                              const std::string& filename);
                                          
       std::string getName() const { return pluginName; } // Get name.
       std::string getType() const { return pluginType; } // Get type.
       std::string getVers() const { return pluginVersion; } // Get version.
       std::string getFilename() const { return filename; } // Get filename. 
       PluginFactoryFunc getFuncHandle() const { // Get the function handle
         return funcHandle;
       }
       
       void setName(const char* name); // Set name.
       void setName(const std::string& name);
       void setType(const char* type); // Set type.
       void setType(const std::string& type);
       void setVers(const char* vers); // Set version 
       void setVers(const std::string& vers);
       void setFileName(const char* fname); // Set filename
       void setFileName(const std::string& fname);
         
       //Creates a copy of the plugin instance.
       Plugin &operator =(const Plugin &other);
       
    private:
       
       std::string pluginName;
       std::string pluginType;
       std::string pluginVersion;
       std::string filename;
       PluginFactoryFunc funcHandle;
     
  };
 
} 

#endif 








