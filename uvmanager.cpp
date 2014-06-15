/**
  * \file uvmanager.cpp
  * \brief Code source des classes CategorieManager, Semestre, UV et UVManager
  * \author Clément FICHMANN et Alexandre KEIL
  * \date Juin 2014
  */

#include "uvmanager.h"
#include "utprofilerexception.h"

#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


/**
 * @brief Constructeur de CategorieManager avec les catégories classiques par défaut.
 */
CategorieManager::CategorieManager() {
    categories.insert("CS", "Connaissances Scientifiques");
    categories.insert("TM", "Techniques et Méthodes");
    categories.insert("TSH", "Technologies et Sciences de l'Homme");
    categories.insert("SP", "Stage et Projet");
}

/**
 * @brief Destructeur de CategorieManager
 */
CategorieManager::~CategorieManager() {
}

/**
/** * @brief addItem ajoute une catégorie à la map des catégories
/** * @param code : nom abrégé de la catégorie
/** * @param desc : nom complet de la catégorie
*/
void CategorieManager::addItem(const QString& code, const QString& desc) {
    categories.insert(code, desc);
}


/**
 * @brief removeItem supprime de la map des catégories la catégorie au nom abrégé passé en paramètre.
 * @param code : nom abrégé de la catégorie à supprimer.
 * @return Nombre de catégories supprimées (normalement 1).
 */
int CategorieManager::removeItem(const QString& code) {
    return categories.remove(code);
}

/**
 * @brief getDesc retourne le nom complet d'une catégorie au nom abrégé passé en paramètre.
 * @param code : Nom abrégé de la catégorie
 * @return Nom complet de la catégorie.
 */
QString& CategorieManager::getDesc(const QString& code) const {
    QString result = categories.value(code);
    return result;
}

/**
 * @brief isCat indique si la catégorie passée en paramètre existe.
 * @param code : nom abrégé de la catégorie recherchée.
 * @return Vrai si la catégorie existe dans la map, faux sinon.
 */
bool CategorieManager::isCat(const QString& code) {
    return categories.contains(code);
}

/**
/** * @brief Handler permet l'implémentation du design pattern Singleton.
*/
CategorieManager::Handler CategorieManager::handler=Handler();

/**
 * @brief getInstance permet de récupérer l'unique instance de CategorieManager
 * @return Instance unique de CategorieManager
 */
CategorieManager& CategorieManager::getInstance(){
    if (!handler.instance) handler.instance = new CategorieManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

/**
 * @brief libererInstance supprimer l'unique instance de CategorieManager
 */
void CategorieManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

NoteManager::NoteManager() {
    notes.insert("A");
    notes.insert("B");
    notes.insert("C");
    notes.insert("D");
    notes.insert("E");
    notes.insert("F");
    notes.insert("FX");
    notes.insert("ABS");
    notes.insert("RES");
    notes.insert("EC");
}

NoteManager::~NoteManager() {
}

void NoteManager::addItem(const QString& code) {
    notes.insert(code);
}

int NoteManager::removeItem(const QString& code) {
    return notes.remove(code);
}

bool NoteManager::isNote(const QString& code) {
    return notes.contains(code);
}

NoteManager::Handler NoteManager::handler=Handler();

NoteManager& NoteManager::getInstance(){
    if (!handler.instance) handler.instance = new NoteManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void NoteManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

/**
 * @brief getNbCreditsTotal calcule le nombre total des crédits attribués avec l'obtention de l'UV.
 * @return Somme des crédits des catégories concernées par l'UV.
 */
unsigned int UV::getNbCreditsTotal() const {
    QList<int> credits = categories.values();
    unsigned int total = 0;
    foreach (int c, credits) {
        if (c > 0)
            total += c;
    }
    return total;
}

/**
 * @brief Constructeur de la classe UVManager.
 */
UVManager::UVManager():categorieM(CategorieManager::getInstance()), noteM(NoteManager::getInstance()), file("") {
}

/**
 * @brief load charge les UV du XML vers la QMap de l'UVManager
 * @param f : adresse du fichier XML.
 */
void UVManager::load(const QString& f){
    if (!uvs.isEmpty()) {
        deleteAllUV();
    }
    file=f;

    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier UV");
    }

    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named uvs, we'll go to the next.
            if(xml.name() == "uvs") continue;
            // If it's named uv, we'll dig the information from there.
            if(xml.name() == "uv") {
                QString code;
                QString titre;
                QMap<QString, int> categories;
                bool automne=false;
                bool printemps=false;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that uvs has attribute. */
                if(attributes.hasAttribute("automne")) {
                    QString val =attributes.value("automne").toString();
                    automne=(val == "true" ? true : false);
                }
                if(attributes.hasAttribute("printemps")) {
                    QString val =attributes.value("printemps").toString();
                    printemps=(val == "true" ? true : false);
                }

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named uv.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "uv")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found code.
                        if(xml.name() == "code") {
                            xml.readNext(); code=xml.text().toString();
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        // We've found credits.
                        if(xml.name() == "credits") {
                            QString cat;
                            int nbC;

                            QXmlStreamAttributes attributes = xml.attributes();
                            foreach (QXmlStreamAttribute attribute, attributes) {
                                cat=attribute.name().toString();
                                nbC=attribute.value().toInt();
                                categories.insert(cat, nbC);

                                if (!categorieM.getAllCategories().contains(cat)) {
                                    categorieM.addItem(cat, "");
                                }
                            }
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                addUV(code,titre,categories,automne,printemps);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    fin.close();
}


/**
 * @brief save sauvegarde les UV de la QMap de l'UVManager vers le XML.
 * @param f : adresse du fichier XML.
 */
void UVManager::save(const QString& f){
    file=f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("uvs");
    foreach(UV* uv, uvs){
        stream.writeStartElement("uv");
        stream.writeAttribute("automne", (uv->ouvertureAutomne())?"true":"false");
        stream.writeAttribute("printemps", (uv->ouverturePrintemps())?"true":"false");
        stream.writeTextElement("code",uv->getCode());
        stream.writeTextElement("titre",uv->getTitre());
        stream.writeStartElement("credits");
        foreach (QString cat, uv->getCategories().keys()) {
            QString nbC;
            nbC.setNum(uv->getCategories().value(cat));
            if (!(nbC == "0"))
                stream.writeAttribute(cat, nbC);
        }
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();

    newfile.close();

}

/**
 * @brief Destructeur de la classe UVManager.
 */
UVManager::~UVManager(){
    this->deleteAllUV();
    categorieM.libererInstance();
    noteM.libererInstance();
}

/**
 * @brief addUV ajoute une nouvelle UV à la QMap.
 * @param c : code de la nouvelle UV.
 * @param t : titre de la nouvelle UV
 * @param cat : QMap contenant les différents codes de catégories et les crédits associés
 * @param a : Indique l'ouverture ou non de l'UV à l'automne
 * @param p : Indique l'ouverture ou non de l'UV au printemps
 */
void UVManager::addUV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p){
    //une demande d'écrasement est faite par les fonctions appelant cette méthode
    UV* newuv=new UV(c,t,cat,a,p);
    uvs.insert(c, newuv);

}

/**
 * @brief deleteUV supprime l'UV dont le code est passé en paramètre.
 * @param c : code de l'UV à supprimer
 */
void UVManager::deleteUV(const QString& c){
    if (!uvs.contains(c)) {
        throw UTProfilerException(QString("erreur, UVManager, UV ")+c+QString("déjà existante"));
    }else{
        delete uvs.value(c);
        uvs.remove(c);
    }
}

/**
 * @brief getUV renvoie une référence vers l'UV dont le code est passé en paramètre.
 * @param code : code de l'UV
 * @return Référence vers l'UV
 */
UV& UVManager::getUV(const QString& code){
    UV* uv=uvs.value(code);
    if (!uv) throw UTProfilerException("erreur, UVManager, UV inexistante",__FILE__,__LINE__);
    return *uv;
}

/**
 * @brief const getUV const renvoie une référence const vers l'UV dont le code est passé en paramètre.
 * @param code : code de l'UV
 * @return Référence const vers l'UV.
 */
const UV& UVManager::getUV(const QString& code)const{
    return const_cast<UVManager*>(this)->getUV(code);
}

/**
 * @brief deleteAllUV supprime toutes les UVs contenues dans la QMap des UVs.
 */
void UVManager::deleteAllUV() {
    foreach (UV* uv, uvs)
        delete uv;
    uvs.clear();
}

/**
 * @brief Le Handler permet l'implémentation du design pattern Singleton pour la classe UVManager.
 */
UVManager::Handler UVManager::handler=Handler();

/**
 * @brief getInstance renvoie l'unique instance d'UVManager.
 * @return Instance d'UVManager.
 */
UVManager& UVManager::getInstance(){
    if (!handler.instance) handler.instance = new UVManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

/**
 * @brief libererInstance détruit l'unique instance d'UVManager.
 */
void UVManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}
