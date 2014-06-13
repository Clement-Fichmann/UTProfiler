#include "openingwindow.h"
#include "ui_openingwindow.h"

OpeningWindow::OpeningWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpeningWindow)
{
    ui->setupUi(this);
}

void OpeningWindow::on_btnParcourirUV_clicked(){
    QString cheminUV = QFileDialog::getOpenFileName();
    ui->txtUV->setText(cheminUV);
}

void OpeningWindow::on_btnValider_clicked(){
    QString cheminUV = ui->txtUV->text();
    if (cheminUV.isEmpty()){ //si aucun fichier d'UV renseigné
        QMessageBox::warning(this, "Attention", "Veuillez choisir un fichier d'UV.");
    }
    else { //si les fichiers nécessaires sont présents, on charge le programme principal
        UVManager& uvM=UVManager::getInstance();
        uvM.load(cheminUV);
        MainWindow* m=new MainWindow();
        m->show();
        this->hide();
    }
}

OpeningWindow::~OpeningWindow()
{
    delete ui;
}

