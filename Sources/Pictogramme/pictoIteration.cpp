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
PictoIteration::PictoIteration( QString titre, QGraphicsItem* parent, QGraphicsScene* scene ):
     Pictogramme( parent, scene ), isNumberedLoop_( true )
{/*{{{*/
     labels_ << new LabelItem( titre, 150, 50, 50, this, scene );
     points_[0].setX( 50 );
     points_[0].setY( 10 );
     points_[1].setX( 45 );
     points_[1].setY( 20 );
     points_[2].setX( 60 );
     points_[2].setY( 15 );

     posBottomAnchor_ = QPoint( 27, 55 );
     posUpAnchor_ = QPoint( 27, 0 );
     updateDimension();

     actions_["InfiniteLoop"] = contexteMenu_.addAction( tr( "Iteration non fixe" ) );
     actions_["InfiniteLoop"]->setCheckable( true );
}/*}}}*/

PictoIteration::PictoIteration( const QDomElement& node,
                                AlgorithmeScene* scene ):
     Pictogramme( 0, scene )
{/*{{{*/
     QString label = node.firstChildElement( "Titre" ).firstChild().toText().data();
     labels_ << new LabelItem( label, 150, 50, 50, this, scene );

     label = node.firstChildElement( "Position" ).firstChild().toText().data();
     QStringList position = label.split( QRegExp( ";" ) );
     setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

     label = node.firstChildElement( "IterationFixe" ).firstChild().toText().data();
     isNumberedLoop_ = ( label == "1" ) ? true : false;

     points_[0].setX( 50 );
     points_[0].setY( 10 );
     points_[1].setX( 45 );
     points_[1].setY( 20 );
     points_[2].setX( 60 );
     points_[2].setY( 15 );

     posBottomAnchor_ = QPoint( 27, 55 );
     posUpAnchor_ = QPoint( 27, 0 );
     updateDimension();

     actions_["InfiniteLoop"] = contexteMenu_.addAction( tr( "Iteration non fixe" ) );
     actions_["InfiniteLoop"]->setCheckable( true );
     actions_["InfiniteLoop"]->setChecked( !isNumberedLoop_ );

     const QDomNodeList nodes = node.firstChildElement( "Enfants" ).childNodes();
     Pictogramme* picto = 0;

     for( int i = 0; i < nodes.count(); i++ ) {
          if( nodes.at( i ).isElement() ) {
               picto = PictoBuilder::fromXml( nodes.at( i ).toElement(), scene );

               if( picto ) {
                    picto->AncreItem::setParent( this );
                    picto = 0;
               }
          }
     }
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
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



/*-----------------------------------------------------------------------------
 *  Gestionnaire évènements
 *-----------------------------------------------------------------------------*/
void PictoIteration::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/

     if( action == actions_["InfiniteLoop"] ) {
          isNumberedLoop_ = !isNumberedLoop_;
          prepareGeometryChange();
          updateDimension();

     } else {
          Pictogramme::processAction( action, event );
     }
}/*}}}*/

