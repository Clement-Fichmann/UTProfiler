#ifndef UTPROFILEREXCEPTION_H
#define UTPROFILEREXCEPTION_H

#include <QString>

class UTProfilerException{
public:
    UTProfilerException(const QString& message, const QString &f="na", unsigned int l=0): info(message),file(f),line(l){}
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a été levée.
    QString getFile() const { return file; }
    // retourne la ligne du fichier à laquelle cette exception a été levée.
    unsigned int getLine() const { return line; }
#endif
private:
    QString info;
    QString file;
    unsigned int line;

};

#endif // UTPROFILEREXCEPTION_H
