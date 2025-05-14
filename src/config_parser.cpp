// This source file contains a config parser class implementation to deal with simple config parsing
#include "config_parser.h" 
  
  // A function that loads the config file and saves the key and value in a map
  bool ConfigParser::load(const std::string &filename) {
  
    std::string appRootPath = getenv("CFG_DIR");
    if(appRootPath.empty()){
      std::cout<<"Kindly source the environment script"<<std::endl;
      return FAILURE;
    }
    std::cout << "Root path: " << appRootPath << std::endl;
    std::string filepath = appRootPath + "/"+ filename;
    std::cout<<"The file path "<<filepath<< std::endl;
    std::ifstream file(filepath);
    
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
      std::string key = line.substr(0,pos);
      // Extract the valeu from the line
      std::string value = line.substr(pos + 1);
      
      //Store the key in am unordered map
      config[key] = value;
    }
    
    return true;
  }
  
  // A function to get the stored value when passing a key
  std::string ConfigParser::getValue(std::string key)
  {
    return config[key];
  }  

