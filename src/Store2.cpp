#include "Store2.h"


Store::Store(){}


bool Store::Initialise(std::string filename){

  std::ifstream file(filename.c_str());
  if(file.is_open(), std::ios::binary){
    boost::archive::binary_iarchive ia(file);

    ia & m_variables;
    file.close();
    return true;
  }
  else return false;
}


void Store::Print(){

  for (std::map<std::string,std::string>::iterator it=m_variables.begin(); it!=m_variables.end(); ++it){
   
    std::cout<< it->first << " => " << it->second <<std::endl;

  }

}


void Store::Delete(){ 
  
  m_variables.clear();
  
  
}


void Store::Remove(std::string key){

  for (std::map<std::string,std::string>::iterator it=m_variables.begin(); it!=m_variables.end(); ++it){

    if(it->first==key){
      m_variables.erase(it);
      break;
    }
  }

}


void Store::Save(std::string filename){

  std::ofstream ofs(filename.c_str());
  boost::archive::binary_oarchive oa(ofs);

  oa & m_variables;

  ofs.close();
  
}
