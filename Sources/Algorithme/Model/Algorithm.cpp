#include "Algorithm.hpp"

Algorithm::Algorithm(const QString& name, Dictionary* dictionary) : name_(name), dictionary_(*dictionary)
{
}

void Algorithm::addPictogram(Pictogramme* picto) {
    pictos_.push_back(picto);
}

void Algorithm::removePictogram(Pictogramme *picto) {
    pictos_.removeOne(picto);
}
