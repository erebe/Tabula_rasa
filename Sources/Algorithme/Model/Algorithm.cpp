#include "Algorithm.hpp"

Algorithm::Algorithm(const QString& name)
{
    name_ = name;
}

void Algorithm::addPictogram(Pictogramme* picto) {
    pictos_.push_back(picto);
}

void Algorithm::removePictogram(Pictogramme *picto) {
    pictos_.removeOne(picto);
}
