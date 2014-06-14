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

ajouterUVWindow::~ajouterUVWindow()
{
    delete ui;
}
