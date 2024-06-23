//  self

    #include "singleton.h"


//  c++

    #include <iostream>

    using namespace std;



void SingletonBase :: Check (void * ptr)
{
    if (ptr == nullptr)
    {
        cerr << "Singleton: can't allocate instance" << endl;
        exit (1);
    }
}
