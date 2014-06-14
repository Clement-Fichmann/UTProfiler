#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "uvmanager.h"
#include "ajouteruvwindow.h"

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
    void on_actionCharger_un_nouveau_fichier_formations_triggered();
    void on_actionDossier_Etudiant_triggered();
    void on_actionQuitter_triggered();
    void on_listUV_currentIndexChanged();
    void on_txtCodeUV_textChanged();
    void on_txtDescription_textChanged();
    void on_chkAutomne_stateChanged();
    void on_chkPrintemps_stateChanged();
    void UVEditee();
    void on_btnSauverUV_clicked();
    void on_btnAjouterUV_clicked();
    void on_actionSaveUV_triggered();
    void on_actionSaveTous_les_fichiers_triggered();
private:
    UVManager& uvM;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
