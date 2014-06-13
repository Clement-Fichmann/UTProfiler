#include "uvmanager.h"
#include "utprofilerexception.h"
#include "openingwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>

int main(int argc, char *argv[]) {
     QApplication app(argc, argv);
     try {
        UVManager& uvM = UVManager::getInstance();
    }catch(UTProfilerException e){
        QMessageBox msgBox;
        msgBox.setText(e.getInfo());
        msgBox.exec();
    }
    OpeningWindow intro;
    intro.show();

    return app.exec();
}
