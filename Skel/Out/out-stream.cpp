//  self

    #include "out-stream.h"


//  c++

    #include <iostream>

    using namespace std;



OutStream :: OutStream ()
    : BufPtr (nullptr)
    , OstrPtr (& cout)
{
}



OutStream :: ~OutStream ()
{
    if (OstrPtr != & cout)
        OstrPtr->flush();
    delete OstrPtr;
    delete BufPtr;
}



void OutStream :: initialize ()
{
    // locale loc ("de_CH");
    // imbue (loc);

    BufPtr = new OutStreamBuf;
    OstrPtr = new ostream (BufPtr);

    connect (BufPtr, & OutStreamBuf::sigOut,
            this, & OutStream::sigOut);
}
