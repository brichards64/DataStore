#include <string>
#include <iostream>
#include <Store2.h>
#include <vector>
#include <MyClass.h>

int main(){

  Store s; //instansiating store

  //creating example stroage objects
  int a=3;
  double b=654.7;
  std::string c="hello";
  std::vector<int> v;
  for (int i=0;i<10;i++){
    v.push_back(i);
  }
  MyClass myclass(a,b,c,v); // custom class example
  std::vector<MyClass> myvec; //vector of custom class
  for (int i=0;i<10;i++){
    myvec.push_back(myclass);
  }
  

  // filling store
  
  s.Set("a",a);
  s.Set("b",b);
  s.Set("c",c);
  s.Set("d",v);
  s.Set("myclass",myclass);
  s.Set("myvec",myvec);
  
  // saving store
  std::string outfile="./outfile";
  s.Save(outfile);
  


  /// loading store from file
  Store s2;
  s2.Initialise(outfile);

  int a2;
  double b2;
  std::string c2;
  std::vector<int> v2;
  MyClass myclass2;
  std::vector<MyClass> myvec2;
    
  // geting variables from store
  s2.Get("a",a2);
  s2.Get("b",b2);
  s2.Get("c",c2);
  s2.Get("d",v2);
  s2.Get("myclass",myclass2);
  s2.Get("myvec",myvec2);


  //print out to confirm

  
  std::cout<<"a="<<a2<<std::endl;
  std::cout<<"b="<<b2<<std::endl;
  std::cout<<"c="<<c2<<std::endl;
  for(int i=0;i<v2.size();i++){
    std::cout<<"v["<<i<<"]="<<v2.at(i)<<std::endl;
  }
  std::cout<<"myclass a="<<myclass2.a<<std::endl;
  std::cout<<"myclass b="<<myclass2.b<<std::endl;
  std::cout<<"myclass c="<<myclass2.c<<std::endl;
  std::cout<<"myclass v[0]="<<myclass2.v.at(0)<<std::endl;
  std::cout<<"myvec size="<<myvec2.size()<<std::endl;
  std::cout<<"myvec[0].a="<<myvec2.at(0).a<<std::endl;

  return 0;

}
