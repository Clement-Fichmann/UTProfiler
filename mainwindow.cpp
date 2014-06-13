#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_btnUV_clicked(){
    UVWindow *uvw = new UVWindow();
    uvw->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
