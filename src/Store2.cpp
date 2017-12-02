#include "Store2.h"


bool Store::Initialise(std::string filename, int type){

  std::ifstream file(filename.c_str());

  if(type==0){
    if(file.is_open(), std::ios::binary){
      if(!m_format){
	boost::archive::binary_iarchive ia(file);
	ia & m_variables;
	if(m_typechecking)ia & m_type_info;
      }
      else{
	boost::archive::text_iarchive ia(file);
	ia & m_variables;
	if(m_typechecking)ia & m_type_info;
      }
      
      
      file.close();
      return true;
    }
    else return false;
  }
  
  else{
    std::string line;
    
    if(file.is_open()){
      
      while (getline(file,line)){
	if (line.size()>0){
	  if (line.at(0)=='#')continue;
	  std::string key;
	  std::string value;
	  std::stringstream stream(line);
	  if(stream>>key>>value){

	    std::stringstream stream;
	    if(!m_format){
	      boost::archive::binary_oarchive oa(stream);
	      oa & value;
	      stream.str(stream.str().replace(0,40,""));
	    }
	    else{
	      boost::archive::text_oarchive oa(stream);
	      oa & value;
	      stream.str(stream.str().replace(0,28,""));
	    }
	    m_variables[key]=stream.str();

	  }
	}	
      }
      
      file.close();
      return true;
    }
    
    else return false;
  }
  
  
}


void Store::Print(){

  for (std::map<std::string,std::string>::iterator it=m_variables.begin(); it!=m_variables.end(); ++it){
   
    std::cout<< it->first << " => " << it->second <<" : "<<m_type_info[it->first]<<std::endl;

  }

}


void Store::Delete(){ 
  
  m_variables.clear();
  m_type_info.clear();
  
}


void Store::Remove(std::string key){

  for (std::map<std::string,std::string>::iterator it=m_variables.begin(); it!=m_variables.end(); ++it){

    if(it->first==key){
      m_variables.erase(it);
      break;
    }
  }

  if(m_typechecking){
    for (std::map<std::string,std::string>::iterator it=m_type_info.begin(); it!=m_type_info.end(); ++it){
      
      if(it->first==key){
	m_type_info.erase(it);
	break;
      }
    }
  }
  

}


void Store::Save(std::string filename){
  
  std::ofstream ofs(filename.c_str());
  
  if(!m_format){
    boost::archive::binary_oarchive oa(ofs);
    oa & m_variables;
    if(m_typechecking)  oa & m_type_info;
  }
  else{
    boost::archive::text_oarchive oa(ofs);
    oa & m_variables;
    if(m_typechecking)  oa & m_type_info;
  }
 
  
  ofs.close();
  
}

void Store::JsonParser(std::string input){
  
  int type=0;
  std::string key;
  std::string value;
  
  for(std::string::size_type i = 0; i < input.size(); ++i) {
    
    if(input[i]=='\"')type++;
    else if(type==1)key+=input[i];
    else if(type==3)value+=input[i];
    else if(type==4){
      type=0;
      std::stringstream stream;
      if(!m_format){
	boost::archive::binary_oarchive oa(stream);
	oa & value;
	stream.str(stream.str().replace(0,40,""));
      }
      else{
	boost::archive::text_oarchive oa(stream);
	oa & value;
	stream.str(stream.str().replace(0,28,""));
      }
      m_variables[key]=stream.str();
      key="";
      value="";
    }
  }
}


std::string Store::Type(std::string key){

  if(m_type_info.count(key)>0){
    if(m_typechecking) return m_type_info[key];
    else return "?";
  }
  else return "Not in Store";

}
