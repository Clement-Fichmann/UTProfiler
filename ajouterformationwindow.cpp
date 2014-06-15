#include "ajouterformationwindow.h"
#include "ui_ajouterformationwindow.h"
#include <QPointer>
#include <QSpinBox>
#include <QCheckBox>
#include <QMessageBox>

ajouterformationwindow::ajouterformationwindow(QWidget *parent) : QDialog(parent), ui(new Ui::ajouterformationwindow), uvM(UVManager::getInstance()), fM(formationManager::getInstance()) {
    ui->setupUi(this);
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

    QMap<QString, QString> categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){
        int ligne = ui->tableFormationCreditsNeeded->rowCount();
        ui->tableFormationCreditsNeeded->insertRow(ligne);
        QPointer<QLabel> ptCat = new QLabel(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setText(cat);
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

    QMap<QString, formation*> formations = fM.getAllFormations();
    foreach(QString formation, formations.keys()){
        int ligne = ui->tableFormationFormationsNeeded->rowCount();
        ui->tableFormationFormationsNeeded->insertRow(ligne);
        QPointer<QLabel> ptFor = new QLabel(this);
        QPointer<QCheckBox> ptCh = new QCheckBox(this);
        ptFor.data()->setText(formation);
        ptFor.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationFormationsNeeded->setCellWidget(ligne, 0, ptFor);
        ui->tableFormationFormationsNeeded->setCellWidget(ligne, 1, ptCh);
    }

    QMap<QString, UV*> uvs = uvM.getAllUV();
    foreach(QString uv, uvs.keys()){
        int ligne = ui->tableFormationUVNeeded->rowCount();
        ui->tableFormationUVNeeded->insertRow(ligne);
        QPointer<QLabel> ptUV = new QLabel(this);
        QPointer<QCheckBox> ptCh = new QCheckBox(this);
        ptUV.data()->setText(uv);
        ptUV.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationUVNeeded->setCellWidget(ligne, 0, ptUV);
        ui->tableFormationUVNeeded->setCellWidget(ligne, 1, ptCh);
    }

    categories = uvM.getCategorieManager().getAllCategories();
    foreach(QString cat, categories.keys()){
        int ligne = ui->tableFormationCreditsNeededInUVSet_Credits->rowCount();
        ui->tableFormationCreditsNeededInUVSet_Credits->insertRow(ligne);
        QPointer<QLabel> ptCat = new QLabel(this);
        QPointer<QSpinBox> ptCredits = new QSpinBox(this);
        ptCat.data()->setText(cat);
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

    uvs = uvM.getAllUV();
    foreach(QString uv, uvs.keys()){
        int ligne = ui->tableFormationCreditsNeededInUVSet_UV->rowCount();
        ui->tableFormationCreditsNeededInUVSet_UV->insertRow(ligne);
        QPointer<QLabel> ptUV = new QLabel(this);
        QPointer<QCheckBox> ptCh = new QCheckBox(this);
        ptUV.data()->setText(uv);
        ptUV.data()->setStyleSheet("qproperty-alignment: AlignCenter;");
        ui->tableFormationCreditsNeededInUVSet_UV->setCellWidget(ligne, 0, ptUV);
        ui->tableFormationCreditsNeededInUVSet_UV->setCellWidget(ligne, 1, ptCh);
    }
    ui->btnAccepter->setEnabled(false);
}

void ajouterformationwindow::on_txtCodeFormation_textChanged() {
    formationEditee(); //appel d'un slot commun permettant d'activer le bouton de sauvegarde
}


void ajouterformationwindow::on_txtDescriptionFormation_textChanged() {
    formationEditee();
}

void ajouterformationwindow::formationEditee() {
    if (ui->txtCodeFormation->text().isEmpty() || ui->txtDescriptionFormation->toPlainText().isEmpty()){ //le code et le titre de la formation doivent être renseignés
        ui->btnAccepter->setEnabled(false);
    } else ui->btnAccepter->setEnabled(true); //si c'est le cas, le bouton de validation est débloqué
}

void ajouterformationwindow::on_btnAnnuler_clicked() {
    this->close();
}

void ajouterformationwindow::on_btnAccepter_clicked() {
    int delta=0;
    QMap<QString, int> creditsNeeded;
    QSet<QString> formationsNeeded;
    QSet<QString> uvNeeded;
    CreditsInUV creditsNeededInUVSet;

    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count() - delta; i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableFormationCreditsNeeded->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeeded->cellWidget(i,1)))->value();
        creditsNeeded.insert(cat, creditsCat);
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count() - delta; i < ui->tableFormationCreditsNeeded->rowCount(); i++){
        QString cat = (dynamic_cast<QLineEdit*>(ui->tableFormationCreditsNeeded->cellWidget(i,0)))->text();
        if (!cat.isEmpty()){
            int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeeded->cellWidget(i,1)))->value();
            creditsNeeded.insert(cat, creditsCat);
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
            formationsNeeded.insert(formation);
    }

    for (int i = 0; i < uvM.getAllUV().count(); i++){
        QString uv = (dynamic_cast<QLabel*>(ui->tableFormationUVNeeded->cellWidget(i,0)))->text();
        bool needed = (dynamic_cast<QCheckBox*>(ui->tableFormationUVNeeded->cellWidget(i,1)))->isChecked();
        if (needed)
            uvNeeded.insert(uv);
    }

    for (int i = 0; i < uvM.getCategorieManager().getAllCategories().count() - delta; i++){
        QString cat = (dynamic_cast<QLabel*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,0)))->text();
        int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,1)))->value();
        creditsNeededInUVSet.credits.insert(cat, creditsCat);
    }
    for (int i = uvM.getCategorieManager().getAllCategories().count() - delta; i < ui->tableFormationCreditsNeededInUVSet_Credits->rowCount(); i++){
        //on ajoute également les éventuels crédits de nouvelles catégories
        QString cat = (dynamic_cast<QLineEdit*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,0)))->text();
        if (!cat.isEmpty()){
            int creditsCat = (dynamic_cast<QSpinBox*>(ui->tableFormationCreditsNeededInUVSet_Credits->cellWidget(i,1)))->value();
            creditsNeededInUVSet.credits.insert(cat, creditsCat);
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
            creditsNeededInUVSet.uvs.insert(uv);
    }

    if (fM.getAllFormations().contains(ui->txtCodeFormation->text())){//si une formation correspondant à ce code existe déjà, on demande confirmation pour l'écraser
        int confirm = QMessageBox::question(this, "Ajout d'une formation", "Cette formation existe déjà. L'écraser ?", QMessageBox::Yes | QMessageBox::No);
        if (confirm == QMessageBox::Yes){
            fM.addFormation(ui->txtCodeFormation->text(), ui->txtDescriptionFormation->toPlainText(), creditsNeeded, formationsNeeded, uvNeeded, creditsNeededInUVSet);
            this->close();
            emit formationAdded(); //émission du signal formationAdded, pour la fenêtre MainWindow
        }
    } else {  fM.addFormation(ui->txtCodeFormation->text(), ui->txtDescriptionFormation->toPlainText(), creditsNeeded, formationsNeeded, uvNeeded, creditsNeededInUVSet);
        this->close();
        emit formationAdded();
    }
}


ajouterformationwindow::~ajouterformationwindow()
{
    delete ui;
}
