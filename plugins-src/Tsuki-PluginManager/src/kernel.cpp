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

#define TSUKI_SOURCE 1

#include "kernel.hpp"
#include <cstring> 

#ifdef TSUKI_LINUX
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#elif TSUKI_WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
#else
#error Shared library system supported for Windows and Linux only!!!
#endif

namespace Tsuki {
  
  void Kernel :: loadPlugins(const std::string& path,bool addIt) {
    #ifdef TSUKI_WIN32
      if(!addIt)
        return;
      WIN32_FIND_DATA fd;
      char fname[1024];
      strcpy(fname,const_cast<char*>(path.c_str()));
      size_t len=strlen(fname);
      if(fname[len-1]=='/' || fname[len-1]=='\\')  strcat(fname,"*.dll");
      else strcat(fname,"\\*.dll");
      HANDLE hFind = FindFirstFile(fname, &fd); 
      if (hFind == INVALID_HANDLE_VALUE) 
      {
        FindClose(hFind); return;
      } 
      Plugin* curPlugin;
      HINSTANCE dllHandle = nullptr;  
      do 
      { 
        try
        {
          if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
          {                                       
            dllHandle = SharedLib::Load(fd.cFileName);
            if (dllHandle != nullptr) 
            {
              curPlugin = new Plugin(static_cast<SharedLib::Handle>
                                    (dllHandle),std::string(fd.cFileName));
              loadedPlugins.emplace(std::string(curPlugin->getName()), curPlugin);                      
              delete curPlugin; curPlugin = nullptr;
            }
            FreeLibrary(dllHandle);
          }
        }
        catch(...)
        {
          if (dllHandle != NULL) FreeLibrary(dllHandle);
          throw std::runtime_error("kernel.cpp : Line 34, \
                 error in finding .dlls in the directory.");
        }
      } while (FindNextFile(hFind, &fd));
      FindClose(hFind);
    #endif
   
    #ifdef TSUKI_LINUX
      if(!addIt)
        return;
      DIR *dp;
      struct stat sb;
      struct dirent *dirp;
     
      try {   
        if((dp  = opendir(path.c_str())) == nullptr) {
          throw std::runtime_error("kernel.cpp : Line 79,error in the operation.");
        }
      }
      catch(std::exception& e) {
        std::cout<<"Caught exception: "<<e.what(); 
      }
    
      std::string filepath,temp,temp2;
      Plugin* curPlugin;
      SharedLib::Handle dllHandle; 
      while((dirp = readdir(dp)) != nullptr) {
        try {
          if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0) continue;
          else { 
            temp.assign(dirp->d_name);
            filepath = path + std::string("/") + temp;
          }     
          if(stat( filepath.c_str(), &sb ) && (S_ISDIR( sb.st_mode ))) continue;              
          else if(stat(filepath.c_str(), &sb) == 0 && S_ISREG(sb.st_mode))
          { 
            dllHandle = SharedLib::Load(filepath);
            if(dllHandle != nullptr) {
              curPlugin = new Plugin(static_cast<SharedLib::Handle&>
                                  (dllHandle),filepath);
              temp2 = curPlugin->getName();
              loadedPlugins.emplace(temp2,curPlugin);
              delete curPlugin; curPlugin = nullptr;
            }
          }
          filepath.clear();
        } 
        catch(std::exception& e)
        {
          if (dllHandle != nullptr) SharedLib::Unload(dllHandle);
          std::cerr<<"Caught exception: "<<e.what();
        } 
      }     
      closedir(dp);
    #endif
  }    

  void Kernel :: loadPlugin(const std::string& path) {
    try {
      SharedLib::Handle dllHandle;
      Plugin* curPlugin;
      dllHandle = SharedLib::Load(path);
      if(dllHandle !=nullptr) {
        curPlugin = new Plugin(static_cast<SharedLib::Handle&>
                            (dllHandle),path);
        std::string temp = curPlugin->getName();
        loadedPlugins.emplace(temp,curPlugin);
      }
    }
    catch(std::exception& e) {
      std::cout<<"Caught exception: \n"<<e.what();
    }
  }

  void Kernel :: unloadPlugins() {
    try {
      loadedPlugins.clear();
    }
    catch(std::exception& e) {
      std::cout<<"Caught exception: \n"<<e.what();
    }
  }  

  BasePlugin* Kernel :: getFuncHandle(const std::string& iden) {
    BasePlugin* p_plugin = nullptr;
    try {
      for(auto&& i : loadedPlugins) {
        if(i.first == iden) {
          Plugin::PluginFactoryFunc temp = i.second.get()->getFuncHandle();
          p_plugin = temp();
        }
      }
    }
    catch(std::exception& e) {
      std::cout<<"Caught exception: \n"<<e.what();
    }
    if(p_plugin != nullptr)
      return p_plugin;
    else return nullptr;
  }
  
  int Kernel :: getFuncPos (const std::string& iden) const {
    int pos = -1,j = 0;
    std::string tempRet;
    for(auto& i: loadedPlugins) {
      tempRet.clear();
      tempRet = i.first;
      if(tempRet == iden) {
        pos = j; break;
      }
      ++j;
    }
    
    return pos;
  }
  
  int Kernel :: getFuncPos (const char* iden) const {
    int pos = -1,j = 0;
    std::string tempRet,identifier;
    identifier.assign(iden); 
    for(auto& i: loadedPlugins) {
      tempRet.clear();
      tempRet = i.first;
      if(tempRet == iden) {
        pos = j; break;
      }
      ++j;
    }
    
    return pos;
  }  
    
  std::string Kernel :: getPluginName (const int& index) const {
    std::string s;
    int i = 0;
    try {
      for(auto& j: loadedPlugins) {
		if(i == index) { 
		  s = j.first;
		  break; 
		}
	    ++i;
	  } 
    }
    catch(std::exception& e) {
      std::cout<<"Caught exception: \n"<<e.what();
    }
    return s;
  }
} //namespace Tryx
