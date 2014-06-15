/**
  * \file ajouteruvwindow.cpp
  * \brief Code source de la classe ajouterUVWindow : fenêtre d'ajout d'UV
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */

#include "ajouteruvwindow.h"
#include "mainwindow.h"
#include "ui_ajouteruvwindow.h"
#include <QPointer>
#include <QComboBox>



ajouterUVWindow::ajouterUVWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ajouterUVWindow), uvM(UVManager::getInstance()) {
    ui->setupUi(this);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableCredits->verticalHeader()->hide();

    QMap<QString, QString> categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){ //pour toutes les catégories
        int ligne = ui->tableCredits->rowCount();
        ui->tableCredits->insertRow(ligne); //on insère une nouvelle ligne dans le tableau d'affichage
        QPointer<QLabel> ptCat = new QLabel(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setText(cat); //on place le code de la catégorie dans un label
        ptCredits.data()->setValue(0);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableCredits->setCellWidget(ligne, 0, ptCat);
        ui->tableCredits->setCellWidget(ligne, 1, ptCredits);
    }
    int rowCountDebut = ui->tableCredits->rowCount();
    for (int cpt = rowCountDebut; cpt < rowCountDebut +2 ; cpt++){ //on va ajouter 2 nouvelles lignes
        ui->tableCredits->insertRow(cpt);
        QPointer<QLineEdit> ptCat = new QLineEdit(this); //La QLineEdit permet d'ajouter une catégorie de crédits
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableCredits->setCellWidget(cpt, 0, ptCat);
        ui->tableCredits->setCellWidget(cpt, 1, ptCredits);
    }
    ui->btnAccepter->setEnabled(false);
}

void ajouterUVWindow::on_txtCodeNewUV_textChanged(){
    this->UVEditee(); //appel d'un slot commun permettant d'activer le bouton de sauvegarde
}

void ajouterUVWindow::on_txtDescNewUV_textChanged(){
    this->UVEditee();
}

void ajouterUVWindow::UVEditee(){
    if (ui->txtCodeNewUV->text().isEmpty() || ui->txtDescNewUV->toPlainText().isEmpty()){
        ui->btnAccepter->setEnabled(false);
    } else ui->btnAccepter->setEnabled(true);
}

void ajouterUVWindow::on_btnAnnuler_clicked(){
    this->close();
}

void ajouterUVWindow::on_btnAccepter_clicked(){
    QMap<QString, int> credits;
    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count(); i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableCredits->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableCredits->cellWidget(i,1)))->value();
        credits.insert(cat, creditsCat);
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count(); i < ui->tableCredits->rowCount(); i++){
        QString cat = (dynamic_cast<QLineEdit*>(ui->tableCredits->cellWidget(i,0)))->text();
        if (!cat.isEmpty()){
            int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableCredits->cellWidget(i,1)))->value();
            credits.insert(cat, creditsCat);
            if (!uvM.getCategorieManager().getAllCategories().contains(cat)) {
                uvM.getCategorieManager().addItem(cat, "");
            }
        }
    }
    if (uvM.getAllUV().contains(ui->txtCodeNewUV->text())){//si une UV correspondant à ce code existe déjà
        int confirm = QMessageBox::question(this, "Ajout d'une UV", "Cette UV existe déjà. L'écraser ?", QMessageBox::Yes | QMessageBox::No);
        if (confirm == QMessageBox::Yes){
            uvM.addUV(ui->txtCodeNewUV->text(), ui->txtDescNewUV->toPlainText(), credits, ui->chkAutomne->isChecked(), ui->chkPrintemps->isChecked());
            this->close();
            emit UVAdded();
        }
    } else {  uvM.addUV(ui->txtCodeNewUV->text(), ui->txtDescNewUV->toPlainText(), credits, ui->chkAutomne->isChecked(), ui->chkPrintemps->isChecked());
        this->close();
        emit UVAdded();
    }
}

ajouterUVWindow::~ajouterUVWindow()
{
    delete ui;
}
