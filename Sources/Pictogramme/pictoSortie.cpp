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
PictoSortie::PictoSortie( QGraphicsItem* parent,
                          QGraphicsScene* scene ):
     Pictogramme( parent, scene )
{/*{{{*/
     posBottomAnchor_.setX( 25 );
     posBottomAnchor_.setY( 50 );
     posUpAnchor_.setX( 25 );
     posUpAnchor_.setY( 0 );
     pos_ = 50;
}/*}}}*/

PictoSortie::PictoSortie( const QDomElement& node,
                          QGraphicsScene* scene ):
     Pictogramme( 0, scene )
{/*{{{*/
     posBottomAnchor_.setX( 25 );
     posBottomAnchor_.setY( 50 );
     posUpAnchor_.setX( 25 );
     posUpAnchor_.setY( 0 );
     pos_ = 50;
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
     painter->drawRect( 0, 0, 50, 50 );
     painter->drawLine( 15, 5, 15, 27 );
     painter->drawLine( 35, 5, 35, 27 );
     painter->drawLine( 5, 25, 25, 45 );
     painter->drawLine( 25, 45, 45, 25 );
     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoSortie::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, 50, 50 );
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
