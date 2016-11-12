#include "DictionaryWriter.hpp"
#include <QDomElement>
#include "XML/XMLNodeCreator.hpp"
#include "XML/DictionaryEntryWriter.hpp"
#include "Model/Dictionary.hpp"

DictionaryWriter::DictionaryWriter(XMLNodeCreator &creator) : nodeCreator(&creator)
{

}

QDomElement DictionaryWriter::write(Dictionary &dictionary) {
    QDomElement dictionaryNode = nodeCreator->createNode("Dictionary");
    DictionaryEntryWriter entryWriter(*nodeCreator);
    foreach (const DictionaryEntry &entry, *dictionary.entries()) {
        QDomElement elementNode = entryWriter.write(entry);
        dictionaryNode.appendChild(elementNode);
    }
    return dictionaryNode;
}
