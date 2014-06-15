#include "formationmanager.h"
#include "uvmanager.h"
#include "utprofilerexception.h"

#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


formationManager::formationManager(): file("") {
}

void formationManager::load(const QString& f){
    if (!formations.isEmpty()) {
        deleteAllFormations();
    }
    file=f;

    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier formations");
    }

    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QStringRef test;
        QXmlStreamReader::TokenType token = xml.readNext();
        test = xml.name();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named formations, we'll go to the next.
            if(xml.name() == "formations") continue;
            // If it's named formation, we'll dig the information from there.
            if(xml.name() == "formation") {
                QString code;
                QString titre;
                QMap<QString, int> creditsNeeded;
                QSet<QString> formationsNeeded;
                QSet<QString> uvNeeded;
                CreditsInUV creditsNeededInUVSet;

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named formation.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "formation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found code.
                        if(xml.name() == "code") {
                            xml.readNext(); code=xml.text().toString();
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        // We've found creditsNeeded.
                        if(xml.name() == "creditsNeeded") {
                            QString cat;
                            int nbC;

                            QXmlStreamAttributes attributes = xml.attributes();
                            foreach (QXmlStreamAttribute attribute, attributes) {
                                cat=attribute.name().toString();
                                nbC=attribute.value().toInt();
                                creditsNeeded.insert(cat, nbC);

                                if (!UVManager::getInstance().getCategorieManager().getAllCategories().contains(cat)) {
                                    UVManager::getInstance().getCategorieManager().addItem(cat, "");
                                }
                            }
                        }
                        // We've found formationNeeded.
                        if(xml.name() == "formationNeeded") {
                            xml.readNext(); formationsNeeded.insert(xml.text().toString());
                        }
                        if(xml.name() == "uvNeeded") {
                            xml.readNext(); uvNeeded.insert(xml.text().toString());
                        }
                        if(xml.name() == "creditsNeededInUVSet") {
                            QString cat;
                            int nbC;
                            QMap<QString, int> credits;
                            QSet<QString> uvs;

                            QXmlStreamAttributes attributes = xml.attributes();
                            foreach (QXmlStreamAttribute attribute, attributes) {
                                cat=attribute.name().toString();
                                nbC=attribute.value().toInt();
                                credits.insert(cat, nbC);

                                if (!UVManager::getInstance().getCategorieManager().getAllCategories().contains(cat)) {
                                    UVManager::getInstance().getCategorieManager().addItem(cat, "");
                                }
                            }
                            xml.readNext();

                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "creditsNeededInUVSet")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "uv") {
                                        xml.readNext(); uvs.insert(xml.text().toString());
                                    }
                                }
                                xml.readNext();
                            }
                            creditsNeededInUVSet.credits=credits;
                            creditsNeededInUVSet.uvs=uvs;
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                addFormation(code,titre,creditsNeeded,formationsNeeded,uvNeeded,creditsNeededInUVSet);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier formations, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    fin.close();
}



void formationManager::save(const QString& f){
    file=f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("formations");
    foreach(formation* formation, formations){
        stream.writeStartElement("formation");
        stream.writeTextElement("code",formation->getCode());
        stream.writeTextElement("titre",formation->getTitre());
        stream.writeStartElement("creditsNeeded");
        foreach (QString cat, formation->getCreditsNeeded().keys()) {
            QString nbC;
            nbC.setNum(formation->getCreditsNeeded().value(cat));
            if (!(nbC == "0"))
                stream.writeAttribute(cat, nbC);
        }
        stream.writeEndElement();
        foreach (QString form, formation->getFormationsNeeded().values())
            stream.writeTextElement("formationNeeded", form);
        foreach (QString uv, formation->getUVNeeded().values())
            stream.writeTextElement("uvNeeded", uv);
        stream.writeStartElement("creditsNeededInUVSet");
        foreach (QString cat, formation->getCreditsNeededInUVSet().credits.keys()) {
            QString nbC;
            nbC.setNum(formation->getCreditsNeededInUVSet().credits.value(cat));
            if (!(nbC == "0"))
                stream.writeAttribute(cat, nbC);
        }
        foreach (QString uv, formation->getCreditsNeededInUVSet().uvs.values())
            stream.writeTextElement("uv", uv);
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();

    newfile.close();

}

formationManager::~formationManager(){
    this->deleteAllFormations();
}

void formationManager::addFormation(const QString& c, const QString& t, QMap<QString, int> credits, QSet<QString> formationsNeeded, QSet<QString> uvs, CreditsInUV cInUV){
        formation* newformation=new formation(c,t,credits,formationsNeeded,uvs, cInUV);
        formations.insert(c, newformation);
}

void formationManager::deleteFormation(const QString& c){
    if (!formations.contains(c)) {
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
