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
};

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
    unsigned int getNbCredits(QString cat) const { return categories.value(cat, -1); }
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
    UV** uvs;
    unsigned int nbUV;
    unsigned int nbMaxUV;
    void addItem(UV* uv);
    bool modification;
    UV* trouverUV(const QString& c) const;
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
    UVManager();
    ~UVManager();
    QString file;
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:

    void load(const QString& f);
   // void save(const QString& f);
    static UVManager& getInstance();
    static void libererInstance();
    void ajouterUV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p);
    const UV& getUV(const QString& code) const;
    UV& getUV(const QString& code);
    /*class Iterator {
        friend class UVManager;
        UV** currentUV;
        unsigned int nbRemain;
        Iterator(UV** u, unsigned nb):currentUV(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentUV(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            nbRemain--;
            currentUV++;
        }
        UV& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    Iterator getIterator() {
        return Iterator(uvs,nbUV);
    }

    class iterator {
        UV** current;
        iterator(UV** u):current(u){}
        friend class UVManager;
    public:
        iterator():current(0){}
        UV& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(uvs); }
    iterator end() { return iterator(uvs+nbUV); }

    class FilterIterator {
        friend class UVManager;
        UV** currentUV;
        unsigned int nbRemain;
        QMap<QString, int> categories;
        FilterIterator(UV** u, unsigned nb, QMap<QString, int> c):currentUV(u),nbRemain(nb),categories(c){
            while(nbRemain>0 && (*currentUV)->getCategories().keys()!=categorie){
                nbRemain--; currentUV++;
            }
        }
    public:
        FilterIterator():nbRemain(0),currentUV(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            do {
                nbRemain--; currentUV++;
            }while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie);
        }
        UV& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    FilterIterator getFilterIterator(QMap<QString, int> c) {
        return FilterIterator(uvs,nbUV,c);
    }*/
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

class Formation{
};

#endif
