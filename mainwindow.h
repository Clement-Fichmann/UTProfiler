#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
  * \file mainwindow.h
  * \brief Header de la classe MainWindow : fenêtre principale d'UTProfiler
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QPointer>
#include <QCloseEvent>
#include "uvmanager.h"
#include "formationmanager.h"
#include "ajouteruvwindow.h"
#include "ajouterformationwindow.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief La classe MainWindow est une fenêtre de type QMainWindow contenant l'interface principale de l'application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief Ouvre une boîte de dialogue pour choisir un nouveau fichier XML d'UV, et en charge les UV dans la QMap de l'UVManager
     */
    void on_actionChoisir_le_fichier_des_UV_triggered();

    /**
     * @brief Ouvre une boîte de dialogue pour choisir un nouveau fichier XML de formations
     */
    void on_actionCharger_un_nouveau_fichier_formations_triggered();

    /**
     * @brief Ouvre une boîte de dialogue pour choisir un nouveau fichier XML de dossier étudiant
     */
    void on_actionDossier_Etudiant_triggered();

    /**
     * @brief Demande confirmation à l'utilisateur avant de quitter, et lui propose d'enregistrer ses modifications.
     */
    void on_actionQuitter_triggered();

    /**
     * @brief Lorsque l'utilisateur choisit une UV dans la liste déroulante des UV, ce slot remplit le formulaire d'édition d'UV avec les informations sur l'UV.
     */
    void on_listUV_currentIndexChanged();

    /**
     * @brief Lorsque l'utilisateur choisit une formation dans la liste déroulante des formation, ce slot remplit le formulaire d'édition de formation avec les informations sur la formation.
     */
    void on_listFormation_currentIndexChanged();

    /**
     * @brief Appelle le slot UVEditee lorsque le champ de texte du code de l'UV est modifié.
     */
    void on_txtCodeUV_textChanged();

    /**
     * @brief Appelle le slot UVEditee lorsque le champ de texte du titre de l'UV est modifié.
     */
    void on_txtDescription_textChanged();

    /**
     * @brief Appelle le slot UVEditee lorsque la case "Automne" du formulaire est cochée ou décochée.
     */
    void on_chkAutomne_stateChanged();
    /**
     * @brief Appelle le slot UVEditee lorsque la case "Printemps" du formulaire est cochée ou décochée.
     */
    void on_chkPrintemps_stateChanged();

    /**
     * @brief Appelle le slot UVEditee lorsque les crédits de l'UV sont sélectionnés.
     */
    void on_tableCredits_clicked();

    /**
     * @brief Appelle le slot FormationEditee lorsque le champ de texte du code de la formation est modifié.
     */
    void on_txtCodeFormation_textChanged();

    /**
     * @brief Appelle le slot FormationEditee lorsque le champ de texte du titre de la formation est modifié.
     */
    void on_txtDescriptionFormation_textChanged();

    /**
     * @brief Appelle le slot FormationEditee lorsque les crédits nécessaires pour valider la formation sont sélectionnés.
     */
    void on_tableFormationCreditsNeeded_clicked();

    /**
     * @brief Appelle le slot FormationEditee lorsque les crédits nécessaires dans une liste d'UV pour valider la formation sont sélectionnés.
     */
    void on_tableFormationCreditsNeededInUVSet_Credits_clicked();

    /**
     * @brief Appelle le slot FormationEditee lorsque les UV de la liste des UV pour valider la formation sont sélectionnées.
     */
    void on_tableFormationCreditsNeededInUVSet_UV_clicked();

    /**
     * @brief Appelle le slot FormationEditee lorsque les formations nécessaires pour valider la formation sont sélectionnées.
     */
    void on_tableFormationFormationsNeeded_clicked();

    /**
     * @brief Appelle le slot FormationEditee lorsque les UV nécessaires pour valider la formation sont sélectionnées.
     */
    void on_tableFormationUVNeeded_clicked();

    /**
     * @brief UVEditee s'active lorsqu'un des éléments du formulaire d'édition est altérée.
     * Il teste alors si le champ du code et du titre de l'UV sont remplis; si oui, il débloque le bouton "Sauvegarder les modifications", désactivé par défaut.
     */
    void UVEditee();

    /**
     * @brief FormationEditee s'active lorsqu'un des éléments du formulaire d'édition est altérée.
     * Il teste alors si le champ du code et du titre de la formation sont remplis; si oui, il débloque le bouton "Sauvegarder les modifications", désactivé par défaut.
     */
    void FormationEditee();

    /**
     * @brief refreshUVList actualise la liste des UV quand il est appelé
     */
    void refreshUVList();

    /**
     * @brief refreshFormationList actualise la liste des formations quand il est appelé
     */
    void refreshFormationList();

    /**
     * @brief Enregistre les modifications apportées à l'UV
     */
    void on_btnSauverUV_clicked();

    /**
     * @brief Enregistre les modifications apportées à la formation
     */
    void on_btnSauverFormation_clicked();

    /**
     * @brief Ouvre une ajouterUVWindow pour ajouter une nouvelle UV
     */
    void on_btnAjouterUV_clicked();

    /**
     * @brief Ouvre une ajouterFormationWindow pour ajouter une nouvelle formation
     */
    void on_btnAjouterFormation_clicked();

    /**
     * @brief Demande confirmation puis supprime l'UV sélectionnée dans la liste déroulante.
     */
    void on_btnDeleteUV_clicked();

    /**
     * @brief Demande confirmation puis supprime la formation sélectionnée dans la liste déroulante.
     */
    void on_btnDeleteFormation_clicked();

    /**
     * @brief Sauvegarde le contenu de la QMap uvs de l'instance d'UVManager dans le fichier XML (appel à la fonction UVManager::save() ).
     */
    void on_actionSaveUV_triggered();

    /**
     * @brief Sauvegarde le contenu de la QMap formations de l'instance de formationManager dans le fichier XML (appel à la fonction formationManager::save() ).
     */
    void on_actionSaveFormations_triggered();

    /**
     * @brief Sauvegarde les UV, les formations et les infos sur un étudiant dans leurs fichiers respectifs.
     */
    void on_actionSaveTous_les_fichiers_triggered();

private:
    UVManager& uvM;
    formationManager& fM;
    Ui::MainWindow *ui;

protected:
    /**
    * @brief Gère les confirmations lorsque l'utilisateur ferme la fenêtre.
    * @param event : évènement de fermeture.
    */
    void closeEvent(QCloseEvent* event);
};

#endif // MAINWINDOW_H
