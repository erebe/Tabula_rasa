#include "DictionaryEntryParser.hpp"
#include "DictionaryEntryAttributes.hpp"
#include "Model/DictionaryEntry.hpp"
#include <QDomElement>

DictionaryEntryParser::DictionaryEntryParser()
{

}

DictionaryEntry *DictionaryEntryParser::parse(const QDomElement &entryNode) {
    DictionaryEntry *entry = new DictionaryEntry();

    entry->setName(readText(entryNode, DictionaryEntryAttributes::NAME_ATTRIBUTE));
    entry->setType(readText(entryNode, DictionaryEntryAttributes::TYPE_ATTRIBUTE));
    entry->setSignification(readText(entryNode, DictionaryEntryAttributes::SIGNIFICATION_ATTRIBUTE));
    return entry;
}

QString DictionaryEntryParser::readText(const QDomNode & node, const QString name) {
    return node.firstChildElement(name).firstChild().toText().data();
}
