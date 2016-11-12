#ifndef PICTOITERATIONPARSER_H
#define PICTOITERATIONPARSER_H

#include "PictoParser.hpp"

class PictoIterationParser : public PictoParser
{
public:
    PictoIterationParser();
    Pictogramme* parse(const QDomElement & element, Algorithm* algorithm = 0 );
};

#endif // PICTOITERATIONPARSER_H
