#include "pictoConditionMultiple.hpp"
#include "pictoBuilder.hpp"
#include "algorithmeScene.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>



/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoConditionMultiple::PictoConditionMultiple() {
    setAnchorType( AncreItem::Up );
    posUpAnchor_.setY( 0 );

    addContextMenuEntry("AjouterA", "Ajouter une condition");
    addContextMenuEntry("SupprimerA", "Supprimer la condition");
}

PictoConditionMultiple::PictoConditionMultiple(const QString& label) :
     Pictogramme()
{/*{{{*/
     labels_ << new LabelItem( label, 150, 25, 25, this );
     labels_.last()->setAnchorType( AncreItem::Down );

     labels_ << new LabelItem( label, 150, 25, 25, this );
     labels_.last()->setAnchorType( AncreItem::Down );

     labels_ << new LabelItem( "Sinon", 150, 25, 25, this );
     labels_.last()->setAnchorType( AncreItem::Down );

     setAnchorType( AncreItem::Up );
     posUpAnchor_.setY( 0 );
     updateDimension();

     addContextMenuEntry("AjouterA", "Ajouter une condition");
     addContextMenuEntry("SupprimerA", "Supprimer la condition");
}/*}}}*/

PictoConditionMultiple::PictoConditionMultiple( const PictoConditionMultiple& item):
  Pictogramme(item)
{}

/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void PictoConditionMultiple::addLabel(LabelItem *item) {
    labels_ << item;
    updateDimension();
}

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
     if( getContextMenuAction("AjouterA") == action ) {
          LabelItem* item = new LabelItem( "", 150, 25, 25, this );
          item->setAnchorType( AncreItem::Down );

          labels_.insert( labels_.size() - 1, item );
          prepareGeometryChange();
          updateDimension();

     } else if( getContextMenuAction("SupprimerA") == action ) {

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

Pictogramme* PictoConditionMultiple::clone() {
    return new PictoConditionMultiple(*this);
}
