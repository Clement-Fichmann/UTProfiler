#ifndef OPENINGWINDOW_H
#define OPENINGWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
class OpeningWindow;
}

class OpeningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpeningWindow(QWidget *parent = 0);
    ~OpeningWindow();

public slots:
    void on_btnParcourirUV_clicked();
    void on_btnValider_clicked();

private:
    Ui::OpeningWindow *ui;
};

#endif // OPENINGWINDOW_H
