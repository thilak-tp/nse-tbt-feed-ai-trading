// This header contains a config parser class to deal with simple config parsing

//Implicit Header files
#include<unordered_map>
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<filesystem>
#include<stdlib.h>

//Explicit Header files
#include "app_defs.h"

#pragma once 

// A class to handle config parsing for the application
class ConfigParser {
 
  // A map to store the key value pair
  std::unordered_map<std::string, std::string> config;  
  
  public:
  
  // A function that loads the config file and saves the key and value in a map
  bool load(const std::string &filename); 
  
  // A function to get the stored value when passing a key
  std::string getValue(std::string key);

};
