#ifndef OUT_WIDGET_H_INCLUDED
#define OUT_WIDGET_H_INCLUDED



//  qt

    #include <QTextEdit>



class OutWidget
    : public QTextEdit
{
        Q_OBJECT


        bool Out; QColor ColCout;
        bool Err; QColor ColCerr;
        bool Log; QColor ColClog;


    public:

        OutWidget (QWidget * parent = nullptr);


    public slots:

        void sltCout (QString qs);
        void sltCerr (QString qs);
        void sltClog (QString qs);
};



#endif
