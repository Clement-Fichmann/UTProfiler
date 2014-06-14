#ifndef UV_MANAGER_h
#define UV_MANAGER_h

#include "utprofilerexception.h"
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QSet>

using namespace std;


class CategorieManager {
private:
    QMap<QString, QString> categories;
    CategorieManager();
    ~CategorieManager();
    friend struct Handler;
    struct Handler{
        CategorieManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
public:
    void addItem(const QString& code, const QString& desc);
    int removeItem(const QString& code);
    QString& getDesc(const QString& code) const;
    bool isCat(const QString& code);
    static CategorieManager& getInstance();
    static void libererInstance();
    const QMap<QString, QString>& getAllCategories() const {return categories;}
};

//TO DO A basculer chez etudiant manager
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

enum Saison { Automne, Printemps };

//TO DO A basculer chez etudiant manager

class Semestre {
    Saison saison;
    unsigned int annee;
public:
    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
    Saison getSaison() const { return saison; }
    unsigned int getAnnee() const { return annee; }
};

class UV {
    QString code;
    QString titre;
    QMap<QString, int> categories;
    bool automne;
    bool printemps;
    UV(const UV& u);
    UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p): code(c),titre(t),categories(cat),automne(a),printemps(p){}
    friend class UVManager;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
    unsigned int getNbCredits(QString cat) const { return categories.value(cat, 0); }
    unsigned int getNbCreditsTotal() const;
    QMap<QString, int> getCategories() const { return categories; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setCategorie(QString cat, int nbC) { categories.insert(cat, nbC); }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }
};


class UVManager {
private:
    QMap<QString, UV*> uvs;
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
    UVManager();
    ~UVManager();
    CategorieManager& categorieM;
    NoteManager& noteM;
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    QString file;
    void load(const QString& f);
    void save(const QString& f);
    static UVManager& getInstance();
    static void libererInstance();
    void addUV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p);
    void deleteUV(const QString& c);
    const UV& getUV(const QString& code) const;
    UV& getUV(const QString& code);
    const QMap<QString, UV*>& getAllUV() const {return uvs;}
    void deleteAllUV();
    const CategorieManager& getCategorieManager() const {return categorieM;}
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
};*/

class Dossier {
};

#endif
