#include "PictoConditionMultipleParser.hpp"
#include "pictoConditionMultiple.hpp"
#include "pictoBuilder.hpp"

PictoConditionMultipleParser::PictoConditionMultipleParser()
{

}

Pictogramme* PictoConditionMultipleParser::parse(const QDomElement & element, Algorithm* algorithm) {
    PictoConditionMultiple *picto = new PictoConditionMultiple();

    QStringList position = readText(element, "Position").split( QRegExp( ";" ) );
    picto->setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

    picto->addLabel(new LabelItem(readText(element, "Titre"), 150, 25, 25, picto));

    const QDomNodeList nodes = element.firstChildElement( "operationsLogiques" ).childNodes();
    Pictogramme* childPicto = 0;

    for( int i = 0; i < nodes.count(); i++ ) {
        QDomNode currentNode = nodes.at(i);
         if(currentNode.isElement()) {
              LabelItem *labelItem = new LabelItem( readText(currentNode, "Titre"), 150, 25, 25, picto );
              labelItem->setAnchorType( AncreItem::Down );


              const QDomNodeList enfants = currentNode.firstChildElement( "Enfants" ).childNodes();

              for( int j = 0; j < enfants.count(); j++ ) {
                   if( enfants.at( j ).isElement() ) {
                        childPicto = PictoBuilder::fromXml( enfants.at( j ).toElement(), algorithm );

                        if( childPicto ) {
                             labelItem->addChild( childPicto );
                             childPicto = 0;
                        }
                   }
              }

              labelItem->setLinkStyle( static_cast<LiaisonItem::Style>( readText(element, "StyleLien").toInt() ) );
              picto->addLabel(labelItem);
         }
    }
    return picto;
}
