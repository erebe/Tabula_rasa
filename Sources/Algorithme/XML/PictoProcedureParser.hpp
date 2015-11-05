#ifndef PICTOPROCEDUREPARSER_H
#define PICTOPROCEDUREPARSER_H

#include "PictoParser.hpp"

class PictoProcedureParser : public PictoParser
{
public:
    PictoProcedureParser();
    Pictogramme* parse(const QDomElement & element, AlgorithmeScene* scene = 0 );
};

#endif // PICTOPROCEDUREPARSER_H
