#include <string>
#include <iostream>
#include <Store2.h>
#include <vector>
#include <MyClass.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(){

  Store s(true,0); //instansiating store
  
  //creating example stroage objects
  int a=3;
  double b=654.7;
  std::string c="hello";
  std::vector<int> v;
  // initialize random seed: 
  srand (time(NULL));
  
  for (int i=0;i<10;i++){
    v.push_back( rand() % 10000 + 1);
  }
  
  MyClass myclass(a,b,c,v); // custom class example
  std::vector<MyClass> myvec; //vector of custom class
  for (int i=0;i<10;i++){
    myvec.push_back(myclass);
  }
  
  Store s3(true,0); //nested store example
  
  // filling store
  
  s.Set("a",a);
  s.Set("b",b);
  s.Set("c",c);
  s.Set("d",v);
  s.Set("myclass",myclass);
  s.Set("myvec",myvec);
  s3.Set("a",a);
  s.Set("store",s3); //nested store
    
  // saving store
  std::string outfile="./outfile";
  s.Save(outfile);
    
  /// loading store from file
  Store s2(true,0);
  s2.Initialise(outfile);
    
  int a2=0;
  double b2=0;
  std::string c2;
  std::vector<int> v2;
  MyClass myclass2;
  std::vector<MyClass> myvec2;
  Store xstore(true,0);
  int x;
    
  // geting variables from store
  s2.Get("a",a2);
  s2.Get("b",b2);
  s2.Get("c",c2);
  s2.Get("d",v2);
  s2.Get("myclass",myclass2);
  s2.Get("myvec",myvec2);
  s2.Get("store",xstore);
  xstore.Get("a",x);
  //rint out to confirm

  std::cout<<"a="<<a2<<" : "<<(a==a2)<<std::endl;
  std::cout<<"b="<<b2<<" : "<<(b==b2)<<std::endl;
  std::cout<<"c="<<c2<<" : "<<(c==c2)<<std::endl;
  for(int i=0;i<v2.size();i++){
    std::cout<<"v["<<i<<"]="<<v2.at(i)<<" : "<<(v.at(i)==v2.at(i))<<std::endl;
  }
  std::cout<<"myclass a="<<myclass2.a<<" : "<<(myclass.a==myclass2.a)<<std::endl;
  std::cout<<"myclass b="<<myclass2.b<<" : "<<(myclass.b==myclass2.b)<<std::endl;
  std::cout<<"myclass c="<<myclass2.c<<" : "<<(myclass.c==myclass2.c)<<std::endl;
  std::cout<<"myclass v[0]="<<myclass2.v.at(0)<<" : "<<(myclass.v.at(0)==myclass2.v.at(0))<<std::endl;
  std::cout<<"myvec size="<<myvec2.size()<<" : "<<(myvec.size()==myvec2.size())<<std::endl;
  std::cout<<"myvec[0].a="<<myvec2.at(0).a<<" : "<<(myvec.at(0).a==myvec2.at(0).a)<<std::endl;
  std::cout<<"nested store a"<<x<<" : "<<(a==x)<<std::endl;

  //s2.Print();

  return 0;

}
