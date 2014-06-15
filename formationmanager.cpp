#include "formationmanager.h"
#include "utprofilerexception.h"

#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


formationManager::formationManager(): file("") {
}

void formationManager::load(const QString& f){
    /* TO DO
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
                // Let's check that uvs has attribute.
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
    fin.close();    */
}



void formationManager::save(const QString& f){
    /* TO DO
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

    newfile.close();    */

}

formationManager::~formationManager(){
    this->deleteAllFormations();
}

void formationManager::addFormation(const QString& c, const QString& t, QMap<QString, int> credits, QSet<QString> formationsNeeded, QSet<QString> uvs, CreditsInUV cInUV){
        formation* newformation=new formation(c,t,credits,formationsNeeded,uvs, cInUV);
        formations.insert(c, newformation);
}

void formationManager::deleteformation(const QString& c){
    if (!uvs.contains(c)) {
        throw UTProfilerException(QString("erreur, UVManager, UV ")+c+QString("déjà existante"));
    }else{
        delete formations.value(c);
        formations.remove(c);
    }
}

formation& formationManager::getFormation(const QString& code){
    formation* f=formations.value(code);
    if (!f) throw UTProfilerException("erreur, formationManager, formation inexistante",__FILE__,__LINE__);
    return *f;
}

const formation& formationManager::getFormation(const QString& code)const{
    return const_cast<formationManager*>(this)->getFormation(code);
}

void formationManager::deleteAllFormations() {
    foreach (formation* formation, formations)
        delete formation;
    formations.clear();
}

formationManager::Handler formationManager::handler=Handler();

formationManager& formationManager::getInstance(){
    if (!handler.instance) handler.instance = new formationManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void formationManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}
