#include "PictoProcedureParser.hpp"
#include "pictoProcedure.hpp"
#include "pictoBuilder.hpp"

PictoProcedureParser::PictoProcedureParser()
{

}

Pictogramme* PictoProcedureParser::parse(const QDomElement & element, Algorithm* algorithm) {
    PictoProcedure * picto = new PictoProcedure(readText(element,"Titre"), readText(element, "PreAssertion"), readText(element, "PostAssertion"));

    QStringList position = readText(element, "Position").split(';');
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
