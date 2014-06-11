#include "mainwindow.h"
#include "uvmanager.h"
#include "utprofilerexception.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;
    fenetre.setFixedSize(200, 400);
    QLineEdit code(&fenetre);
    QTextEdit titre(&fenetre);
    QPushButton save("Sauver", &fenetre);
    code.setFixedWidth(180);
    titre.setFixedSize(180, 110);
    save.setFixedWidth(80);
    QVBoxLayout couche;
    couche.addWidget(&code);
    couche.addWidget(&titre);
    couche.addWidget(&save);
    fenetre.setLayout(&couche);

    try {
        CategorieManager& c=CategorieManager::getInstance();
        NoteManager& n=NoteManager::getInstance();
        UVManager& m=UVManager::getInstance();
        QString chemin = QFileDialog::getOpenFileName();
        m.load(chemin);
        UV& uv=m.getUV("LO21");
        code.setText(uv.getCode());
        titre.setText(uv.getTitre());
    }catch(UTProfilerException e){
        QMessageBox msgBox;
        msgBox.setText(e.getInfo());
        msgBox.exec();
    }
    fenetre.show();
    return app.exec();
}
