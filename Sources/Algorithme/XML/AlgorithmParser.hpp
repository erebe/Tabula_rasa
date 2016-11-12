#ifndef ALGORITHMPARSER_H
#define ALGORITHMPARSER_H

#include <QDomElement>
class Algorithm;

class AlgorithmParser
{
public:
    AlgorithmParser();
    Algorithm* parse(const QDomElement & element);
};

#endif // ALGORITHMPARSER_H
