#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
#include <vector>
#include <SerialisableObject.h>

class MyClass : public SerialisableObject
{
  
 private:
  friend class boost::serialization::access;
  
    template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
	ar & a;
	ar & b;
	ar & s;
	ar & v;
      }

 public:
    int a;
    double b;
    std::string s;
    std::vector<int> v;
    
    MyClass(){};
    MyClass(int ina, double inb, std::string ins, std::vector<int> inv) :a(ina), b(inb), s(ins), v(inv){}
    
    bool Print(){return true;};
    ~MyClass(){}
};

#endif
