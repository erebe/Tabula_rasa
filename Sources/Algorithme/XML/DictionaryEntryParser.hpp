#ifndef ELEMENTPARSER_H
#define ELEMENTPARSER_H

class QDomNode;
class QDomElement;
class DictionaryEntry;
class QString;

class DictionaryEntryParser
{
public:
    DictionaryEntryParser();
    DictionaryEntry* parse(const QDomElement &element);
private:
    QString readText(const QDomNode & node, const QString name);
};

#endif // ELEMENTPARSER_H
