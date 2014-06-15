#ifndef UTPROFILEREXCEPTION_H
#define UTPROFILEREXCEPTION_H

#include <QString>

/**
 * @brief Exceptions pour l'appli UTProfiler
 */
class UTProfilerException{
public:
    /**
     * @brief Constructeur d'exception
     * @param message : message d'erreur
     * @param f : fichier ayant levé l'exception
     * @param l : ligne du fichier concernée
     */
    UTProfilerException(const QString& message, const QString &f="na", unsigned int l=0): info(message),file(f),line(l){}
    /**
     * @brief Renvoie le message de l'exception
     * @return Message d'erreur
     */
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a été levée.
    /**
     * @brief Accesseur sur le nom du fichier
     * @return Nom du fichier concerné
     */
    QString getFile() const { return file; }
    // retourne la ligne du fichier à laquelle cette exception a été levée.
    /**
     * @brief Accesseur sur la ligne du fichier concernée
     * @return Numéro de ligne
     */
    unsigned int getLine() const { return line; }
#endif
private:
    QString info; /**Message d'erreur*/
    QString file; /**Chemin du fichier*/
    unsigned int line; /**Ligne du fichier*/

};

#endif // UTPROFILEREXCEPTION_H
