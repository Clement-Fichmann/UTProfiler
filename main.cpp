#include "uvmanager.h"
#include "formationmanager.h"
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
        formationManager& fM = formationManager::getInstance();
        /*QString chemin = QFileDialog::getOpenFileName();
        fM.load(chemin);
        QString bla;*/
    }catch(UTProfilerException e){
        QMessageBox msgBox;
        msgBox.setText(e.getInfo());
        msgBox.exec();
    }
    OpeningWindow intro;
    intro.show();

    return app.exec();
}
