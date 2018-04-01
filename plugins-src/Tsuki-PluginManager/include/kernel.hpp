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

#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "plugin.hpp"
#include "config.hpp"
#include <string>
#include <map>
#include <memory>
#include <algorithm>

namespace Tsuki {

  //The engine's core
  class Kernel {
    private:
      
      class Node {
        public:
          Node() : _name(), _data() {}
          Node(std::string& name,Plugin* data) : _name(name), _data(new Plugin(data)) {}
          Node(const Node& other) {
            try {
              _name = other.getName();
              _data = other.getData();
            }
            catch(std::exception& e) {
              std::cerr<<"Caught exception: \n"<<e.what();
            }
          }
          Node& operator=(const Node& other) {
            try {
              _name = other.getName();
              _data = other.getData();
            }
            catch(std::exception& e) {
              std::cerr<<"Caught exception: \n"<<e.what(); 
            }
            return *this;
          }
          ~Node() {}
          std::string getName() const{ return _name; }
          std::shared_ptr<Plugin> getData() const{ return _data; }    
        
        private:
          std::string _name;
          std::shared_ptr<Plugin> _data;
      };
        
      //Map of plugins by their associated file names
      std::map<std::string,std::shared_ptr<Plugin>> loadedPlugins;

    public: 
       
       Kernel() : loadedPlugins() {}
       ~Kernel() { unloadPlugins(); }
       Kernel(const std::string& path,bool& doIt) : loadedPlugins() { loadPlugins(path,doIt); }
       
       void loadPlugin(const std::string& path);
         
       // Loads all plugins present in a directory.
       void loadPlugins(const std::string& path,bool addIt);
       
       // Unloads all plugins 
       void unloadPlugins();
       
       //Helper functions
       BasePlugin* getFuncHandle(const std::string& identifier);
       std::string getPluginName (const int& index) const;
       int getFuncPos (const std::string& identifier) const;
       int getFuncPos (const char* identifier) const;
       
       std::map<std::string,std::shared_ptr<Plugin>> getPlugins() { 
		 return loadedPlugins; 
	   }
       int getSize() const{ return loadedPlugins.size(); }
  };

} // namespace Tryx

#endif //KERNEL_HPP
