/*
 * =====================================================================================
 *
 *       Filename:  pictoProcedure.cpp
 *
 *    Description:  Tabula Rasa : Implementation d'un appel de procedure
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:40:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "pictoProcedure.hpp"
#include "pictoBuilder.hpp"
#include "algorithmeScene.hpp"
#include <QPainter>


/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoProcedure::PictoProcedure( QString titre,
                                QString preCondition,
                                QString postCondition,
                                QGraphicsItem* parent ) :
     Pictogramme( parent ), detail_( true ), emptyDetail_( true )
{/*{{{*/
     labels_ << new LabelItem( preCondition, 150, 15, 50, this );
     labels_ << new LabelItem( titre, 200, 50, 50, this );
     labels_ << new LabelItem( postCondition, 150, 15, 50, this );

     setAnchorType( AncreItem::Up );
     posBottomAnchor_.setY( 55 );
     posUpAnchor_.setY( 5 );
     updateDimension();

     addContextMenuEntry("Details", "Masquer les assertions", true);
     addContextMenuEntry("EmptyDetails", "Masquer les assertions vides", true);
}/*}}}*/

PictoProcedure::PictoProcedure( const PictoProcedure& item):
    Pictogramme(item),
    detail_(item.detail_), emptyDetail_(item.emptyDetail_)
{}

PictoProcedure::PictoProcedure( const QDomElement& node,
                                AlgorithmeScene* scene ):
     Pictogramme( 0 )
{/*{{{*/
     QString label = node.firstChildElement( "PreAssertion" ).firstChild().toText().data();
     labels_ << new LabelItem( label, 150, 15, 50, this );

     label = node.firstChildElement( "Titre" ).firstChild().toText().data();
     labels_ << new LabelItem( label, 200, 50, 50, this );

     label = node.firstChildElement( "PostAssertion" ).firstChild().toText().data();
     labels_ << new LabelItem( label, 150, 15, 50, this );

     label = node.firstChildElement( "Position" ).firstChild().toText().data();
     QStringList position = label.split( ';' );
     setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

     label = node.firstChildElement( "DetailsVisible" ).firstChild().toText().data();
     detail_ = ( label == "1" ) ? true : false;

     label = node.firstChildElement( "DetailsVideVisible" ).firstChild().toText().data();
     emptyDetail_ = ( label == "1" ) ? true : false;

     setAnchorType( AncreItem::Up );
     posBottomAnchor_.setY( 55 );
     posUpAnchor_.setY( 5 );
     updateDimension();


     addContextMenuEntry("Details", "Masquer les assertions", true, !detail_);
     addContextMenuEntry("EmptyDetails", "Masquer les assertions vides", true, !emptyDetail_);

     const QDomNodeList nodes = node.firstChildElement( "Enfants" ).childNodes();
     Pictogramme* picto = 0;

     for( int i = 0; i < nodes.count(); i++ ) {
          if( nodes.at( i ).isElement() ) {
               picto = PictoBuilder::fromXml( nodes.at( i ).toElement(), scene );

               if( picto ) {
                    addChild( picto );
                    picto = 0;
               }
          }
     }

     label = node.firstChildElement( "StyleLien" ).firstChild().toText().data();
     setLinkStyle( static_cast<LiaisonItem::Style>( label.toInt() ) );
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void PictoProcedure::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{/*{{{*/
     Q_UNUSED( option );
     Q_UNUSED( widget );
     int pos = drawDetails( painter, labels_.at( 0 ), 5 );
     painter->drawRect( pos, 5,
                        labels_.at( 1 )->width() + 20, 50 );
     pos += 10;
     painter->drawLine( pos, 5,
                        pos, 55 );
     painter->drawLine( pos + labels_.at( 1 )->width(), 5,
                        pos + labels_.at( 1 )->width(), 55 );
     labels_.at( 1 )->setPos( pos, 5 );
     pos += labels_.at( 1 )->width() + 25;
     pos = drawDetails( painter, labels_.at( 2 ), pos );
     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoProcedure::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, pos_, 60 );
}/*}}}*/

void PictoProcedure::updateDimension()
{/*{{{*/
     qreal posAncre;
     pos_ = labels_.at( 1 )->width() + 30;

     if( detail() ) {
          posAncre = ( labels_.at( 1 )->width() / 2 ) + 15;

          if( emptyDetail_ ||
              ( !emptyDetail_ && !labels_.at( 0 )->isEmpty() ) ) {
               pos_ += labels_.at( 0 )->width() + 45;
               posAncre =  labels_.at( 0 )->width() + 60
                           + ( labels_.at( 1 )->width() / 2 );
          }

          if( emptyDetail_ ||
              ( !emptyDetail_ && !labels_.at( 2 )->isEmpty() ) ) {
               pos_ += labels_.at( 2 )->width() + 45;
          }

     } else {
          posAncre = ( labels_.at( 1 )->width() / 2 ) + 15;
     }

     posBottomAnchor_.setX( posAncre );
     posUpAnchor_.setX( posAncre );
     updateLink();
}/*}}}*/

void PictoProcedure::toXml( QDomDocument& doc, QDomNode& node ) const
{/*{{{*/
     QDomElement item = doc.createElement( "Procedure" );
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
     QDomElement preAssertion = doc.createElement( "PreAssertion" );
     preAssertion.appendChild( doc.createTextNode( labels_.at( 0 )->label() ) );
     item.appendChild( preAssertion );
     QDomElement postAssertion = doc.createElement( "PostAssertion" );
     postAssertion.appendChild( doc.createTextNode( labels_.at( 2 )->label() ) );
     item.appendChild( postAssertion );
     QDomElement titre = doc.createElement( "Titre" );
     titre.appendChild( doc.createTextNode( labels_.at( 1 )->label() ) );
     item.appendChild( titre );
     QDomElement details = doc.createElement( "DetailsVisible" );
     details.appendChild( doc.createTextNode( detail_ ? "1" : "0" ) );
     item.appendChild( details );
     QDomElement detailsVide = doc.createElement( "DetailsVideVisible" );
     detailsVide.appendChild( doc.createTextNode( emptyDetail_ ? "1" : "0" ) );
     item.appendChild( detailsVide );
     QDomElement enfants = doc.createElement( "Enfants" );
     item.appendChild( enfants );
     AncreItem* picto;
     foreach( picto, children_ )
     static_cast<Pictogramme*>( picto )->toXml( doc, enfants );
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes privées
 *-----------------------------------------------------------------------------*/
int PictoProcedure::drawDetails( QPainter* painter, LabelItem* texte, int pos ) const
{/*{{{*/
     if( detail() &&
         ( emptyDetail_ || ( !emptyDetail_ && !texte->isEmpty() ) ) ) {
          painter->drawArc( pos, 5, 10, 25, 90 * 16, 179 * 16 );
          painter->drawArc( pos - 6, 30, 15, 2, 90 * 16, 180 * 16 );
          painter->drawArc( pos, 32, 10, 25, 90 * 16, 179 * 16 );
          pos += 15;
          texte->setPos( pos, 4 );
          texte->setEnabled( true );
          texte->setVisible( true );
          pos += texte->width() + 5;
          painter->drawArc( pos, 5, 10, 25, 90 * 16, -179 * 16 );
          painter->drawArc( pos + 1, 30, 15, 2, 90 * 16, -180 * 16 );
          painter->drawArc( pos, 32, 10, 25, 90 * 16, -179 * 16 );
          pos += 25;

     } else {
          texte->setEnabled( false );
          texte->setVisible( false );
     }

     return pos;
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Gestionnaire d'évènements
 *-----------------------------------------------------------------------------*/
void PictoProcedure::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     if( action == getContextMenuAction("Details") ) {
          detail_ = !detail_;
          prepareGeometryChange();
          updateDimension();

     } else if ( action == getContextMenuAction("EmptyDetails") ) {
          emptyDetail_ = !emptyDetail_;
          prepareGeometryChange();
          updateDimension();

     } else {
          Pictogramme::processAction( action, event );
     }
}/*}}}*/

Pictogramme* PictoProcedure::clone() {
    return new PictoProcedure(*this);
}
