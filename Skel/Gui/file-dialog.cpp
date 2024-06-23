//  self

    #include "file-dialog.h"


//  app

    #include "cfg.h"


//  c++

    using namespace std;



FileDialog :: FileDialog (QWidget * parent)
    : QFileDialog (parent, "Save Image", "", "*.tif")
    , BaseName ("ray-tracing")
{
    setAcceptMode (QFileDialog::AcceptSave);
    setFileMode (QFileDialog::AnyFile);

    connect (this, & QFileDialog::fileSelected,
        this, & FileDialog::SltSelected,
        Qt::QueuedConnection);

}



QString FileDialog :: NextFileName () const
{
    for (int i = 1; i <= 99; ++i)
    {
        QString format = BaseName + "-%1.tif";
        QString name = format.arg (i, 2, 10, QChar ('0'));
        QFileInfo info (directory(), name);
        if (! info.exists())
            return name;
    }

    return BaseName + ".tif";
}



void FileDialog :: setBaseName (const QString & basename)
{
    BaseName = basename;
}



void FileDialog :: SltSelected (const QString & selected)
{
    QFileInfo info (directory(), selected);
    emit sigSave (selected);
}



void FileDialog :: sltSave ()
{
    CfgVar <string> imgdirname ("image-directory", ".");
    QDir imgdir (QString::fromStdString (imgdirname));
    setDirectory (imgdir.exists() ? imgdir : QDir ("."));
    selectFile (NextFileName());

    exec();

    imgdir = directory();
    imgdirname = imgdir .canonicalPath() .toStdString();
}
