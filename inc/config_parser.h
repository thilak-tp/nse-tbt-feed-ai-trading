//Implicit Header files
#include<unordered_map>
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>

// A class to handle config parsing for the appication
class ConfigParser {
  
  // A map to store the key value pair
  std::unordered_map<std::string, std::string> config;  
  
  public:
  
  // A function that loads the config file and saves the key and value in a map
  bool load(std::string &filename) {

    std::ifstream file(filename);
    
    // If the file doesn't exit, return false
    if(!file) return false;

    std::string line;
    
    //Read the file line by line
    while(std::getline(file, line)){
      
      // If the file is empty or it starts with the comment symbol #, continue
      if(line.empty() || line[0] == '#') continue;

      auto pos = line.find('=');

      //Check if npos was returned in the last find call and if yes, continue
      if(pos == std::string::npos) continue;
      
      // Extract the key from the line
      std::string key = trim(line.substr(0,pos));
      // Extract the valeu from the line
      std::string value = trim(line, substr(pos + 1));
      
      //Store the key in am unordered map
      condig[key] = value;
    }
    
    return true;
  }
  

}
