#ifndef DICTIONARYWRITER_H
#define DICTIONARYWRITER_H

class Dictionary;
class DictionaryEntryWriter;
class QDomElement;
class XMLNodeCreator;

class DictionaryWriter
{
public:
    DictionaryWriter(XMLNodeCreator &creator);
    QDomElement write(Dictionary &dictionary);
private:
    XMLNodeCreator *nodeCreator;
};

#endif // DICTIONARYWRITER_H
