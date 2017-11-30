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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>


class Store{

 public:
  
  Store();
 Store(std::map<std::string,std::string> invariables):m_variables(invariables){}
  bool Initialise(std::string filename);
  void Print();
  void Delete();
  void Remove(std::string key);
  void Save(std::string fimename);
  
  
  template<typename T> bool Get(std::string name,T &out){
    
    if(m_variables.count(name)>0){

      std::stringstream stream(m_variables[name]);
      boost::archive::binary_iarchive ia(stream);
      ia & out;
      return true;
    }
    
    else return false;
    
  }
  
  template<typename T> void Set(std::string name,T in){
    std::stringstream stream;
    boost::archive::binary_oarchive oa(stream);
    oa & in;
    m_variables[name]=stream.str();
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
  
  std::map<std::string,std::string> m_variables;
  friend class boost::serialization::access;

      template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	  ar & m_variables;
	}
      
};

#endif
