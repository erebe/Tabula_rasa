#include "PictoSortieParser.hpp"
#include "pictoSortie.hpp"

PictoSortieParser::PictoSortieParser()
{

}

Pictogramme* PictoSortieParser::parse(const QDomElement &element, AlgorithmeScene *scene) {
    PictoSortie * sortie = new PictoSortie();
    QStringList position = readText(element, "Position").split( QRegExp( ";" ) );
    sortie->setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );
    return sortie;
}
