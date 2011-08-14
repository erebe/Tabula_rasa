#include "pictoConditionMultiple.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


PictoConditionMultiple::PictoConditionMultiple( const QString& label,
                                                QGraphicsItem* parent,
                                                QGraphicsScene* scene ) :
Pictogramme( parent, scene )
{
    labels_ << new LabelItem( label, 150, 25, 25, this, scene );
    labels_ << new LabelItem( label, 150, 25, 25, this, scene );
    labels_ << new LabelItem( "Sinon", 150, 25, 25, this, scene );
    posUpAnchor_.setY( 0 );

    updateDimension();

    actions_["AjouterA"] = contexteMenu_.addAction( tr("Ajouter une condition") );
    actions_["SupprimerA"] = contexteMenu_.addAction( tr("Supprimer la condition") );
}


void PictoConditionMultiple::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {

        Q_UNUSED( option );
        Q_UNUSED( widget );

        int pos = 0;

        //On dessine "<"
        painter->drawLine( pos, 25, 20, 0 );
        painter->drawLine( pos, 25, 20, 50 );

        pos += 20;


        if( labels_.size() > 1 ){
                int i;
                for( i = 1; i < labels_.size() - 1; i++ ){

                        pos += 5;
                        labels_[i]->setPos( pos, 25 );
                        pos += labels_[i]->width() + 5;
                        painter->drawLine( pos, 25, pos, 50 );
                }

                pos += 5;
                labels_[i]->setPos( pos, 25 );
                pos += labels_[i]->width() + 5;


        }

        if( pos < labels_.at( 0 )->width() + 40 )
               pos = labels_.at( 0 )->width() + 40;

        labels_[0]->setPos( (pos - labels_[0]->width() + 20 ) / 2, 0 );



        //On dessine ">"
        painter->drawLine( pos, 0, pos + 20, 25 );
        painter->drawLine( pos, 50, pos + 20, 25 );
        painter->drawLine( 20, 0, pos, 0 );
        painter->drawLine( 20, 50, pos , 50 );

        pos += 20;
        painter->drawLine( 0, 25, pos, 25 );

        Pictogramme::paint( painter, option, widget );
}

QRectF PictoConditionMultiple::boundingRect() const {

        return QRectF( 0, 0, pos_, 50 );
}

QVariant PictoConditionMultiple::itemChange( GraphicsItemChange change, const QVariant &value ){


         if ( change == QGraphicsItem::ItemPositionChange ){

                 updateLink();
                 AncreItem* ancre;
                 foreach( ancre, labels_ )
                         ancre->AncreItem::itemChange( change, value );
         }

         return value;
}

void PictoConditionMultiple::processAction( QAction* action, QGraphicsSceneContextMenuEvent *event ){

        if( actions_["AjouterA"] == action ){

                labels_.insert( labels_.size() - 1, new LabelItem( "", 150, 25, 25, this, scene() ) );
                prepareGeometryChange();
                updateDimension();

        }else if( actions_["SupprimerA"] == action){

                LabelItem* tmp;

                foreach( tmp, labels_ ){
                         if( ( tmp != labels_.at(0) ) &&
                               tmp->contains( event->pos() - tmp->pos() ) ){
                                 labels_.removeOne( tmp );
                                 delete tmp;
                                 prepareGeometryChange();
                                 updateDimension();
                                 break;
                         }
                }

        }else{
                Pictogramme::processAction( action, event );
        }
}


void PictoConditionMultiple::updateDimension() {

    qreal posAncre;
    pos_ = 40;

    for( int i = 1; i < labels_.size(); i++ ){
           pos_ += labels_.at( i )->width() + 10;
    }

    if( pos_ < labels_.at( 0 )->width() + 60 )
           pos_ = labels_.at( 0 )->width() + 60;

    posAncre = ( pos_ / 2 );

    posBottomAnchor_.setX( posAncre );
    posUpAnchor_.setX( posAncre );
    updateLink();

    AncreItem* item;

    foreach( item, labels_ )
            item->updateLink();

}
