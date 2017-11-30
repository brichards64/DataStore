Alpha build of the binary version of the universal store.  (by Dr. Benjamin Richards [b.richards@qmul.ac.uk])

The universal store can store:
1) All basic types e.g. int, short, long, double, float, bool ......
2) All stl containers e.g maps, vectors, lists .....
3) any custom class that has a boost serialise method (see Example/MyClass)

Please note this is an alpha build so no checking of types exists yet.

Usage can be seen in Example/main.cpp
There is a makefile in Example folder just set your boost install directory.



