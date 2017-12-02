///////////////////////////////////////////////////////////////////////////////////////////////
/////////////// Universal binary store created by Dr. Benjamin Rirchards (b.richards@qmul.ac.uk)
//////////////////////////////////////////////////////////////////////////////////////////////


#ifndef STORE_H
#define STORE_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <typeinfo> 

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>


class Store{
  
 public:
  
 Store(bool typechecking=false, int format=0): m_typechecking(typechecking),m_format(format) {findheader();} // format 0=binary, 1=text.
 Store(std::map<std::string,std::string> invariables):m_variables(invariables){findheader();}
 Store(std::map<std::string,std::string> invariables, std::map<std::string,std::string> ininfo):m_variables(invariables), m_type_info(ininfo){findheader();}
  bool Initialise(std::string filename, int type=0); //type 0=boost archive, config file 
  void JsonParser(std::string input); 
  void Print();
  void Delete();
  void Remove(std::string key);
  void Save(std::string fimename);
  std::string Type(std::string key);
  
  template<typename T> bool Get(std::string name,T &out){
    
    if(m_variables.count(name)>0){
      if(m_type_info[name]==typeid(out).name() || !m_typechecking){

	std::stringstream stream(m_variables[name]);
	
	stream.str(m_archiveheader+stream.str());
	if(!m_format){
	  boost::archive::binary_iarchive ia(stream);
	  ia & out;
	}
	else{
	  boost::archive::text_iarchive ia(stream);
	  ia & out;
	}
	
	return true;
      }
      else return false;
    }
    
    else return false;
    
  }
  
  template<typename T> void Set(std::string name,T in){
    std::stringstream stream;
    
    if(!m_format){
      boost::archive::binary_oarchive oa(stream);
      oa & in;
      stream.str(stream.str().replace(0,40,""));
    }
    else{
      boost::archive::text_oarchive oa(stream);
      oa & in;
      stream.str(stream.str().replace(0,28,""));
    }
    
    
    m_variables[name]=stream.str();
    if(m_typechecking) m_type_info[name]=typeid(in).name();

  }
  
  std::string* operator[](std::string key){
    return &m_variables[key];
  }
  
  template<typename T> void operator>>(T& obj){
    
    std::stringstream stream;
    stream<<"{";
    bool first=true;
    for (std::map<std::string,std::string>::iterator it=m_variables.begin(); it!=m_variables.end(); ++it){
      if (!first) stream<<",";
      stream<<"\""<<it->first<<"\":\""<< it->second<<"\"";
      first=false;
    }
    stream<<"}";
    
    obj=stream.str();
    
  }
  
 private:

  int m_format;
  bool m_typechecking;
  std::string m_archiveheader;
  std::map<std::string,std::string> m_variables;
  std::map<std::string,std::string> m_type_info;
  
  friend class boost::serialization::access;
  
  void findheader(){
    std::string tmp="";
    std::stringstream stream;
    if(!m_format){
      boost::archive::binary_oarchive oa(stream);
      oa & tmp;
    }
    else{
      boost::archive::text_oarchive oa(stream);
      oa & tmp;
    }
    if(!m_format) m_archiveheader=stream.str().substr(0,40);
    else  m_archiveheader=stream.str().substr(0,28);
  } 
  
  template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & m_variables;
      if(m_typechecking)    ar & m_type_info;
    }
  
  
};

#endif
