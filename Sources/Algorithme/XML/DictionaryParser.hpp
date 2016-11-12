#ifndef DICTIONARYPARSER_H
#define DICTIONARYPARSER_H

#include <QDomElement>
#include "XML/DictionaryEntryParser.hpp"
class Dictionary;

class DictionaryParser
{
public:
    DictionaryParser();
    Dictionary* parse(const QDomElement & element);
private:
    DictionaryEntryParser entryParser;
};

#endif // DICTIONARYPARSER_H
