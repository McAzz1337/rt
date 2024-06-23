//  app

    #include "main-window.h"
    #include "scan-line-ptr.h"


//  qt

    #include <QApplication>
    #include <QFileInfo>
    #include <QStyleFactory>


//  c++

    #include <iostream>

    using namespace std;



int main (int argc, char * argv [])
{
    QFileInfo qfi (argv [0]);
    QString qprgname = qfi.baseName();
    string prgname = qprgname.toStdString();
    cout << "program " << prgname << " started ..." << endl;

    Cfg::setFilename (prgname + ".cfg");

    qRegisterMetaType <ScanLinePtr> ("ScanLinePtr");
    qRegisterMetaType <std::string> ("std::string");

    QApplication::setStyle (QStyleFactory::create ("Fusion"));
    QApplication app (argc, argv);
    MainWindow * winptr = new MainWindow (qprgname);
    QApplication::setFont (winptr->font());
    winptr->show();
    int res = app.exec();
    delete winptr;

    cout << "program " << prgname << " finished." << endl;
    cout << "return code: " << res << endl;
    return res;
}
