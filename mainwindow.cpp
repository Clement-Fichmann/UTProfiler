#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listUV->addItem("LO21");
    ui->listUV->addItem("NF17");
    ui->listUV->addItem("NF28");
    ui->listUV->setCurrentIndex(-1);
    ui->txtCodeUV->setEnabled(false);
    ui->txtDescription->setEnabled(false);
    ui->chkAutomne->setEnabled(false);
    ui->chkPrintemps->setEnabled(false);
    ui->btnSauver->setEnabled(false);
}

void MainWindow::on_actionChoisir_le_fichier_des_UV_triggered(){
    QFileDialog::getOpenFileName();
}

void MainWindow::on_actionQuitter_triggered(){
    this->close();
}

void MainWindow::on_listUV_currentIndexChanged(){
    //on récupère les infos sur l'UV
    //TODO

    //on débloque les champs pour la modification
    ui->txtCodeUV->setEnabled(true);
    ui->txtDescription->setEnabled(true);
    ui->chkAutomne->setEnabled(true);
    ui->chkPrintemps->setEnabled(true);
}

void MainWindow::on_txtCodeUV_textChanged(){
    this->UVEditee(); //appel d'un slot commun permettant d'activer le bouton de sauvegarde
}

void MainWindow::on_txtDescription_textChanged(){
    this->UVEditee();
}

void MainWindow::on_chkAutomne_stateChanged(){
    this->UVEditee();
}

void MainWindow::on_chkPrintemps_stateChanged(){
    this->UVEditee();
}

void MainWindow::UVEditee(){
    ui->btnSauver->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
