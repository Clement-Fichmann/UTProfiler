#include "uvmanager.h"
#include "utprofilerexception.h"
#include "openingwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    try {
        UVManager& uvM=UVManager::getInstance();
    }catch(UTProfilerException e){
        QMessageBox msgBox;
        msgBox.setText(e.getInfo());
        msgBox.exec();
    }
    QApplication app(argc, argv);
    OpeningWindow intro;
    intro.show();
    return app.exec();
}
