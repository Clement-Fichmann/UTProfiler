#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), uvM(UVManager::getInstance()) {
    ui->setupUi(this);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
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

void MainWindow::on_actionChoisir_le_fichier_des_UV_triggered(){
    QString newChemin = QFileDialog::getOpenFileName();
    if (!newChemin.isEmpty()){
        disconnect(ui->listUV, 0, 0, 0);
        ui->listUV->clear();
        connect(ui->listUV, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listUV_currentIndexChanged()));
        uvM.load(newChemin);
        foreach(QString code, uvM.getAllUV().keys()){
            ui->listUV->addItem(code);
        }
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
    int quitter = QMessageBox::question(this, "Fermer UTProfiler", "Voulez-vous quitter UTProfiler? Vous lui manquerez.", QMessageBox::Yes | QMessageBox::No);
    if (quitter == QMessageBox::Yes)
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

    //récupération des crédits de l'UV

    //TODO chargement crédits
    foreach(QString cat, uvSelectionnee.getCategories().keys()){

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

void MainWindow::UVEditee(){
    ui->btnSauverUV->setEnabled(true);
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

    //les changements ont été enregistrés, on verrouille le bouton "Sauver" jusqu'à la prochaine édition
    ui->btnSauverUV->setEnabled(false);
}

void MainWindow::on_btnAjouterUV_clicked(){
    ajouterUVWindow *a = new ajouterUVWindow();
    a->exec();
}

void MainWindow::on_btnSauverUV_clicked(){
    UV& uvADelete = uvM.getUV(ui->listUV->currentText());
    int indexUV = ui->listUV->currentIndex();
    int reponse = QMessageBox::warning(this, "Suppression de l'UV", "Voulez-vous vraiment supprimer l'UV" + ui->listUV->currentText() + " ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        //TODO deleteUV
        ui->listUV->removeItem(indexUV);
        ui->listUV->setCurrentIndex(index-1<0?0:index-1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
