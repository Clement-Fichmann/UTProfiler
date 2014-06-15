#ifndef OPENINGWINDOW_H
#define OPENINGWINDOW_H

/**
  * \file openingwindow.h
  * \brief Header de la classe OpeningWindow : fenêtre s'affichant à l'ouverture du programme, permettant de sélectionner les XML de données.
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "uvmanager.h"
#include "formationmanager.h"

namespace Ui {
class OpeningWindow;
}

/**
 * @brief OpeningWindow est un fenêtre de type QDialog permettant de renseigner les XML sources nécessaires au programme.
 */
class OpeningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpeningWindow(QWidget *parent = 0);
    ~OpeningWindow();

public slots:
    /**
     * @brief Ouvre une boîte de dialogue pour spécifier le chemin du XML contenant les UVs.
     */
    void on_btnParcourirUV_clicked();

    /**
     * @brief Ouvre une boîte de dialogue pour spécifier le chemin du XML contenant les formations.
     */
    void on_btnParcourirFormation_clicked();

    /**
     * @brief Ouvre une boîte de dialogue pour spécifier le chemin du XML contenant un dossier étudiant.
     */
    //void on_btnParcourirEtudiant_clicked();

    /**
     * @brief Vérifie que tous les fichiers nécessaires ont été spécifiés, et charge les infos des fichiers dans les modules appropriés.
     * Les UV sont ainsi chargées dans une instance d'UVManager.
     */
    void on_btnValider_clicked();

private:
    Ui::OpeningWindow *ui;
};

#endif // OPENINGWINDOW_H
