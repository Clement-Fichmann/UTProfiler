/**
  * \file formationmanager.h
  * \brief Header des classes Formation et FormationManager
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */

#ifndef FORMATIONMANAGER_H
#define FORMATIONMANAGER_H

#include "utprofilerexception.h"
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QSet>

using namespace std;

/**
 * @brief Structure définissant des crédits à obtenir, fournis par des UV appartenant à une certaine liste.
 */
struct CreditsInUV
{
    QMap<QString, int> credits; /** Map répertoriant les crédits requis par catégories*/
    QSet<QString> uvs; /** Set indiquant les UV fournissant ces crédits*/
};

class formation {
    QString code; /**Nom abrégé de la formation*/
    QString titre; /**Nom complet de la formation*/
    QMap<QString, int> creditsNeeded; /**Crédits par catégorie requis pour la complétion de la formation, hors d'une liste d'UV*/
    QSet<QString> formationsNeeded; /**Formation(s) à suivre pour valider la formation courante*/
    QSet<QString> uvNeeded; /**UV à suivre pour valider la formation*/
    CreditsInUV creditsNeededInUVSet; /**UV à suivre pour les crédits requis*/

    /**
     * @brief Constructeur par recopie
     * @param f : Formation à recopier
     */
    formation(const formation& f);

    /**
     * @brief Constructeur de la classe Formation
     * @param c : nom abrégé de la formation
     * @param t : nom complet de la formation
     * @param credits : crédits à obtenir dans chaque catégorie
     * @param formations : formation requises
     * @param uvs : UV à valider pour compléter la formation
     * @param cInUV :
     */
    formation(const QString& c, const QString& t, QMap<QString, int> credits, QSet<QString> formations, QSet<QString> uvs, CreditsInUV cInUV): code(c),titre(t),creditsNeeded(credits), formationsNeeded(formations), uvNeeded(uvs), creditsNeededInUVSet(cInUV) {}
    friend class formationManager;
public:
    /**
     * @brief Accesseur sur le code de la formation
     * @return Nom abrégé (code) de la formation
     */
    QString getCode() const { return code; }

    /**
     * @brief Accesseur sur le titre de la formation
     * @return Nom complet (titre) de la formation
     */
    QString getTitre() const { return titre; }

    /**
     * @brief Accesseur sur les crédits nécessaires à la complétion de la formation
     * @return QMap de Crédits requis par catégorie
     */
    QMap<QString, int> getCreditsNeeded() const { return creditsNeeded; }

    /**
     * @brief Accesseurs sur les formations requises au préalable
     * @return QSet de Formations requises.
     */
    QSet<QString> getFormationsNeeded() const { return formationsNeeded; }

    /**
     * @brief Accesseurs sur les UV nécessaires à la complétion de la formation
     * @return QSet de code d'UVs
     */
    QSet<QString> getUVNeeded() const { return uvNeeded;}

    /**
    /** * @brief getCreditsNeededInUVSet
    /** * @return
    */
    CreditsInUV getCreditsNeededInUVSet() const {return creditsNeededInUVSet;}

    /**
     * @brief Setter sur le code de la formation
     * @param c : nouveau code de la Formation
     */
    void setCode(const QString& c) { code=c; }

    /**
     * @brief Setter sur le titre de la formation
     * @param t : nouveau titre de la Formation
     */
    void setTitre(const QString& t) { titre=t; }

    /**
     * @brief Setter sur les crédits requis dans une catégorie
     * @param cat : Catégorie à modifier/à insérer
     * @param nbC : Nombre de crédits dans la catégorie.
     */
    void setCreditsNeeded(QString cat, int nbC) { creditsNeeded.insert(cat, nbC); }

    /**
     * @brief Setter sur les formations requises : ajout d'une formation
     * @param formation : Formation à insérer dans les formations préalablement requises
     */
    void setFormationNeeded(QString formation) { formationsNeeded.insert(formation); }

    /**
     * @brief Setter sur les Formations requises : suppression d'une Formation
     * @param formation : Formation à supprimer
     */
    void remooveFormationNeeded(QString formation) {formationsNeeded.remove(formation);}

    /**
     * @brief Setter sur les UV nécessaires : ajout d'une UV
     * @param UV : code de l'UV à ajouter à la liste
     */
    void setUVNeeded(QString UV) {uvNeeded.insert(UV);}

    /**
     * @brief Setter sur les UV nécessaires : suppression d'une UV
     * @param UV : code de l'UV à supprimer de la liste
     */
    void removeUVNeeded(QString UV) {uvNeeded.remove(UV);}

    /**
     * @brief setCreditsNeededInUVSet
     * @param credits
     * @param uvs
     */
    void setCreditsNeededInUVSet(QMap<QString, int> credits, QSet<QString> uvs) {creditsNeededInUVSet.credits=credits; creditsNeededInUVSet.uvs=uvs;}
};

/**
 * @brief La classe FormationManager permet de gérer l'ensemble des Formations
 */
class formationManager {
private:
    QMap<QString, formation*> formations; /**QMap avec pour clé les codes des Formations, et pour valeur des pointeurs vers ces Formations*/

    /**
     * @brief Constructeur par recopie de FormationManager : mis en privé pour préserver le design pattern Singleton
     * @param um : Formation
     */
    formationManager(const formationManager& fm);

    /**
     * @brief Constructeur de la classe FormationManager
     */
    formationManager();

    /**
     * @brief Destructeur de la classe FormationManager
     */
    ~formationManager();
    friend struct Handler;

    /**
     * @brief Le Handler permet l'implémentation du design pattern Singleton pour la classe FormationManager
     */
    struct Handler{
        formationManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    QString file; /**Le chemin d'accès au fichier XML contenant les Formations*/

    /**
     * @brief load charge dans l'instance de FormationManager les Formations contenues dans le fichier XML au chemin passé en paramètre.
     * @param f : chemin du fichier XML
     */
    void load(const QString& f);

    /**
     * @brief save sauvegarde dans le fichier XML au chemin passé en paramètre les Formations contenues dans l'instance de FormationManager
     * @param f : chemin du fichier XML
     */
    void save(const QString& f);

    /**
     * @brief getInstance récupère l'instance unique de Formation Manager
     * @return Référence vers l'instance.
     */
    static formationManager& getInstance();

    /**
     * @brief libererInstance supprime l'instance unique de FormationManager
     */
    static void libererInstance();

    /**
     * @brief addFormation ajoute une Formation à l'instance de FormationManager
     * @param c : nom abrégé (code) de la formation
     * @param t : nom complet (titre) de la formation
     * @param credits : QMap contenant les crédits par catégorie
     * @param formations : QSet des Formations préalablement requises
     * @param uvs : QSet des UVs à suivre pour valider la formation
     * @param cInUV
     */
    void addFormation(const QString& c, const QString& t, QMap<QString, int> credits, QSet<QString> formations, QSet<QString> uvs, CreditsInUV cInUV);

    /**
     * @brief deleteFormation supprime la Formation au code passé en paramètre de l'instance de FormationManager
     * @param c : code de la Formation à supprimer
     */
    void deleteFormation(const QString& c);

    /**
     * @brief const getFormation const renvoie une référence const vers la Formation dont le code est passé en paramètre
     * @param code : code de la Formation à trouver
     * @return Référence const vers la Formation
     */
    const formation& getFormation(const QString& code) const;

    /**
     * @brief getFormation renvoie une référence vers la Formation dont le code est passé en paramètre
     * @param code : code de la Formation à trouver
     * @return Référence vers la Formation
     */
    formation& getFormation(const QString& code);

    /**
     * @brief const getAllFormations const renvoie une référence const vers la QMap formations.
     * Elle contient l'ensemble des Formations de l'instance de FormationManager.
     * @return Référence const vers la QMap des Formations
     */
    const QMap<QString, formation*>& getAllFormations() const {return formations;}

    /**
     * @brief deleteAllFormations supprime toutes les Formations de l'instance de FormationManager
     */
    void deleteAllFormations();
};

#endif // FORMATIONMANAGER_H
