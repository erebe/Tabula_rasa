/*
 * =====================================================================================
 *
 *       Filename:  pictoSortie.cpp
 *
 *    Description:  Tabula Rasa : Implémentation d'une sortie
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:42:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "pictoSortie.hpp"
#include <QPainter>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoSortie::PictoSortie( QGraphicsItem* parent):
     Pictogramme( parent )
{/*{{{*/
     posUpAnchor_.setX( 20 );
     posUpAnchor_.setY( 0 );
     pos_ = 40;
     setAnchorType( AncreItem::Up );
}/*}}}*/

PictoSortie::PictoSortie(const PictoSortie &item):
  Pictogramme(item)
{}

PictoSortie::PictoSortie( const QDomElement& node):
     Pictogramme( 0 )
{/*{{{*/
     setAnchorType( AncreItem::Up );
     posUpAnchor_.setX( 20 );
     posUpAnchor_.setY( 0 );

     pos_ = 40;

     QString label = node.firstChildElement( "Position" ).firstChild().toText().data();
     QStringList position = label.split( QRegExp( ";" ) );
     setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void PictoSortie::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{/*{{{*/
     Q_UNUSED( option );
     Q_UNUSED( widget );

     painter->drawRect( 0, 0, 40, 40 );
     painter->drawLine( 12, 5, 12, 20 );
     painter->drawLine( 28, 5, 28, 20 );
     painter->drawLine( 5, 20, 20, 35 );
     painter->drawLine( 20, 35, 35, 20 );

     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoSortie::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, 40, 40 );
}/*}}}*/

void PictoSortie::toXml( QDomDocument& doc, QDomNode& node ) const
{/*{{{*/
     QDomElement item = doc.createElement( "Sortie" );
     node.appendChild( item );

     QDomElement position = doc.createElement( "Position" );
     position.appendChild( doc.createTextNode( QString( "%1;%2" ).arg( scenePos().x() )
                           .arg( scenePos().y() ) ) );

     item.appendChild( position );
}/*}}}*/

void PictoSortie::updateDimension()
{}

Pictogramme* PictoSortie::clone() {
    return new PictoSortie(*this);
}
