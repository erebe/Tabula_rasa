/*
 * =====================================================================================
 *
 *       Filename:  pictoCondition.cpp
 *
 *    Description:  Tabula Rasa : Classe implementant une Condition simle
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:24:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "pictoCondition.hpp"
#include "pictoBuilder.hpp"
#include "algorithmeScene.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoCondition::PictoCondition( const QString& label,
                                QGraphicsItem* parent,
                                QGraphicsScene* scene ) :
     Pictogramme( parent, scene ), isForeverAlone_( false )
{/*{{{*/
     labels_ << new LabelItem( label, 150, 25, 50, this, scene );
     labels_.at( 0 )->setAnchorType( AncreItem::Down );

     labels_ << new LabelItem( "Sinon", 150, 25, 50, this, scene );
     labels_.at( 1 )->setAnchorType( AncreItem::Down );

     setAnchorType( AncreItem::Up );
     posUpAnchor_.setY( 0 );
     updateDimension();

     actions_["SingleOne"] = contexteMenu_.addAction( tr( "Condition unique" ) );
     actions_["SingleOne"]->setCheckable( true );

     actions_["AjouterA"] = contexteMenu_.addAction( tr( "Ajouter une condition" ) );
     actions_["SupprimerA"] = contexteMenu_.addAction( tr( "Supprimer la condition" ) );
}/*}}}*/

PictoCondition::PictoCondition( const QDomElement& node,
                                AlgorithmeScene* scene ):
     Pictogramme( 0, scene )
{/*{{{*/
     QString label = node.firstChildElement( "Position" ).firstChild().toText().data();
     QStringList position = label.split( QRegExp( ";" ) );
     setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

     label = node.firstChildElement( "estUnique" ).firstChild().toText().data();
     isForeverAlone_ = ( label == "1" ) ? true : false;

     setAnchorType( AncreItem::Up );
     posUpAnchor_.setY( 0 );

     actions_["SingleOne"] = contexteMenu_.addAction( tr( "Condition unique" ) );
     actions_["SingleOne"]->setCheckable( true );
     actions_["SingleOne"]->setChecked( isForeverAlone_ );
     actions_["AjouterA"] = contexteMenu_.addAction( tr( "Ajouter une condition" ) );
     actions_["SupprimerA"] = contexteMenu_.addAction( tr( "Supprimer la condition" ) );

     const QDomNodeList nodes = node.firstChildElement( "operationsLogiques" ).childNodes();
     Pictogramme* picto = 0;

     for( int i = 0; i < nodes.count(); i++ ) {
          if( nodes.at( i ).isElement() ) {
               label = nodes.at( i ).firstChildElement( "Titre" ).firstChild().toText().data();
               labels_ << new LabelItem( label, 150, 25, 50, this, scene );
               labels_.last()->setAnchorType( AncreItem::Down );

               const QDomNodeList enfants = nodes.at( i ).firstChildElement( "Enfants" ).childNodes();

               for( int j = 0; j < enfants.count(); j++ ) {
                    if( enfants.at( j ).isElement() ) {
                         picto = PictoBuilder::fromXml( enfants.at( j ).toElement(), scene );

                         if( picto ) {
                              labels_.last()->addChild( picto );
                              picto = 0;
                         }
                    }
               }

               label = node.firstChildElement( "StyleLien" ).firstChild().toText().data();
               labels_.last()->setLinkStyle( static_cast<LiaisonItem::Style>( label.toInt() ) );
          }
     }

     updateDimension();
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void PictoCondition::paint( QPainter* painter,
                            const QStyleOptionGraphicsItem* option,
                            QWidget* widget )
{/*{{{*/
     Q_UNUSED( option );
     Q_UNUSED( widget );
     int pos = 0;
     painter->drawLine( pos, 25, 20, 0 );
     painter->drawLine( pos, 25, 20, 50 );
     pos += labels_.at( 0 )->width() + 35;

     if( !isForeverAlone_ ) {

             for( int i = 1; i< labels_.size(); i++ ) {
                 painter->drawLine( pos, 0, pos, 50 );
                 pos += labels_.at( i )->width() + 15;
                 labels_[i]->setEnabled( true );
                 labels_[i]->setVisible( true );
             }


     } else {
         for( int i = 1; i < labels_.size(); i++ ) {
             labels_[i]->setEnabled( false );
             labels_[i]->setVisible( false );
         }

     }

     painter->drawLine( 20, 0, pos, 0 );
     painter->drawLine( 20, 50, pos, 50 );
     painter->drawLine( pos, 0, pos + 20, 25 );
     painter->drawLine( pos, 50, pos + 20, 25 );
     pos += 20;
     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoCondition::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, pos_, 50 );
}/*}}}*/

void PictoCondition::updateDimension()
{/*{{{*/
     qreal posAncre;
     pos_ = 20;

     if( !isForeverAlone_ ) {

         for( int  i = 0; i < labels_.size(); i++ ) {
              pos_ += 5;
              labels_[i]->setPos( pos_, 0 );
              pos_ += labels_[i]->width() + 10;
         }
     } else {
          pos_ = labels_.at( 0 )->width() + 35;
     }

     pos_ += 20;

     posAncre = ( pos_ / 2 );
     posBottomAnchor_.setX( posAncre );
     posUpAnchor_.setX( posAncre );
     updateLink();

     foreach( AncreItem* item, labels_ )
     item->updateLink();
}/*}}}*/

void PictoCondition::toXml( QDomDocument& doc, QDomNode& node ) const
{/*{{{*/

     QDomElement item = doc.createElement( "Condition" );
     node.appendChild( item );

     QDomElement position = doc.createElement( "Position" );
     position.appendChild( doc.createTextNode( QString( "%1;%2" ).arg( scenePos().x() )
                           .arg( scenePos().y() ) ) );
     item.appendChild( position );

     QDomElement style = doc.createElement( "StyleLien" );
     style.appendChild( doc.createTextNode(
                             ( labels_.last()->hasLink() ) ?
                             QString::number( static_cast<int>( labels_.last()->linkStyle() ) ) :
                             "1" ) ) ;
     item.appendChild( style );

     QDomElement unique = doc.createElement( "estUnique" );
     unique.appendChild( doc.createTextNode( isForeverAlone_ ? "1" : "0" ) );
     item.appendChild( unique );

     QDomElement operations = doc.createElement( "operationsLogiques" );
     item.appendChild( operations );


     foreach( LabelItem * label, labels_ ) {

          QDomElement condition = doc.createElement( "operation" );
          operations.appendChild( condition );

          QDomElement titre = doc.createElement( "Titre" );
          titre.appendChild( doc.createTextNode( label->label() ) );
          condition.appendChild( titre );

          QDomElement enfants = doc.createElement( "Enfants" );
          condition.appendChild( enfants );



          foreach( AncreItem * picto, label->childrenList() ) {
               static_cast<Pictogramme*>( picto )->toXml( doc, enfants );
          }
     }
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Gestionnaire évènements
 *-----------------------------------------------------------------------------*/
QVariant PictoCondition::itemChange( GraphicsItemChange change, const QVariant& value )
{/*{{{*/
     if ( change == QGraphicsItem::ItemPositionChange ) {
          updateLink();
          AncreItem* ancre;
          foreach( ancre, labels_ )
          ancre->AncreItem::itemChange( change, value );
     }

     return value;
}/*}}}*/

void PictoCondition::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     if( action == actions_["SingleOne"] ) {
          isForeverAlone_ = !isForeverAlone_;

          if( isForeverAlone_ ) {
                  for( int i = 1; i < labels_.size(); i++ ) {
                          labels_[i]->detach();
                  }
          }

          prepareGeometryChange();
          updateDimension();

     }else if( actions_["AjouterA"] == action ) {
               LabelItem* item = new LabelItem( "", 150, 25, 50, this, scene() );
               item->setAnchorType( AncreItem::Down );

               labels_.insert( labels_.size() - 1, item );
               prepareGeometryChange();
               updateDimension();

     } else if( actions_["SupprimerA"] == action ) {

               LabelItem* tmp;
               foreach( tmp, labels_ ) {
                    if( ( tmp != labels_.at( 0 ) ) &&
                        tmp->contains( event->pos() - tmp->pos() ) ) {
                         labels_.removeOne( tmp );
                         delete tmp;
                         prepareGeometryChange();
                         updateDimension();
                         break;
                    }
               }

      }else {
          Pictogramme::processAction( action, event );
     }
}/*}}}*/

