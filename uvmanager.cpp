#include "uvmanager.h"
#include "utprofilerexception.h"

#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


CategorieManager::CategorieManager() {
    categories.insert("CS", "Connaissances Scientifiques");
    categories.insert("TM", "Techniques et Méthodes");
    categories.insert("TSH", "Technologies et Sciences de l'Homme");
    categories.insert("SP", "Stage et Projet");
}

CategorieManager::~CategorieManager() {
}

void CategorieManager::addItem(const QString& code, const QString& desc) {
    categories.insert(code, desc);
}

int CategorieManager::removeItem(const QString& code) {
    return categories.remove(code);
}

QString& CategorieManager::getDesc(const QString& code) const {
    QString result = categories.value(code);
    return result;
}

bool CategorieManager::isCat(const QString& code) {
    return categories.contains(code);
}

CategorieManager::Handler CategorieManager::handler=Handler();

CategorieManager& CategorieManager::getInstance(){
    if (!handler.instance) handler.instance = new CategorieManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

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


unsigned int UV::getNbCreditsTotal() const {
    QList<int> credits = categories.values();
    unsigned int total = 0;
    foreach (int c, credits) {
        if (c > 0)
            total += c;
    }
    return total;
}


UVManager::UVManager():categorieM(CategorieManager::getInstance()), noteM(NoteManager::getInstance()), file("") {
}

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
            stream.writeAttribute(cat, nbC);
        }
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();

    newfile.close();

}

UVManager::~UVManager(){
    if (file!="" && !uvs.isEmpty())
        save(file);
    this->deleteAllUV();
    categorieM.libererInstance();
    noteM.libererInstance();
}

void UVManager::addUV(const QString& c, const QString& t, QMap<QString, int> cat, bool a, bool p){
    if (uvs.contains(c)) {
        throw UTProfilerException(QString("erreur, UVManager, UV ")+c+QString("déjà existante"));
    }else{
        UV* newuv=new UV(c,t,cat,a,p);
        uvs.insert(c, newuv);
    }
}

void UVManager::deleteUV(const QString& c){
    if (!uvs.contains(c)) {
        throw UTProfilerException(QString("erreur, UVManager, UV ")+c+QString("déjà existante"));
    }else{
        delete uvs.value(c);
        uvs.remove(c);
    }
}

UV& UVManager::getUV(const QString& code){
    UV* uv=uvs.value(code);
    if (!uv) throw UTProfilerException("erreur, UVManager, UV inexistante",__FILE__,__LINE__);
    return *uv;
}

const UV& UVManager::getUV(const QString& code)const{
    return const_cast<UVManager*>(this)->getUV(code);
}

void UVManager::deleteAllUV() {
    foreach (UV* uv, uvs)
        delete uv;
    uvs.clear();
}

UVManager::Handler UVManager::handler=Handler();

UVManager& UVManager::getInstance(){
    if (!handler.instance) handler.instance = new UVManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void UVManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}
