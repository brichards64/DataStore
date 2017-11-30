#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
#include <vector>

class MyClass
{
  
 private:
  friend class boost::serialization::access;
  
    template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
	ar & a;
	ar & b;
	ar & c;
	ar & v;
      }

 public:
    int a;
    double b;
    std::string c;
    std::vector<int> v;
    
    MyClass(){};
     MyClass(int ina, double inb, std::string inc, std::vector<int> inv) :a(ina), b(inb), c(inc), v(inv){}
    
};

#endif
