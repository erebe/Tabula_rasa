#ifndef PICTOCONDITIONMULTIPLEPARSER_H
#define PICTOCONDITIONMULTIPLEPARSER_H

#include "PictoParser.hpp"

class PictoConditionMultipleParser : public PictoParser
{
public:
    PictoConditionMultipleParser();
    Pictogramme* parse(const QDomElement & element, Algorithm* algorithm = 0 );
};

#endif // PICTOCONDITIONMULTIPLEPARSER_H
