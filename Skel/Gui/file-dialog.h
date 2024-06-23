#ifndef FILE_DIALOG_H_INCLUDED
#define FILE_DIALOG_H_INCLUDED



//  qt

    #include <QFileDialog>



class FileDialog
    : public QFileDialog
{
        Q_OBJECT

        QString BaseName;

        QString NextFileName () const;


    public:

        FileDialog (QWidget * parent = nullptr);

        void setBaseName (const QString & basename);


    signals:

        void sigSave (const QString filename);


    private slots:

        void SltSelected (const QString & selected);


    public slots:

        void sltSave ();
};



#endif
