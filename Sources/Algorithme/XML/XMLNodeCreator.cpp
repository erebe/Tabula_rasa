#include "XMLNodeCreator.hpp"
#include <QDomElement>

XMLNodeCreator::XMLNodeCreator(QDomDocument & doc) : document(&doc)
{
}


QDomElement XMLNodeCreator::createNode(QString name) {
    return document->createElement(name);
}

QDomElement XMLNodeCreator::createSimpleTextNode(QString name, QString text) {
    QDomElement node = document->createElement(name);
    node.appendChild(document->createTextNode(text));
    return node;
}
