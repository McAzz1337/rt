#ifndef OUT_STREAM_BUF_H_INCLUDED
#define OUT_STREAM_BUF_H_INCLUDED



//  qt

    #include <QObject>


//  c++

    #include <streambuf>



class OutStreamBuf
    : public QObject
    , public std::streambuf
{
        Q_OBJECT


        std::string Buffer;


    protected:

        virtual int overflow (int c = EOF) override;


    signals:

        void sigOut (QString qs);
};



#endif
