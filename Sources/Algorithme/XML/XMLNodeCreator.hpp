#ifndef XMLNODECREATOR_H
#define XMLNODECREATOR_H

class QDomDocument;
class QDomElement;
class QString;

class XMLNodeCreator
{
public:
    XMLNodeCreator(QDomDocument & doc);
    QDomElement createNode(QString name);
    QDomElement createSimpleTextNode(QString name, QString text);
private:
    QDomDocument *document;
};

#endif // XMLNODECREATOR_H
