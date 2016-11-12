/*
 * =====================================================================================
 *
 *       Filename:  pictoIteration.cpp
 *
 *    Description:  Tabula Rasa : Implémentation d'un item d'iteration
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:37:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "pictoIteration.hpp"
#include "pictoBuilder.hpp"
#include "algorithmeScene.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoIteration::PictoIteration(QString titre):
     Pictogramme(), isNumberedLoop_( true )
{/*{{{*/
     labels_ << new LabelItem( titre, 150, 50, 50, this );

     points_[0].setX( 50 );
     points_[0].setY( 10 );
     points_[1].setX( 45 );
     points_[1].setY( 20 );
     points_[2].setX( 60 );
     points_[2].setY( 15 );

     setAnchorType( AncreItem::Both );
     posBottomAnchor_ = QPoint( 27, 55 );
     posUpAnchor_ = QPoint( 27, 0 );
     updateDimension();

     addContextMenuEntry("InfiniteLoop", "Iteration non fixe", true);
}/*}}}*/

PictoIteration::PictoIteration(const PictoIteration &item):
  Pictogramme(item),
  isNumberedLoop_(item.isNumberedLoop_)
{
    for(unsigned long i = 0; i < sizeof(points_) / sizeof(points_[0]); i++) {
        points_[i] = item.points_[i];
    }
}

/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void PictoIteration::setIsNumberedLoop(bool numbered) {
    isNumberedLoop_ = numbered;
}

void PictoIteration::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{/*{{{*/
     Q_UNUSED( option );
     Q_UNUSED( widget );
     int pos = 55;
     painter->drawEllipse( 0, 0, pos, 55 );
     painter->setBrush( Qt::SolidPattern );
     painter->drawPolygon( points_, 3 );
     painter->setBrush( Qt::NoBrush );

     if( isNumberedLoop_ ) {
          labels_.at( 0 )->setEnabled( true );
          labels_.at( 0 )->setVisible( true );
          labels_.at( 0 )->setPos( pos, 0 );

     } else {
          labels_.at( 0 )->setEnabled( false );
          labels_.at( 0 )->setVisible( false );
     }

     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoIteration::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, pos_ , 55 );
}/*}}}*/

void PictoIteration::updateDimension()
{/*{{{*/
     if( isNumberedLoop_ )
          { pos_ = labels_.at( 0 )->width() + 55; }

     else
          { pos_ = 60; }
}/*}}}*/

void PictoIteration::toXml( QDomDocument& doc, QDomNode& node ) const
{/*{{{*/
     QDomElement item = doc.createElement( "Iteration" );
     node.appendChild( item );
     QDomElement position = doc.createElement( "Position" );
     position.appendChild( doc.createTextNode( QString( "%1;%2" ).arg( scenePos().x() )
                           .arg( scenePos().y() ) ) );
     item.appendChild( position );
     QDomElement style = doc.createElement( "StyleLien" );
     style.appendChild( doc.createTextNode(
                             ( liaison_ ) ?
                             QString::number( static_cast<int>( liaison_->style() ) ) :
                             "1" ) ) ;
     item.appendChild( style );
     QDomElement titre = doc.createElement( "Titre" );
     titre.appendChild( doc.createTextNode( labels_.at( 0 )->label() ) );
     item.appendChild( titre );
     QDomElement loop = doc.createElement( "IterationFixe" );
     loop.appendChild( doc.createTextNode( isNumberedLoop_ ? "1" : "0" ) );
     item.appendChild( loop );
     QDomElement enfants = doc.createElement( "Enfants" );
     item.appendChild( enfants );
     AncreItem* picto;
     foreach( picto, children_ )
     static_cast<Pictogramme*>( picto )->toXml( doc, enfants );
}/*}}}*/

void PictoIteration::createLink()
{/*{{{*/
     AncreItem::createLink();
     liaison_->setStyle( LiaisonItem::Simple );
}/*}}}*/

/*-----------------------------------------------------------------------------
 *  Gestionnaire évènements
 *-----------------------------------------------------------------------------*/
void PictoIteration::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     if( action == getContextMenuAction("InfiniteLoop") ) {
          isNumberedLoop_ = !isNumberedLoop_;
          prepareGeometryChange();
          updateDimension();

     } else {
          Pictogramme::processAction( action, event );
     }
}/*}}}*/

Pictogramme* PictoIteration::clone() {
    return new PictoIteration(*this);
}
