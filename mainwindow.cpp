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
    ui->tableFormationCreditsNeeded->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableFormationCreditsNeeded->verticalHeader()->hide();
    ui->tableFormationCreditsNeededInUVSet_Credits->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableFormationCreditsNeededInUVSet_Credits->verticalHeader()->hide();
    ui->tableFormationCreditsNeededInUVSet_UV->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableFormationCreditsNeededInUVSet_UV->verticalHeader()->hide();
    ui->tableFormationFormationsNeeded->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableFormationFormationsNeeded->verticalHeader()->hide();
    ui->tableFormationUVNeeded->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableFormationUVNeeded->verticalHeader()->hide();
    foreach(QString code, uvM.getAllUV().keys()){
        ui->listUV->addItem(code);
    }
    foreach(QString code, fM.getAllFormations().keys()){
        ui->listFormation->addItem(code);
    }

    ui->txtCodeUV->setEnabled(true);
    ui->txtDescription->setEnabled(true);
    ui->chkAutomne->setEnabled(true);
    ui->chkPrintemps->setEnabled(true);
    ui->btnSauverUV->setEnabled(false);
    ui->txtCodeFormation->setEnabled(true);
    ui->txtDescriptionFormation->setEnabled(true);
    ui->btnSauverFormation->setEnabled(false);
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
    int sauvegarder = QMessageBox::question(this, "Sauvegarder fichier formations", "Voulez-vous sauvegarder le fichier des formations avant d'en charger un nouveau ?", QMessageBox::Yes | QMessageBox::No);
    if (sauvegarder == QMessageBox::Yes)
        fM.save(fM.file);
    QString newChemin = QFileDialog::getOpenFileName();
    if (!newChemin.isEmpty()){
        fM.load(newChemin);
        refreshFormationList();
        if (ui->listFormation->count() != 0){
            ui->btnSauverFormation->setEnabled(false);
            ui->listFormation->setCurrentIndex(1);
            ui->listFormation->setCurrentIndex(0); //sert à simuler un changement d'index
        } else {
            ui->txtCodeFormation->setEnabled(false);
            ui->txtDescriptionFormation->setEnabled(false);
            ui->txtCodeFormation->setText("");
            ui->txtDescriptionFormation->setText("");
            ui->btnSauverUV->setEnabled(false);
        }
    }
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

    //On vide le tableau de crédits de ses anciens éléments
    ui->tableCredits->clearContents();
    while (ui->tableCredits->rowCount() > 0){
        ui->tableCredits->removeRow(0);
    }
    //récupération des crédits de l'UV
    QMap<QString, QString> categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){ //pour toutes les catégories
        int creditsCat = uvSelectionnee.getNbCredits(cat); //on récupère les crédits de l'UV pour cette catégorie
        int ligne = ui->tableCredits->rowCount();
        ui->tableCredits->insertRow(ligne);
        QPointer<QLabel> ptCat = new QLabel(this); //on affiche la catégorie dans un QLabel
        QPointer<QSpinBox> ptCredits = new QSpinBox(this); //et les crédits dans une QSpinBox
        ptCat.data()->setText(cat);
        ptCredits.data()->setValue(creditsCat);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableCredits->setCellWidget(ligne, 0, ptCat); //puis on affiche ces widgets dans le tableau
        ui->tableCredits->setCellWidget(ligne, 1, ptCredits);
    }
    int rowCountDebut = ui->tableCredits->rowCount();
    for (int cpt = rowCountDebut; cpt < rowCountDebut +2 ; cpt++){
        //on ajoute 2 lignes pour l'ajout éventuel de catégories
        ui->tableCredits->insertRow(cpt);
        QPointer<QLineEdit> ptCat = new QLineEdit(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableCredits->setCellWidget(cpt, 0, ptCat);
        ui->tableCredits->setCellWidget(cpt, 1, ptCredits);
    }
    //on verrouille le bouton "Sauvegarder" jusqu'à la prochaine modification
    ui->btnSauverUV->setEnabled(false);
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
    //pour autoriser la sauvegarde, il faut qu'un code et un titre soient précisés
    if (ui->txtCodeUV->text().isEmpty() || ui->txtDescription->toPlainText().isEmpty()){
        ui->btnSauverUV->setEnabled(false);
    } else ui->btnSauverUV->setEnabled(true); //si c'est le cas, on débloque le bouton "Sauvegarder"
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

    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count(); i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableCredits->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableCredits->cellWidget(i,1)))->value();
        uvEditee.setCategorie(cat, creditsCat);
        //on met à jour les crédits de l'UV à l'aide des éléments du tableau
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count(); i < ui->tableCredits->rowCount(); i++){
        //on ajoute également les éventuels crédits de nouvelles catégories
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
    //une fois la fenêtre d'ajout refermée, si on reçoit un signal UVAdded, on actualise la liste des UV
    connect(a, SIGNAL(UVAdded()), this, SLOT(refreshUVList()));
    a->exec();
}

void MainWindow::on_btnDeleteUV_clicked(){
    int reponse = QMessageBox::warning(this, "Suppression de l'UV", "Voulez-vous vraiment supprimer l'UV " + ui->listUV->currentText() + " ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        uvM.deleteUV(ui->listUV->currentText());
        refreshUVList();
    }
}

void MainWindow::on_btnAjouterFormation_clicked(){
    ajouterformationwindow *a = new ajouterformationwindow();
    //une fois la fenêtre d'ajout refermée, si on reçoit un signal formationAdded, on actualise la liste des UV
    connect(a, SIGNAL(formationAdded()), this, SLOT(refreshFormationList()));
    a->exec();
}

void MainWindow::on_actionSaveUV_triggered(){ //menu Fichier -> Sauver le fichier d'UV
    uvM.save(uvM.file); //appel de la fonction save
}

void MainWindow::on_actionSaveFormations_triggered() {
    fM.save(fM.file);
}

void MainWindow::on_actionSaveTous_les_fichiers_triggered(){ //menu Fichier -> Sauver tous les fichiers
    uvM.save(uvM.file);
    fM.save(fM.file);
    // TODO save dossier étudiant
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::refreshUVList() {
    disconnect(ui->listUV, 0, 0, 0); //déconnexion des signaux nécessaire pour le clear()
    ui->listUV->clear();
    connect(ui->listUV, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listUV_currentIndexChanged())); //reconnexion du seul signal sur listUV
    foreach(QString code, uvM.getAllUV().keys()){
        ui->listUV->addItem(code); //ajout des UV à listUV
    }
}

void MainWindow::on_listFormation_currentIndexChanged(){
    //on récupère les infos sur la formation
    QString codeFormation = ui->listFormation->currentText();
    formation& formationSelectionnee = fM.getFormation(codeFormation);
    ui->txtCodeFormation->setText(formationSelectionnee.getCode());
    ui->txtDescriptionFormation->setText(formationSelectionnee.getTitre());
    ui->tableFormationCreditsNeeded->clearContents();
    while (ui->tableFormationCreditsNeeded->rowCount() > 0){
        ui->tableFormationCreditsNeeded->removeRow(0);
    }
    ui->tableFormationCreditsNeededInUVSet_Credits->clearContents();
    while (ui->tableFormationCreditsNeededInUVSet_Credits->rowCount() > 0){
        ui->tableFormationCreditsNeededInUVSet_Credits->removeRow(0);
    }
    ui->tableFormationCreditsNeededInUVSet_UV->clearContents();
    while (ui->tableFormationCreditsNeededInUVSet_UV->rowCount() > 0){
        ui->tableFormationCreditsNeededInUVSet_UV->removeRow(0);
    }
    ui->tableFormationFormationsNeeded->clearContents();
    while (ui->tableFormationFormationsNeeded->rowCount() > 0){
        ui->tableFormationFormationsNeeded->removeRow(0);
    }
    ui->tableFormationUVNeeded->clearContents();
    while (ui->tableFormationUVNeeded->rowCount() > 0){
        ui->tableFormationUVNeeded->removeRow(0);
    }

    //récupération des crédits needed
    QMap<QString, QString> categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){
        int creditsCat = formationSelectionnee.getCreditsNeeded().value(cat);
        int ligne = ui->tableFormationCreditsNeeded->rowCount();
        ui->tableFormationCreditsNeeded->insertRow(ligne);
        QPointer<QLabel> ptCat = new QLabel(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setText(cat);
        ptCredits.data()->setValue(creditsCat);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationCreditsNeeded->setCellWidget(ligne, 0, ptCat);
        ui->tableFormationCreditsNeeded->setCellWidget(ligne, 1, ptCredits);
    }
    int rowCountDebut = ui->tableFormationCreditsNeeded->rowCount();
    for (int cpt = rowCountDebut; cpt < rowCountDebut +2 ; cpt++){
        ui->tableFormationCreditsNeeded->insertRow(cpt);
        QPointer<QLineEdit> ptCat = new QLineEdit(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationCreditsNeeded->setCellWidget(cpt, 0, ptCat);
        ui->tableFormationCreditsNeeded->setCellWidget(cpt, 1, ptCredits);
    }

    //récupération des formationsNeeded
    QMap<QString, formation*> formations = fM.getAllFormations();
    foreach(QString formation, formations.keys()){
        if (formation == codeFormation)
            continue;
        bool formationNeeded = formationSelectionnee.getFormationsNeeded().contains(formation);
        int ligne = ui->tableFormationFormationsNeeded->rowCount();
        ui->tableFormationFormationsNeeded->insertRow(ligne);
        QPointer<QLabel> ptFor = new QLabel(this);
        QPointer<QCheckBox> ptCh = new QCheckBox(this);
        ptFor.data()->setText(formation);
        ptCh->setChecked(formationNeeded);
        ptFor.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationFormationsNeeded->setCellWidget(ligne, 0, ptFor);
        ui->tableFormationFormationsNeeded->setCellWidget(ligne, 1, ptCh);
    }

    //récupération des UVNeeded
    QMap<QString, UV*> uvs = uvM.getAllUV();
    foreach(QString uv, uvs.keys()){
        bool uvNeeded = formationSelectionnee.getUVNeeded().contains(uv);
        int ligne = ui->tableFormationUVNeeded->rowCount();
        ui->tableFormationUVNeeded->insertRow(ligne);
        QPointer<QLabel> ptUV = new QLabel(this);
        QPointer<QCheckBox> ptCh = new QCheckBox(this);
        ptUV.data()->setText(uv);
        ptCh->setChecked(uvNeeded);
        ptUV.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationUVNeeded->setCellWidget(ligne, 0, ptUV);
        ui->tableFormationUVNeeded->setCellWidget(ligne, 1, ptCh);
    }

    //récupération des créditsNeededInUVSet_credits
    categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){
        int creditsCat = formationSelectionnee.getCreditsNeededInUVSet().credits.value(cat);
        int ligne = ui->tableFormationCreditsNeededInUVSet_Credits->rowCount();
        ui->tableFormationCreditsNeededInUVSet_Credits->insertRow(ligne);
        QPointer<QLabel> ptCat = new QLabel(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setText(cat);
        ptCredits.data()->setValue(creditsCat);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationCreditsNeededInUVSet_Credits->setCellWidget(ligne, 0, ptCat);
        ui->tableFormationCreditsNeededInUVSet_Credits->setCellWidget(ligne, 1, ptCredits);
    }
    rowCountDebut = ui->tableFormationCreditsNeededInUVSet_Credits->rowCount();
    for (int cpt = rowCountDebut; cpt < rowCountDebut +2 ; cpt++){
        ui->tableFormationCreditsNeededInUVSet_Credits->insertRow(cpt);
        QPointer<QLineEdit> ptCat = new QLineEdit(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ptCredits.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationCreditsNeededInUVSet_Credits->setCellWidget(cpt, 0, ptCat);
        ui->tableFormationCreditsNeededInUVSet_Credits->setCellWidget(cpt, 1, ptCredits);
    }

    //récupération des créditsNeededInUVSet_uv
    uvs = uvM.getAllUV();
    foreach(QString uv, uvs.keys()){
        bool uvNeeded = formationSelectionnee.getUVNeeded().contains(uv);
        int ligne = ui->tableFormationCreditsNeededInUVSet_UV->rowCount();
        ui->tableFormationCreditsNeededInUVSet_UV->insertRow(ligne);
        QPointer<QLabel> ptUV = new QLabel(this);
        QPointer<QCheckBox> ptCh = new QCheckBox(this);
        ptUV.data()->setText(uv);
        ptCh->setChecked(uvNeeded);
        ptUV.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationCreditsNeededInUVSet_UV->setCellWidget(ligne, 0, ptUV);
        ui->tableFormationCreditsNeededInUVSet_UV->setCellWidget(ligne, 1, ptCh);
    }

    ui->btnSauverFormation->setEnabled(false);
}

void MainWindow::on_btnDeleteFormation_clicked(){
    int reponse = QMessageBox::warning(this, "Suppression de la formation", "Voulez-vous vraiment supprimer la formation " + ui->listFormation->currentText() + " ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        fM.deleteFormation(ui->listFormation->currentText());
        refreshFormationList();
    }
}

void MainWindow::refreshFormationList() {
    disconnect(ui->listFormation, 0, 0, 0); //déconnexion des signaux nécessaire pour le clear()
    ui->listFormation->clear();
    connect(ui->listFormation, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listFormation_currentIndexChanged()));
    foreach(QString formation, fM.getAllFormations().keys()){
        ui->listFormation->addItem(formation);
    }
}

void MainWindow::FormationEditee(){
    if (ui->txtCodeFormation->text().isEmpty() || ui->txtDescriptionFormation->toPlainText().isEmpty()){
        ui->btnSauverFormation->setEnabled(false);
    } else ui->btnSauverFormation->setEnabled(true);
}

void MainWindow::on_txtCodeFormation_textChanged() {
    FormationEditee();
}

void MainWindow::on_txtDescriptionFormation_textChanged() {
    FormationEditee();
}

void MainWindow::on_tableFormationCreditsNeeded_clicked() {
    FormationEditee();
}

void MainWindow::on_tableFormationCreditsNeededInUVSet_Credits_clicked() {
    FormationEditee();
}

void MainWindow::on_tableFormationCreditsNeededInUVSet_UV_clicked() {
    FormationEditee();
}

void MainWindow::on_tableFormationFormationsNeeded_clicked() {
    FormationEditee();
}

void MainWindow::on_tableFormationUVNeeded_clicked() {
    FormationEditee();
}

void MainWindow::on_btnSauverFormation_clicked(){
    int delta=0;
    //on récupère la clé (code formation) de la formation en cours d'édition
    QString codeFormationEditee = ui->listFormation->currentText();
    //puis la formation correspondant dans la map
    formation& formationEditee = fM.getFormation(codeFormationEditee);
    formationEditee.setCode(ui->txtCodeFormation->text());
    formationEditee.setTitre(ui->txtDescriptionFormation->toPlainText());

    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count() - delta; i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableFormationCreditsNeeded->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeeded->cellWidget(i,1)))->value();
        formationEditee.setCreditsNeeded(cat, creditsCat);
        //on met à jour les crédits de la formation à l'aide des éléments du tableau
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count() - delta; i < ui->tableFormationCreditsNeeded->rowCount(); i++){
        //on ajoute également les éventuels crédits de nouvelles catégories
        QString cat = (dynamic_cast<QLineEdit*>(ui->tableFormationCreditsNeeded->cellWidget(i,0)))->text();
        if (!cat.isEmpty()){
            int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeeded->cellWidget(i,1)))->value();
            formationEditee.setCreditsNeeded(cat, creditsCat);
            if (!uvM.getCategorieManager().getAllCategories().contains(cat)) {
                delta++;
                uvM.getCategorieManager().addItem(cat, "");
            }
        }
    }

    for (int i = 0; i < fM.getAllFormations().count() - 1; i++){
        QString formation = (dynamic_cast<QLabel*>(ui->tableFormationFormationsNeeded->cellWidget(i,0)))->text();
        bool needed = (dynamic_cast<QCheckBox*>(ui->tableFormationFormationsNeeded->cellWidget(i,1)))->isChecked();
        if (needed)
            formationEditee.setFormationNeeded(formation);
        else
            formationEditee.removeFormationNeeded(formation);
    }

    for (int i = 0; i < uvM.getAllUV().count(); i++){
        QString uv = (dynamic_cast<QLabel*>(ui->tableFormationUVNeeded->cellWidget(i,0)))->text();
        bool needed = (dynamic_cast<QCheckBox*>(ui->tableFormationUVNeeded->cellWidget(i,1)))->isChecked();
        if (needed)
            formationEditee.setUVNeeded(uv);
        else
            formationEditee.removeUVNeeded(uv);
    }

    CreditsInUV cInUV;
    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count() - delta; i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,1)))->value();
        cInUV.credits.insert(cat, creditsCat);
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count() - delta; i < ui->tableFormationCreditsNeededInUVSet_Credits->rowCount(); i++){
        //on ajoute également les éventuels crédits de nouvelles catégories
        QString cat = (dynamic_cast<QLineEdit*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,0)))->text();
        if (!cat.isEmpty()){
            int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,1)))->value();
            cInUV.credits.insert(cat, creditsCat);
            if (!uvM.getCategorieManager().getAllCategories().contains(cat)) {
                delta++;
                uvM.getCategorieManager().addItem(cat, "");
            }
        }
    }
    for (int i = 0; i < uvM.getAllUV().count(); i++){
        QString uv = (dynamic_cast<QLabel*>(ui->tableFormationCreditsNeededInUVSet_UV->cellWidget(i,0)))->text();
        bool needed = (dynamic_cast<QCheckBox*>(ui->tableFormationCreditsNeededInUVSet_UV->cellWidget(i,1)))->isChecked();
        if (needed)
            cInUV.uvs.insert(uv);
    }
    formationEditee.setCreditsNeededInUVSet(cInUV);



    //les changements ont été enregistrés, on verrouille le bouton "Sauver" jusqu'à la prochaine édition
    ui->btnSauverFormation->setEnabled(false);

}
