#include "DictionaryEntryWriter.hpp"
#include "DictionaryEntryAttributes.hpp"
#include "XML/XMLNodeCreator.hpp"
#include <QDomElement>
#include "Model/DictionaryEntry.hpp"

DictionaryEntryWriter::DictionaryEntryWriter(XMLNodeCreator &creator) : nodeCreator(&creator)
{

}

QDomElement DictionaryEntryWriter::write(const DictionaryEntry &entry) {
    QDomElement entryNode = nodeCreator->createNode(DictionaryEntryAttributes::ENTRY_TAG);
    entryNode.appendChild(nodeCreator->createSimpleTextNode(DictionaryEntryAttributes::NAME_ATTRIBUTE, entry.name()));
    entryNode.appendChild(nodeCreator->createSimpleTextNode(DictionaryEntryAttributes::TYPE_ATTRIBUTE, entry.type()));
    entryNode.appendChild(nodeCreator->createSimpleTextNode(DictionaryEntryAttributes::SIGNIFICATION_ATTRIBUTE, entry.signification()));
    return entryNode;
}
