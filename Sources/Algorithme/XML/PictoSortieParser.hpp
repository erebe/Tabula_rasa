#ifndef PICTOSORTIEPARSER_H
#define PICTOSORTIEPARSER_H

#include "PictoParser.hpp"
#include "pictoSortie.hpp"
class QDomElement;

class PictoSortieParser : PictoParser
{
public:
    PictoSortieParser();
    PictoSortie* parse(const QDomElement &element);
};

#endif // PICTOSORTIEPARSER_H
