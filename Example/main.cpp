#include <string>
#include <iostream>
#include <Store2.h>
#include <vector>
#include <MyClass.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(){

  // initialize random seed:
  srand (time(NULL));

  /////////////////////////////////////////////////////////////
  //Example 1: Simple store and recall
  ////////////////////////////////////////////////////////////
  std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;  
  std::cout<<"Example 1: Simple store and recall"<<std::endl;
  std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;


  //////////////////////////////////////////
  ////// E1 Step1: Creating a store
  /////////////////////////////////////////
  
  
  Store s1(true,0); //instansiating store (bool type checking, output type 0=binary, 1=text, 2=multievent)
  
  //////////////////////////////////////////
  ////// E1 Step2: Creating some basic variables
  /////////////////////////////////////////

  int a=9999;
  double b=654.7;
  int *iptr=new int(6); //can store pointers too

  //// creating some stl containers ///////
  std::string st="hello";
  std::vector<int> v;
  for (int i=0;i<1;i++){
    v.push_back( rand() % 10000 + 1);
  }

  //// creating custom serialisable class ///
  MyClass myclass(a,b,st,v);
  MyClass* myclassptr=new MyClass(a,b,st,v); //can store poitners to custom classes
  std::vector<MyClass> myvec; //can store vectors of custom classes
  for (int i=0;i<10;i++){
    myvec.push_back(myclass);
  }
  
  /////creating nested store /////
  Store s3(true,0); //stores can be saved within stores 

  /////////////////////////////////////////////
  // E1 Step3: Filling stores
  //////////////////////////////////////////////
  
  s1.Set("a",a);
  s1.Set("b",b);
  s1.Set("st",st);
  s1.Set("v",v);
  s1.Set("myclass",myclass);
  s1.Set("myvec",myvec);
  s3.Set("a",a); //filling nested store
  s1.Set("store",s3); //inserting nested store into top level
  s1.SetPtr("iptr",iptr);
  s1.SetPtr("myclassptr",myclassptr);

  //////////////////////////////////////////
  // E1 Step4: Saving store
  //////////////////////////////////////////
  std::string outfile="./outfile";
  s1.Save(outfile);

  
  ///////////////////////////////////////////    
  /// E1 Step5: Loading store from file and recalling variables
  //////////////////////////////////////////

  Store s2(true,0);
  s2.Initialise(outfile);

  
  int a2;
  double b2=0;
  std::string st2;
  std::vector<int> v2;
  MyClass myclass2;
  std::vector<MyClass> myvec2;
  Store s4(true,0);
  int x;
  int* iptr2=0;
  MyClass* myclassptr2=0;
  
  // geting variables from store
  s2.Get("a",a2);
  s2.Get("b",b2);
  s2.Get("st",st2);
  s2.Get("v",v2);
  s2.Get("myclass",myclass2);
  s2.Get("myvec",myvec2);
  s2.Get("store",s4);
  s4.Get("a",x);
  s2.GetPtr("iptr",iptr2);
  s2.GetPtr("myclassptr",myclassptr2);

  
  //Print out to confirm correct outputs
  std::cout<<"a="<<a2<<" : "<<(a==a2)<<std::endl;
  std::cout<<"b="<<b2<<" : "<<(b==b2)<<std::endl;
  std::cout<<"s="<<st2<<" : "<<(st==st2)<<std::endl;
  for(int i=0;i<v2.size();i++){
    std::cout<<"v["<<i<<"]="<<v2.at(i)<<" : "<<(v.at(i)==v2.at(i))<<std::endl;
  }
  std::cout<<"myclass a="<<myclass2.a<<" : "<<(myclass.a==myclass2.a)<<std::endl;
  std::cout<<"myclass b="<<myclass2.b<<" : "<<(myclass.b==myclass2.b)<<std::endl;
  std::cout<<"myclass s="<<myclass2.s<<" : "<<(myclass.s==myclass2.s)<<std::endl;
  std::cout<<"myclass v[0]="<<myclass2.v.at(0)<<" : "<<(myclass.v.at(0)==myclass2.v.at(0))<<std::endl;
  std::cout<<"myvec size="<<myvec2.size()<<" : "<<(myvec.size()==myvec2.size())<<std::endl;
  std::cout<<"myvec[0].a="<<myvec2.at(0).a<<" : "<<(myvec.at(0).a==myvec2.at(0).a)<<std::endl;
  std::cout<<"nested store a="<<x<<" : "<<(a==x)<<std::endl;
  std::cout<<"*iptr="<<*iptr2<<" : "<<((*iptr)==(*iptr2))<<std::endl;
  std::cout<<"*myclassptr.a="<<(*myclassptr2).a<<" : "<<((*myclassptr).a==(*myclassptr2).a)<<std::endl;
  
  //note can also print the contets of a store using
  //s2.Print();


  

  ////////////////////////////////////////
  // Example 2: Pointers
  /////////////////////////////////////////

  std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
  std::cout<<"Example 2: Ponters"<<std::endl;
  std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
  

  ////////////////////////////////////////
  // Example 3: Event Store
  /////////////////////////////////////////

  std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
  std::cout<<"Example 3: Event Store"<<std::endl;
  std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
  
  Store test1(false,2);
  
  test1.Set("a",a);
  unsigned long entries=2;
  test1.Set("TotalEntries",entries);
  
  test1.Save("testfile");
  test1.Delete();
  test1.Set("b",b);
  test1.Save("testfile");
  test1.Delete();
  test1.Set("st",st);
  test1.Save("testfile");
  test1.Delete();
  
  test1.Close();
  
  Store test2(false,2);
  test2.Initialise("testfile");
  
  test2.GetEntry(0);
  int out=0;
  double out2=0;
  std::string pp="";
  
  test2.Get("a",out);
  test2.Get("b",out2);
  test2.Get("st",pp);
  // test2.Print();
  std::cout<<"out="<<out<<std::endl;
  std::cout<<"out2="<<out2<<std::endl;
  std::cout<<"pp="<<pp<<std::endl;
  test2.GetEntry(1);
  test2.Get("a",out);
  out2=0;
  test2.Get("b",out2);
  test2.Get("st",pp);
  //  test2.Print();
  std::cout<<"out="<<out<<std::endl;
  std::cout<<"out2="<<out2<<std::endl;
  std::cout<<"pp="<<pp<<std::endl;
  

  
  return 0;

}
