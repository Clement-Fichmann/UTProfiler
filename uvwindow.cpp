#include "uvwindow.h"
#include "ui_uvwindow.h"

UVWindow::UVWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UVWindow)
{
    ui->setupUi(this);
}

void UVWindow::on_btnFermer_clicked(){
    this->close();
}

UVWindow::~UVWindow()
{
    delete ui;
}
