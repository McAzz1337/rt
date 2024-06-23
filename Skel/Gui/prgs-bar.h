#ifndef PRGS_BAR_H_INCLUDED
#define PRGS_BAR_H_INCLUDED



//  qt designer

    namespace Ui { class Progress; }


//  qt

    class QElapsedTimer;

    #include <QProgressBar>



class PrgsBar
    : public QProgressBar
{
        Q_OBJECT


        QTimer * TimPtr;
        QElapsedTimer * ElaPtr;
        QString Todo, Done;

        static const int SystemSteps = 1000;

        int NextSystemStep;
        int UserSteps;
        int CurrentUserStep;


        QString TimeStr (int ms) const;
        void Adjust ();

    public:

        explicit PrgsBar (QWidget * parent = nullptr);
        ~ PrgsBar ();


    private slots:

        void SltTick ();


    public slots:

        void sltStart (int usersteps);
        void sltStep ();
};



#endif
