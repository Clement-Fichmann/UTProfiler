#ifndef AJOUTERFORMATIONWINDOW_H
#define AJOUTERFORMATIONWINDOW_H

#include <QDialog>
#include "formationmanager.h"
#include "uvmanager.h"

namespace Ui {
class ajouterformationwindow;
}

class ajouterformationwindow : public QDialog
{
    Q_OBJECT

signals:
    /**
     * @brief formationAdded est un signal émis à la fermeture de la fenêtre si l'utilisateur a demandé l'enregistrement d'une nouvelle formation.
     */
    void formationAdded();

public:
    explicit ajouterformationwindow(QWidget *parent = 0);
    ~ajouterformationwindow();

public slots:
    /**
     * @brief Lorsque le texte contenu dans le champ de saisie du code de la nouvelle formation est éditée, on appelle la fonction formationEditee()
     */
    void on_txtCodeFormation_textChanged();

    /**
     * @brief Lorsque le texte contenu dans le champ de saisie du titre de la nouvelle formation est éditée, on appelle la fonction formationEditee()
     */
    void on_txtDescriptionFormation_textChanged();

    /**
     * @brief formationEditee teste si les champs du code et du titre de la nouvelle formation sont vides.
     * Si l'un des 2 ou les 2 le sont, le bouton "Ajouter la nouvelle formation" devient/reste grisé.
     * Si les 2 champs contiennent du texte, on autorise le click sur le bouton.
     */
    void formationEditee();

    /**
     * @brief Ferme la fenêtre sans enregistrer la formation
     */
    void on_btnAnnuler_clicked();

    /**
     * @brief Teste si la formation existe déjà, au travers du code de la formation.
     * Si oui, on demande à l'utilisateur s'il souhaite écraser l'ancienne formation.
     * Dans le cas où il accepte, et dans le cas où la formation n'existe pas, on ajoute la nouvelle formation à la QMap de formationManager et on émet le signal formationAdded à l'attention de la MainWindow.
     * Sinon, la fenêtre ne se ferme pas pour qu'il puisse modifier la formation.
     */
    void on_btnAccepter_clicked();

private:
    UVManager& uvM;
    formationManager& fM;
    Ui::ajouterformationwindow *ui;
};

#endif // AJOUTERFORMATIONWINDOW_H
