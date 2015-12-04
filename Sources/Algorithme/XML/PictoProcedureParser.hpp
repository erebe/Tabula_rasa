#ifndef PICTOPROCEDUREPARSER_H
#define PICTOPROCEDUREPARSER_H

#include "PictoParser.hpp"

class PictoProcedureParser : public PictoParser
{
public:
    PictoProcedureParser();
    Pictogramme* parse(const QDomElement & element, Algorithm* algorithm = 0 );
};

#endif // PICTOPROCEDUREPARSER_H
