#ifndef ELEMENTWRITER_H
#define ELEMENTWRITER_H

class DictionaryEntry;
class QDomElement;
class XMLNodeCreator;

class DictionaryEntryWriter
{
public:
    DictionaryEntryWriter(XMLNodeCreator &creator);
    QDomElement write(const DictionaryEntry &element);
private:
    XMLNodeCreator *nodeCreator;
};

#endif // ELEMENTWRITER_H
