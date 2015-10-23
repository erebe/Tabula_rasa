#include "PictoSortieParser.hpp"
#include "pictoSortie.hpp"

PictoSortieParser::PictoSortieParser()
{

}


PictoSortie* PictoSortieParser::parse(const QDomElement &element) {
    PictoSortie * sortie = new PictoSortie();
    QString label = element.firstChildElement( "Position" ).firstChild().toText().data();
    QStringList position = label.split( QRegExp( ";" ) );
    sortie->setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );
    return sortie;
}
