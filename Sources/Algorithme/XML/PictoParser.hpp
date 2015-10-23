#ifndef PICTOPARSER_H
#define PICTOPARSER_H

class Pictogramme;
class QDomElement;

class PictoParser
{
public:
    PictoParser();
    virtual Pictogramme* parse(const QDomElement & element) = 0;
    virtual ~PictoParser();
};

#endif // PICTOPARSER_H
