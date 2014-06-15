#ifndef FORMATIONMANAGER_H
#define FORMATIONMANAGER_H

#include "utprofilerexception.h"
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QSet>

using namespace std;

class formation {
    QString code;
    QString titre;
    QMap<QString, int> creditsNeeded;
    UV(const UV& u);
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
    QMap<QString, UV*> uvs;
    UVManager(const UVManager& um);
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

#endif // FORMATIONMANAGER_H
