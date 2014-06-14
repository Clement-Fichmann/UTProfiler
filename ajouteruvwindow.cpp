#include "ajouteruvwindow.h"
#include "ui_ajouteruvwindow.h"

ajouterUVWindow::ajouterUVWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterUVWindow)
{
    ui->setupUi(this);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void ajouterUVWindow::on_btnAnnuler_clicked(){
    this->close();
}

void ajouterUVWindow::on_btnAccepter_clicked(){
    UVManager& uvm = UVManager::getInstance();
    QMap<QString, int> credits; //TODO
    uvm.addUV(ui->txtCodeNewUV->text(), ui->txtDescNewUV->toPlainText(), credits, ui->chkAutomne->isChecked(), ui->chkPrintemps->isChecked());
    this->close();
}

ajouterUVWindow::~ajouterUVWindow()
{
    delete ui;
}
