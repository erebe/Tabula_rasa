#include "DictionaryParser.hpp"
#include "Model/Dictionary.hpp"

DictionaryParser::DictionaryParser()
{

}

Dictionary* DictionaryParser::parse(const QDomElement & element) {
    Dictionary *dictionary = new Dictionary();
    QDomElement dictionaryElement = element.firstChildElement("Dictionary");
    // for backward compatibility, we authorize not having a <Dictionary> tag
    if (!dictionaryElement.isNull()) {
        const QDomNodeList nodes = dictionaryElement.childNodes();
        for (int i = 0; i < nodes.count(); i++) {
            QDomNode node = nodes.at(i);
            if (node.isElement()) {
                dictionary->addEntry(*entryParser.parse(node.toElement()));
            }
        }
    }
    return dictionary;
}
