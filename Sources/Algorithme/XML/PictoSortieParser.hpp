#ifndef PICTOSORTIEPARSER_H
#define PICTOSORTIEPARSER_H

#include "PictoParser.hpp"
class QDomElement;

class PictoSortieParser : public PictoParser
{
public:
    PictoSortieParser();
    Pictogramme* parse(const QDomElement & element, Algorithm* algorithm = 0 );
};

#endif // PICTOSORTIEPARSER_H
