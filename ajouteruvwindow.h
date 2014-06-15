#ifndef AJOUTERUVWINDOW_H
#define AJOUTERUVWINDOW_H
/**
  * \file ajouteruvwindow.h
  * \brief Header de la classe ajouterUVWindow : fenêtre d'ajout d'UV
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */
#include <QDialog>
#include "uvmanager.h"

namespace Ui {
class ajouterUVWindow;
}

/**
 * @brief ajouterUVWindow est une fenêtre de type QDialog permettant la création d'une nouvelle UV
 */
class ajouterUVWindow : public QDialog
{
    Q_OBJECT

signals:
    /**
     * @brief UVAdded est un signal émis à la fermeture de la fenêtre si l'utilisateur a demandé l'enregistrement d'une nouvelle UV.
     */
    void UVAdded();

public:
    explicit ajouterUVWindow(QWidget *parent = 0);
    ~ajouterUVWindow();

public slots:
    /**
     * @brief Lorsque le texte contenu dans le champ de saisie du code de la nouvelle UV est éditée, on appelle la fonction UVEditee()
     */
    void on_txtCodeNewUV_textChanged();

    /**
     * @brief Lorsque le texte contenu dans le champ de saisie du titre de la nouvelle UV est éditée, on appelle la fonction UVEditee()
     */
    void on_txtDescNewUV_textChanged();

    /**
     * @brief UVEditee teste si les champs du code et du titre de la nouvelle UV sont vides.
     * Si l'un des 2 ou les 2 le sont, le bouton "Ajouter la nouvelle UV" devient/reste grisé.
     * Si les 2 champs contiennent du texte, on autorise le click sur le bouton.
     */
    void UVEditee();

    /**
     * @brief Ferme la fenêtre sans enregistrer l'UV
     */
    void on_btnAnnuler_clicked();

    /**
     * @brief Crée une QMap contenant les crédits par catégories de la nouvelle UV
     * Teste si l'UV existe déjà, au travers du code de l'UV.
     * Si oui, on demande à l'utilisateur s'il souhaite écraser l'ancienne UV.
     * Dans le cas où il accepte, et dans le cas où l'UV n'existe pas, on ajoute la nouvelle UV à la QMap d'UVManager et on émet le signal UVAdded à l'attention de la MainWindow.
     * Sinon, la fenêtre ne se ferme pas pour qu'il puisse modifier l'UV.
     */
    void on_btnAccepter_clicked();

private:
    UVManager& uvM; /**Référence vers l'UVManager*/
    Ui::ajouterUVWindow *ui; /**Pointeur vers les QWidgets de la fenêtre*/
};

#endif // AJOUTERUVWINDOW_H
