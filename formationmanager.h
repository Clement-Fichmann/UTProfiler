#ifndef FORMATIONMANAGER_H
#define FORMATIONMANAGER_H

#include "utprofilerexception.h"
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QSet>

using namespace std;

struct CreditsInUV
{
    QMap<QString, int> credits;
    QSet<QString> uvs;
};

class formation {
    QString code;
    QString titre;
    QMap<QString, int> creditsNeeded;
    QSet<QString> formationsNeeded;
    QSet<QString> uvNeeded;
    CreditsInUV creditsNeededInUVSet;
    formation(const formation& f);
    formation(const QString& c, const QString& t, QMap<QString, int> credits, QSet<QString> formations, QSet<QString> uvs, CreditsInUV cInUV): code(c),titre(t),creditsNeeded(credits), formationsNeeded(formations), uvNeeded(uvs), creditsNeededInUVSet(cInUV) {}
    friend class formationManager;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
    QMap<QString, int> getCreditsNeeded() const { return creditsNeeded; }
    QSet<QString> getFormationsNeeded() const { return formationsNeeded; }
    QSet<QString> getUVNeeded() const { return uvNeeded;}
    QMap<QMap<QString, int>, QSet<QString>> getCreditsNeededInUVSet() const {return creditsNeededInUVSet;}
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setCreditsNeeded(QString cat, int nbC) { creditsNeeded.insert(cat, nbC); }
    void setFormationNeeded(QString formation) { formationsNeeded.insert(formation); }
    void remooveFormationNeeded(QString formation) {formationsNeeded.remove(formation);}
    void setUVNeeded(QString UV) {uvNeeded.remove(UV);}
    void setCreditsNeededInUVSet(QMap<QString, int> credits, QSet<QString> uvs) {creditsNeededInUVSet.credits=credits; creditsNeededInUVSet.uvs=uvs;}
};


class formationManager {
private:
    QMap<QString, formation*> formations;
    formationManager(const formationManager& um);
    formationManager();
    ~formationManager();
    friend struct Handler;
    struct Handler{
        formationManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    QString file;
    void load(const QString& f);
    void save(const QString& f);
    static formationManager& getInstance();
    static void libererInstance();
    void addFormation(const QString& c, const QString& t, QMap<QString, int> credits, QSet<QString> formations, QSet<QString> uvs, CreditsInUV cInUV);
    void deleteFormation(const QString& c);
    const formation& getFormation(const QString& code) const;
    UV& getFormation(const QString& code);
    const QMap<QString, formation*>& getAllFormations() const {return formations;}
    void deleteAllFormations();
};

#endif // FORMATIONMANAGER_H
