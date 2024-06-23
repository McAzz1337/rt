//  self

    #include "thrd-factory.h"


//  c++

    #include <iostream>

    using namespace std;



ThrdFactoryBasePtr ThrdFactoryBase::InstancePtr = nullptr;



ThrdPtr ThrdFactoryBase :: make ()
{
    if (! InstancePtr)
    {
        cerr << "no thread class registered" << endl;
        exit (1);
    }

    return InstancePtr->Make();
}
