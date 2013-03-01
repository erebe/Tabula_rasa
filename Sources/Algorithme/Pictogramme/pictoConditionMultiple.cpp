#include "pictoConditionMultiple.hpp"
#include "pictoBuilder.hpp"
#include "algorithmeScene.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>



/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoConditionMultiple::PictoConditionMultiple( const QString& label,
          QGraphicsItem* parent,
          QGraphicsScene* scene ) :
     Pictogramme( parent, scene )
{/*{{{*/
     labels_ << new LabelItem( label, 150, 25, 25, this, scene );
     labels_.last()->setAnchorType( AncreItem::Down );

     labels_ << new LabelItem( label, 150, 25, 25, this, scene );
     labels_.last()->setAnchorType( AncreItem::Down );

     labels_ << new LabelItem( "Sinon", 150, 25, 25, this, scene );
     labels_.last()->setAnchorType( AncreItem::Down );

     setAnchorType( AncreItem::Up );
     posUpAnchor_.setY( 0 );
     updateDimension();

     actions_["AjouterA"] = contexteMenu_.addAction( tr( "Ajouter une condition" ) );
     actions_["SupprimerA"] = contexteMenu_.addAction( tr( "Supprimer la condition" ) );
}/*}}}*/

PictoConditionMultiple::PictoConditionMultiple( const QDomElement& node,
          AlgorithmeScene* scene ):
     Pictogramme( 0, scene )
{/*{{{*/
     QString label = node.firstChildElement( "Position" ).firstChild().toText().data();
     QStringList position = label.split( QRegExp( ";" ) );
     setPos( position.at( 0 ).toDouble(), position.at( 1 ).toDouble() );

     label = node.firstChildElement( "Titre" ).firstChild().toText().data();
     labels_ << new LabelItem( label, 150, 25, 25, this, scene );

     setAnchorType( AncreItem::Up );
     posUpAnchor_.setY( 0 );

     actions_["AjouterA"] = contexteMenu_.addAction( tr( "Ajouter une condition" ) );
     actions_["SupprimerA"] = contexteMenu_.addAction( tr( "Supprimer la condition" ) );

     const QDomNodeList nodes = node.firstChildElement( "operationsLogiques" ).childNodes();
     Pictogramme* picto = 0;

     for( int i = 0; i < nodes.count(); i++ ) {
          if( nodes.at( i ).isElement() ) {
               label = nodes.at( i ).firstChildElement( "Titre" ).firstChild().toText().data();
               labels_ << new LabelItem( label, 150, 25, 25, this, scene );
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
void PictoConditionMultiple::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{/*{{{*/
     Q_UNUSED( option );
     Q_UNUSED( widget );
     unsigned int pos = 0;
     painter->drawLine( pos, 25, 20, 0 );
     painter->drawLine( pos, 25, 20, 50 );
     pos += 20;

     if( labels_.size() > 1 ) {
          int i;

          for( i = 1; i < labels_.size() - 1; i++ ) {
               pos += labels_[i]->width() + 10;
               painter->drawLine( pos, 25, pos, 50 );
          }

          pos += labels_[i]->width() + 10;
     }

     if( pos < labels_.at( 0 )->width() + 40 ) {
          pos = labels_.at( 0 )->width() + 40;
     }

     painter->drawLine( pos, 0, pos + 20, 25 );
     painter->drawLine( pos, 50, pos + 20, 25 );
     painter->drawLine( 20, 0, pos, 0 );
     painter->drawLine( 20, 50, pos , 50 );
     pos += 20;
     painter->drawLine( 0, 25, pos, 25 );
     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoConditionMultiple::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, pos_, 50 );
}/*}}}*/

void PictoConditionMultiple::updateDimension()
{/*{{{*/
     qreal posAncre;
     pos_ = 20;

     for( int  i = 1; i < labels_.size(); i++ ) {
          pos_ += 5;
          labels_[i]->setPos( pos_, 25 );
          pos_ += labels_[i]->width() + 5;
     }

     if( pos_ < labels_.at( 0 )->width() + 40 ) {
          pos_ = labels_.at( 0 )->width() + 40;
     }

     labels_[0]->setPos( ( pos_ - labels_[0]->width() + 20 ) / 2, 0 );
     pos_ += 20;
     posAncre = pos_ / 2;
     posBottomAnchor_.setX( posAncre );
     posUpAnchor_.setX( posAncre );
     updateLink();
     AncreItem* item;
     foreach( item, labels_ )
     item->updateLink();
}/*}}}*/

void PictoConditionMultiple::toXml( QDomDocument& doc, QDomNode& node ) const
{/*{{{*/
     QDomElement item = doc.createElement( "ConditionMultiple" );
     node.appendChild( item )
     ;
     QDomElement position = doc.createElement( "Position" );
     position.appendChild( doc.createTextNode( QString( "%1;%2" ).arg( scenePos().x() )
                           .arg( scenePos().y() ) ) );
     item.appendChild( position );

     QDomElement style = doc.createElement( "StyleLien" );
     style.appendChild( doc.createTextNode(QString::number( static_cast<int>(linkStyle()))));
     item.appendChild( style );

     QDomElement titre = doc.createElement( "Titre" );
     titre.appendChild( doc.createTextNode( labels_.at( 0 )->label() ) );
     item.appendChild( titre );

     QDomElement operations = doc.createElement( "operationsLogiques" );
     item.appendChild( operations );

     for( QList<LabelItem*>::const_iterator label = labels_.constBegin() + 1; label != labels_.constEnd(); label++ ) {

          QDomElement condition = doc.createElement( "operation" );
          operations.appendChild( condition );

          QDomElement titre = doc.createElement( "Titre" );
          titre.appendChild( doc.createTextNode( ( *label )->label() ) );
          condition.appendChild( titre );

          QDomElement enfants = doc.createElement( "Enfants" );
          condition.appendChild( enfants );


          foreach( AncreItem * picto, ( *label )->childrenList() ) {
               static_cast<Pictogramme*>( picto )->toXml( doc, enfants );
          }
     }
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Gestionnaire d'évènements
 *-----------------------------------------------------------------------------*/
QVariant PictoConditionMultiple::itemChange( GraphicsItemChange change, const QVariant& value )
{/*{{{*/
     if ( change == QGraphicsItem::ItemPositionChange ) {
          updateLink();
          AncreItem* ancre;
          foreach( ancre, labels_ )
          ancre->AncreItem::itemChange( change, value );
     }

     return value;
}/*}}}*/

void PictoConditionMultiple::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     if( actions_["AjouterA"] == action ) {
          LabelItem* item = new LabelItem( "", 150, 25, 25, this, scene() );
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

     } else {
          Pictogramme::processAction( action, event );
     }
}/*}}}*/


LiaisonItem::Style PictoConditionMultiple::linkStyle() const
{
    LiaisonItem::Style style = LiaisonItem::Linear;

    for(int i = 1; i < labels_.size(); ++i) {
        if( labels_[i]->hasLink())
            style = labels_[i]->linkStyle();
    }

    return style;
}

