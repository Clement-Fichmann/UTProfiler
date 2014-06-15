/**
  * \file uvmanager.h
  * \brief Header des classes CategorieManager, Semestre, UV et UVManager
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */
#ifndef UV_MANAGER_h
#define UV_MANAGER_h

#include "utprofilerexception.h"
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QSet>

using namespace std;

/**
 * @brief CategorieManager contient une QMap de 2 QString :
 * La première indique le nom abrégé de la catégorie, la 2e son nom complet.
 */
class CategorieManager {
private:
    QMap<QString, QString> categories; /**Contient les codes des catégories et les noms complets associés*/

    /**
     * @brief Constructeur de CategorieManager avec les catégories classiques par défaut.
     */
    CategorieManager();

    /**
     * @brief Destructeur de CategorieManager
     */
    ~CategorieManager();
    friend struct Handler;
    /**
     * @brief Handler permet l'implémentation du design pattern Singleton.
     */
    struct Handler{
        CategorieManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
public:
    /**
     * @brief addItem ajoute une catégorie à la map des catégories
     * @param code : nom abrégé de la catégorie
     * @param desc : nom complet de la catégorie
     */
    void addItem(const QString& code, const QString& desc);

    /**
     * @brief removeItem supprime de la map des catégories la catégorie au nom abrégé passé en paramètre.
     * @param code : nom abrégé de la catégorie à supprimer.
     * @return Nombre de catégories supprimées (normalement 1).
     */
    int removeItem(const QString& code);

    /**
     * @brief getDesc retourne le nom complet d'une catégorie au nom abrégé passé en paramètre.
     * @param code : Nom abrégé de la catégorie
     * @return Nom complet de la catégorie.
     */
    QString& getDesc(const QString& code) const;

    /**
     * @brief isCat indique si la catégorie passée en paramètre existe.
     * @param code : nom abrégé de la catégorie recherchée.
     * @return Vrai si la catégorie existe dans la map, faux sinon.
     */
    bool isCat(const QString& code);

    /**
     * @brief getInstance permet de récupérer l'unique instance de CategorieManager
     * @return Instance unique de CategorieManager
     */
    static CategorieManager& getInstance();

    /**
     * @brief libererInstance supprimer l'unique instance de CategorieManager
     */
    static void libererInstance();

    /**
     * @brief getAllCategories : accesseur pour la QMap categories
     * @return QMap<QString, QString> categories
     */
    const QMap<QString, QString>& getAllCategories() const {return categories;}
};

/*
class NoteManager {
private:
    QSet<QString> notes;
    NoteManager();
    ~NoteManager();
    friend struct Handler;
    struct Handler{
        NoteManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
public:
    void addItem(const QString& code);
    int removeItem(const QString& code);
    bool isNote(const QString& code);
    static NoteManager& getInstance();
    static void libererInstance();
};
*/

/**
 * @brief Saison est une énumération des 2 saisons possible pour nommer un semestre : Automne et Printemps.
 */
enum Saison { Automne, Printemps };

/*
class Semestre {
    Saison saison;
    unsigned int annee;
public:
    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
    Saison getSaison() const { return saison; }
    unsigned int getAnnee() const { return annee; }
};*/

/**
 * @brief La classe UV permet d'enregistrer les différentes informations sur une UV.
 */
class UV {
    QString code; /**Exemple : LO21*/
    QString titre; /**Exemple : Programmation Orientée Objet*/
    QMap<QString, int> categories; /**QMap contenant le code abrégé d'une catégorie, et le nombre de crédits associés.*/
    bool automne; /**Indique si l'UV est suivable à l'automne*/
    bool printemps; /**Indique si l'UV est suivable au printemps*/

    /**
     * @brief Constructeur de recopie d'UV
     * @param u : UV à recopier.
     */
    UV(const UV& u);

    /**
     * @brief Constructeur de la classe UV
     * @param c : code de l'UV
     * @param t : titre de l'UV
     * @param cat : QMap de crédits par catégorie
     * @param a : booléen autorisant ou non l'inscription à l'UV en automne
     * @param p : booléen autorisant ou non l'inscription à l'UV au printemps
     */
    UV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p): code(c),titre(t),categories(cat),automne(a),printemps(p){}
    friend class UVManager;
public:
    /**
     * @brief Accesseur sur le code de l'UV.
     * @return Code de l'UV.
     */
    QString getCode() const { return code; }

    /**
     * @brief Accesseur sur le titre de l'UV.
     * @return Titre de l'UV.
     */
    QString getTitre() const { return titre; }

    /**
     * @brief getNbCredits renvoie le nombre de crédits de l'UV pour une catégorie donnée.
     * @param cat : code de la catégorie.
     * @return Nombre de crédits attribués dans la catégorie.
     */
    unsigned int getNbCredits(QString cat) const { return categories.value(cat, 0); }

    /**
     * @brief getNbCreditsTotal calcule le nombre total des crédits attribués avec l'obtention de l'UV.
     * @return Somme des crédits des catégories concernées par l'UV.
     */
    unsigned int getNbCreditsTotal() const;

    /**
     * @brief Accesseur sur les catégories de l'UV.
     * @return QMap des catégories de l'UV.
     */
    QMap<QString, int> getCategories() const { return categories; }

    /**
     * @brief L'UV ouvre-t-elle à l'automne ?
     * @return Vrai si c'est le cas, faux sinon.
     */
    bool ouvertureAutomne() const { return automne; }

    /**
     * @brief L'UV ouvre-t-elle au printemps ?
     * @return Vrai si c'est le cas, faux sinon.
     */
    bool ouverturePrintemps() const { return printemps; }

    /**
     * @brief Setter sur le code de l'UV
     * @param c : nouveau code de l'UV
     */
    void setCode(const QString& c) { code=c; }

    /**
     * @brief Setter sur le titre de l'UV.
     * @param t : nouveau titre de l'UV.
     */
    void setTitre(const QString& t) { titre=t; }

    /**
     * @brief Setter pour l'insertion de crédits d'une catégorie.
     * @param cat : Catégorie concernée.
     * @param nbC : Nombre de crédits alloués par l'UV dans la catégorie.
     */
    void setCategorie(QString cat, int nbC) { categories.insert(cat, nbC); }

    /**
     * @brief setOuvertureAutomne ouvre ou non l'UV à l'automne.
     * @param b : vrai pour l'ouverture, faux sinon.
     */
    void setOuvertureAutomne(bool b) { automne=b; }

    /**
     * @brief setOuverturePrintemps ouvre ou non l'UV au printemps.
     * @param b : vrai pour l'ouverture, faux sinon.
     */
    void setOuverturePrintemps(bool b) { printemps=b; }
};

/**
 * @brief La classe UVManager permet de gérer l'ensemble des UVs.
 */
class UVManager {
private:
    QMap<QString, UV*> uvs; /**QMap contenant le code de l'UV en clé, et un pointeur vers l'UV associée.*/

    /**
     * @brief Constructeur de recopie d'UVManager : passé en private pour éviter les doublons.
     * @param um : UVManager à recopier.
     */
    UVManager(const UVManager& um);

    /**
     * @brief Constructeur de la classe UVManager.
     */
    UVManager();

    /**
     * @brief Destructeur de la classe UVManager.
     */
    ~UVManager();
    CategorieManager& categorieM; /**Référence vers l'instance unique de CategorieManager.*/
    NoteManager& noteM;
    friend struct Handler;

    /**
     * @brief Le Handler permet l'implémentation du design pattern Singleton pour la classe UVManager.
     */
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    QString file; /**Adresse du fichier XML des UV*/

    /**
     * @brief load charge les UV du XML vers la QMap de l'UVManager
     * @param f : adresse du fichier XML.
     */
    void load(const QString& f);

    /**
     * @brief save sauvegarde les UV de la QMap de l'UVManager vers le XML.
     * @param f : adresse du fichier XML.
     */
    void save(const QString& f);

    /**
     * @brief getInstance renvoie l'unique instance d'UVManager.
     * @return Instance d'UVManager.
     */
    static UVManager& getInstance();

    /**
     * @brief libererInstance détruit l'unique instance d'UVManager.
     */
    static void libererInstance();

    /**
     * @brief addUV ajoute une nouvelle UV à la QMap.
     * @param c : code de la nouvelle UV.
     * @param t : titre de la nouvelle UV
     * @param cat : QMap contenant les différents codes de catégories et les crédits associés
     * @param a : Indique l'ouverture ou non de l'UV à l'automne
     * @param p : Indique l'ouverture ou non de l'UV au printemps
     */
    void addUV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p);

    /**
     * @brief deleteUV supprime l'UV dont le code est passé en paramètre.
     * @param c : code de l'UV à supprimer
     */
    void deleteUV(const QString& c);

    /**
     * @brief const getUV const renvoie une référence const vers l'UV dont le code est passé en paramètre.
     * @param code : code de l'UV
     * @return Référence const vers l'UV.
     */
    const UV& getUV(const QString& code) const;

    /**
     * @brief getUV renvoie une référence vers l'UV dont le code est passé en paramètre.
     * @param code : code de l'UV
     * @return Référence vers l'UV
     */
    UV& getUV(const QString& code);

    /**
     * @brief getAllUV renvoie une référence vers la QMap contenant toutes les UV.
     * @return Référence vers la QMap uvs
     */
    const QMap<QString, UV*>& getAllUV() const {return uvs;}

    /**
     * @brief deleteAllUV supprime toutes les UVs contenues dans la QMap des UVs.
     */
    void deleteAllUV();

    /**
     * @brief getCategorieManager renvoie une référence vers l'unique instance de CategorieManager.
     * @return Référence sur CategorieManager
     */
    CategorieManager& getCategorieManager() const {return categorieM;}
    const NoteManager& getNoteManager() const {return noteM;}
};


/*class Inscription {
    const UV* uv;
    Semestre semestre;
    Note resultat;
public:
    Inscription(const UV& u, const Semestre& s, Note res=EC):uv(&u),semestre(s),resultat(res){}
    const UV& getUV() const { return *uv; }
    Semestre getSemestre() const { return semestre; }
    Note getResultat() const { return resultat; }
    void setResultat(Note newres) { resultat=newres; }
};

class Dossier {
};*/

#endif
