#include "PictoParser.hpp"
#include <QDomElement>

PictoParser::PictoParser()
{

}

QString PictoParser::readText(const QDomNode & node, const QString name) {
    return node.firstChildElement(name).firstChild().toText().data();
}

PictoParser::~PictoParser()
{

}
