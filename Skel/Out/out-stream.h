#ifndef OUT_STREAM_H_INCLUDED
#define OUT_STREAM_H_INCLUDED



//  app

    #include "out-stream-buf.h"



class OutStream
    : public QObject
{
        Q_OBJECT

        OutStreamBuf * BufPtr;
        std::ostream * OstrPtr;


    public:

        OutStream ();
        ~ OutStream ();

        OutStream (const OutStream &) = delete;
        OutStream & operator = (const OutStream &) = delete;

        void initialize ();


        template <class T>
        OutStream & operator << (const T & t)
        {
            *OstrPtr << t;
            return *this;
        }


        OutStream & operator << (std::ostream & (*f) (std::ostream &))
        {
            f (*OstrPtr);
            return *this;
        }


    signals:

        void sigOut (QString qs);
};



#endif
