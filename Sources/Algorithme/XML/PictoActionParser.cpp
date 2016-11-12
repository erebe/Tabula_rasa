#include "PictoActionParser.hpp"
#include "pictoAction.hpp"
#include "pictoBuilder.hpp"

PictoActionParser::PictoActionParser()
{

}

Pictogramme* PictoActionParser::parse(const QDomElement & element, Algorithm* algorithm) {
    PictoAction *picto = new PictoAction(readText(element, "Titre"), readText(element, "PreAssertion"), readText(element, "PostAssertion"));

    QStringList position = readText(element, "Position").split( QRegExp( ";" ) );
    picto->setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

    picto->setDetailsVisible(readText(element, "DetailsVisible") == "1");
    picto->setEmptyDetailsVisible(readText(element, "DetailsVideVisible") == "1");

    const QDomNodeList nodes = element.firstChildElement( "Enfants" ).childNodes();
    Pictogramme* childPicto = 0;

    for( int i = 0; i < nodes.count(); i++ ) {
         if( nodes.at( i ).isElement() ) {
              childPicto = PictoBuilder::fromXml( nodes.at( i ).toElement(), algorithm );

              if( childPicto ) {
                   picto->addChild( childPicto );
                   childPicto = 0;
              }
         }
    }

    picto->setLinkStyle( static_cast<LiaisonItem::Style>( readText(element, "StyleLien").toInt() ) );
    return picto;
}
