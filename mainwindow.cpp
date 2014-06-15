/**
  * \file mainwindow.cpp
  * \brief Code source de la classe MainWindow : fenêtre principale d'UTProfiler
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), uvM(UVManager::getInstance()), fM(formationManager::getInstance()) {
    ui->setupUi(this);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableCredits->verticalHeader()->hide();
    foreach(QString code, uvM.getAllUV().keys()){
        ui->listUV->addItem(code);
    }
    /*
    ui->txtCodeUV->setEnabled(false);
    ui->txtDescription->setEnabled(false);
    ui->chkAutomne->setEnabled(false);
    ui->chkPrintemps->setEnabled(false);
    */
    ui->txtCodeUV->setEnabled(true);
    ui->txtDescription->setEnabled(true);
    ui->chkAutomne->setEnabled(true);
    ui->chkPrintemps->setEnabled(true);
    ui->btnSauverUV->setEnabled(false);
}

void MainWindow::closeEvent(QCloseEvent* event){
    int quitter = QMessageBox::question(this, "Fermer UTProfiler", "Voulez-vous quitter UTProfiler ? Vous lui manquerez.", QMessageBox::Yes | QMessageBox::No);
    if (quitter == QMessageBox::Yes) {
        int sauvegarder = QMessageBox::question(this, "Sauvegarder tous les fichiers", "Voulez-vous sauvegarder tous les fichiers avant de quitter ?", QMessageBox::Yes | QMessageBox::No);
        if (sauvegarder == QMessageBox::Yes)
            on_actionSaveTous_les_fichiers_triggered();
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::on_actionChoisir_le_fichier_des_UV_triggered(){
    int sauvegarder = QMessageBox::question(this, "Sauvegarder fichier UV", "Voulez-vous sauvegarder le fichier des UV avant d'en charger un nouveau ?", QMessageBox::Yes | QMessageBox::No);
    if (sauvegarder == QMessageBox::Yes)
        uvM.save(uvM.file);
    QString newChemin = QFileDialog::getOpenFileName();
    if (!newChemin.isEmpty()){
        uvM.load(newChemin);
        refreshUVList();
        if (ui->listUV->count() != 0){
            ui->btnSauverUV->setEnabled(false);
            ui->listUV->setCurrentIndex(1);
            ui->listUV->setCurrentIndex(0); //sert à simuler un changement d'index
        } else {
            ui->txtCodeUV->setEnabled(false);
            ui->txtDescription->setEnabled(false);
            ui->chkAutomne->setEnabled(false);
            ui->chkPrintemps->setEnabled(false);
            ui->txtCodeUV->setText("");
            ui->txtDescription->setText("");
            ui->chkAutomne->setChecked(false);
            ui->chkPrintemps->setChecked(false);
            ui->btnSauverUV->setEnabled(false);
        }
    }
}

void MainWindow::on_actionCharger_un_nouveau_fichier_formations_triggered(){
    QFileDialog::getOpenFileName();
}

void MainWindow::on_actionDossier_Etudiant_triggered(){
    QFileDialog::getOpenFileName();
}

void MainWindow::on_actionQuitter_triggered(){
    this->close();
}

void MainWindow::on_listUV_currentIndexChanged(){
    //on récupère les infos sur l'UV
    QString codeUV = ui->listUV->currentText();
    UV& uvSelectionnee = uvM.getUV(codeUV);
    ui->txtCodeUV->setText(uvSelectionnee.getCode());
    ui->txtDescription->setText(uvSelectionnee.getTitre());
    ui->chkAutomne->setChecked(uvSelectionnee.ouvertureAutomne());
    ui->chkPrintemps->setChecked(uvSelectionnee.ouverturePrintemps());
    ui->tableCredits->clearContents();
    while (ui->tableCredits->rowCount() > 0){
        ui->tableCredits->removeRow(0);
    }
    //récupération des crédits de l'UV

    //TODO chargement crédits
    QMap<QString, QString> categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){
        int creditsCat = uvSelectionnee.getNbCredits(cat);
        int ligne = ui->tableCredits->rowCount();
        ui->tableCredits->insertRow(ligne);
        QPointer<QLabel> ptCat = new QLabel(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setText(cat);
        ptCredits.data()->setValue(creditsCat);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableCredits->setCellWidget(ligne, 0, ptCat);
        ui->tableCredits->setCellWidget(ligne, 1, ptCredits);
    }
    int rowCountDebut = ui->tableCredits->rowCount();
    for (int cpt = rowCountDebut; cpt < rowCountDebut +2 ; cpt++){
        ui->tableCredits->insertRow(cpt);
        QPointer<QLineEdit> ptCat = new QLineEdit(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableCredits->setCellWidget(cpt, 0, ptCat);
        ui->tableCredits->setCellWidget(cpt, 1, ptCredits);
    }

    ui->btnSauverUV->setEnabled(false);
    //on débloque les champs pour la modification
    /*ui->txtCodeUV->setEnabled(true);
    ui->txtDescription->setEnabled(true);
    ui->chkAutomne->setEnabled(true);
    ui->chkPrintemps->setEnabled(true);*/
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

void MainWindow::on_tableCredits_clicked(){
    this->UVEditee();
}

void MainWindow::UVEditee(){
    if (ui->txtCodeUV->text().isEmpty() || ui->txtDescription->toPlainText().isEmpty()){
        ui->btnSauverUV->setEnabled(false);
    } else ui->btnSauverUV->setEnabled(true);
}

void MainWindow::on_btnSauverUV_clicked(){
    //on récupère la clé (code UV) de l'UV en cours d'édition
    QString codeUVEditee = ui->listUV->currentText();
    //puis l'UV correspondant dans la map
    UV& uvEditee = uvM.getUV(codeUVEditee);
    uvEditee.setCode(ui->txtCodeUV->text());
    uvEditee.setTitre(ui->txtDescription->toPlainText());
    uvEditee.setOuvertureAutomne(ui->chkAutomne->isChecked());
    uvEditee.setOuverturePrintemps(ui->chkPrintemps->isChecked());

    //TODO gestion sauvegarde crédits
    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count(); i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableCredits->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableCredits->cellWidget(i,1)))->value();
        uvEditee.setCategorie(cat, creditsCat);
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count(); i < ui->tableCredits->rowCount(); i++){
        QString cat = (dynamic_cast<QLineEdit*>(ui->tableCredits->cellWidget(i,0)))->text();
        if (!cat.isEmpty()){
            int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableCredits->cellWidget(i,1)))->value();
            uvEditee.setCategorie(cat, creditsCat);
            if (!uvM.getCategorieManager().getAllCategories().contains(cat)) {
                uvM.getCategorieManager().addItem(cat, "");
            }
        }
    }
    //les changements ont été enregistrés, on verrouille le bouton "Sauver" jusqu'à la prochaine édition
    ui->btnSauverUV->setEnabled(false);
}

void MainWindow::on_btnAjouterUV_clicked(){
    ajouterUVWindow *a = new ajouterUVWindow();
    connect(a, SIGNAL(UVAdded()), this, SLOT(refreshUVList()));
    a->exec();
}

void MainWindow::on_btnDeleteUV_clicked(){
    int indexUV = ui->listUV->currentIndex();
    int reponse = QMessageBox::warning(this, "Suppression de l'UV", "Voulez-vous vraiment supprimer l'UV " + ui->listUV->currentText() + " ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        uvM.deleteUV(ui->listUV->currentText());
        ui->listUV->removeItem(indexUV);
        ui->listUV->setCurrentIndex(indexUV-1<0?0:indexUV-1);
    }
}

void MainWindow::on_actionSaveUV_triggered(){
    uvM.save(uvM.file);
}

void MainWindow::on_actionSaveTous_les_fichiers_triggered(){
    uvM.save(uvM.file);
    // TODO save formation et dossir étudiant
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshUVList() {
    disconnect(ui->listUV, 0, 0, 0); //déconnexion des signaux nécessaire pour le clear()
    ui->listUV->clear();
    connect(ui->listUV, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listUV_currentIndexChanged()));
    foreach(QString code, uvM.getAllUV().keys()){
        ui->listUV->addItem(code);
    }
}
