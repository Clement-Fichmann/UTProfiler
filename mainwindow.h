#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionChoisir_le_fichier_des_UV_triggered();
    void on_actionQuitter_triggered();
    void on_listUV_currentIndexChanged();
    void on_txtCodeUV_textChanged();
    void on_txtDescription_textChanged();
    void on_chkAutomne_stateChanged();
    void on_chkPrintemps_stateChanged();
    void UVEditee();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
