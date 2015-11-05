#include "PictoIterationParser.hpp"
#include "pictoIteration.hpp"
#include "pictoBuilder.hpp"

PictoIterationParser::PictoIterationParser()
{

}

Pictogramme* PictoIterationParser::parse(const QDomElement & element, AlgorithmeScene* scene) {
    PictoIteration * picto = new PictoIteration(readText(element, "Titre"));

    QStringList position = readText(element, "Position").split( QRegExp( ";" ) );
    picto->setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

    picto->setIsNumberedLoop(readText(element, "IterationFixe") == "1");

    const QDomNodeList nodes = element.firstChildElement( "Enfants" ).childNodes();
    Pictogramme* childPicto = 0;

    for( int i = 0; i < nodes.count(); i++ ) {
         if( nodes.at( i ).isElement() ) {
              childPicto = PictoBuilder::fromXml( nodes.at( i ).toElement(), scene );

              if( childPicto ) {
                   picto->addChild( childPicto );
                   childPicto = 0;
              }
         }
    }

    picto->setLinkStyle( static_cast<LiaisonItem::Style>( readText(element, "StyleLien").toInt() ) );
    return picto;
}
