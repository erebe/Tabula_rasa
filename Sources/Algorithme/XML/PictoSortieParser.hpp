#ifndef PICTOSORTIEPARSER_H
#define PICTOSORTIEPARSER_H

#include "PictoParser.hpp"
#include "pictoSortie.hpp"
class QDomElement;

class PictoSortieParser : public PictoParser
{
public:
    PictoSortieParser();
    Pictogramme* parse(const QDomElement & element, AlgorithmeScene* scene = 0 );
};

#endif // PICTOSORTIEPARSER_H
