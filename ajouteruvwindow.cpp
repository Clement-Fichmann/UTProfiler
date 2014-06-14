#include "ajouteruvwindow.h"
#include "ui_ajouteruvwindow.h"
#include <QPointer>
#include <QComboBox>

ajouterUVWindow::ajouterUVWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterUVWindow)
{
    ui->setupUi(this);
    ui->tableCredits->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableCredits->verticalHeader()->hide();
    /*ui->tableCredits->insertRow(ui->tableCredits->rowCount());
    QPointer<QComboBox> test = new QComboBox(this);
    ui->tableCredits->setCellWidget(0, 0, test);*/
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
