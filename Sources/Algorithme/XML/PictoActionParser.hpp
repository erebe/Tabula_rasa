#ifndef PICTOACTIONPARSER_H
#define PICTOACTIONPARSER_H

#include "PictoParser.hpp"

class PictoActionParser : public PictoParser
{
public:
    PictoActionParser();
    Pictogramme* parse(const QDomElement & element, AlgorithmeScene* scene = 0 );
};

#endif // PICTOACTIONPARSER_H
