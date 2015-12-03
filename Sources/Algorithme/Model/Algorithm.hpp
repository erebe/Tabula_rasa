#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QString>
#include <QList>
class Pictogramme;

class Algorithm
{
private:
    QString name_; //Nom de l'agorithme
    QList<Pictogramme*> pictos_; //Liste de tous les pictogrammes de l'algorithme (sans les liaisons)
public:
    Algorithm(const QString& name);
    inline QString name() { return name_; }
    inline void setName( const QString& name ) { name_ = name; }
    void addPictogram(Pictogramme* picto);
    void removePictogram(Pictogramme *picto);
    inline QList<Pictogramme*> allPictograms() { return pictos_; }
};

#endif // ALGORITHM_H
