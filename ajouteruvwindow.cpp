#include "ajouteruvwindow.h"
#include "ui_ajouteruvwindow.h"

ajouterUVWindow::ajouterUVWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterUVWindow)
{
    ui->setupUi(this);
}

void ajouterUVWindow::on_btnAnnuler_clicked(){
    this->close();
}

ajouterUVWindow::~ajouterUVWindow()
{
    delete ui;
}
