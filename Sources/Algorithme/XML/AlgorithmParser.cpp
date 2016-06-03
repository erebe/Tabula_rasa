#include "AlgorithmParser.hpp"
#include "Model/Algorithm.hpp"
#include "pictoBuilder.hpp"
#include "XML/DictionaryParser.hpp"

AlgorithmParser::AlgorithmParser()
{

}

Algorithm* AlgorithmParser::parse(const QDomElement & element)
{
    DictionaryParser dictionaryParser;
    Algorithm *algorithm = new Algorithm(element.firstChildElement("nom").firstChild().toText().data(), dictionaryParser.parse(element));

    const QDomNodeList nodes = element.firstChildElement("Elements").childNodes();

    for (int i = 0; i < nodes.count(); i++) {
        if (nodes.at(i).isElement()) {
            PictoBuilder::fromXml(nodes.at(i).toElement(), algorithm);
        }
    }

    return algorithm;
}
