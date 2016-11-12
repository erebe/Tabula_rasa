#ifndef PICTOCONDITIONPARSER_H
#define PICTOCONDITIONPARSER_H

#include "PictoParser.hpp"

class PictoConditionParser : public PictoParser
{
public:
    PictoConditionParser();
    Pictogramme* parse(const QDomElement & element, Algorithm* algorithm = 0 );
};

#endif // PICTOCONDITIONPARSER_H
