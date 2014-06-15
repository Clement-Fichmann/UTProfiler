/**
  * \file openingwindow.h
  * \brief Code source de la classe OpeningWindow : fenêtre s'affichant à l'ouverture du programme, permettant de sélectionner les XML de données.
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */

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

void OpeningWindow::on_btnParcourirFormation_clicked(){
    QString cheminFormation = QFileDialog::getOpenFileName();
    ui->txtFormation->setText(cheminFormation);
}

void OpeningWindow::on_btnValider_clicked(){
    QString cheminUV = ui->txtUV->text();
    QString cheminFormation = ui->txtFormation->text();
    if (cheminUV.isEmpty()){ //si aucun fichier d'UV renseigné
        QMessageBox::warning(this, "Attention", "Veuillez choisir un fichier d'UV.");
    }
    else if (cheminFormation.isEmpty()){ //si aucun fichier d'UV renseigné
        QMessageBox::warning(this, "Attention", "Veuillez choisir un fichier de formations.");
    }
    else { //si les fichiers nécessaires sont présents, on charge le programme principal
        UVManager::getInstance().load(cheminUV);
        formationManager::getInstance().load(cheminFormation);
        MainWindow* m=new MainWindow(); //ouverture de la fenêtre principal
        m->show();
        this->hide();
    }
}

OpeningWindow::~OpeningWindow()
{
    delete ui;
}

