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

    actions_["AjouterA"] = contexteMenu_.addAction( tr("Ajouter une condition") );
    actions_["SupprimerA"] = contexteMenu_.addAction( tr("Supprimer la condition") );
}


void PictoConditionMultiple::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {

        Q_UNUSED( option );
        Q_UNUSED( widget );

        pos_ = 0;

        //On dessine "<"
        painter->drawLine( pos_, 25, 20, 0 );
        painter->drawLine( pos_, 25, 20, 50 );

        pos_ += 20;


        if( labels_.size() > 1 ){
                int i;
                for( i = 1; i < labels_.size() - 1; i++ ){

                        pos_ += 5;
                        labels_[i]->setPos( pos_, 25 );
                        pos_ += labels_[i]->width() + 5;
                        painter->drawLine( pos_, 25, pos_, 50 );
                }

                pos_ += 5;
                labels_[i]->setPos( pos_, 25 );
                pos_ += labels_[i]->width() + 5;


        }

        if( pos_ < labels_.at( 0 )->width() + 25 )
                pos_ = labels_.at( 0 )->width() + 25;

        labels_[0]->setPos( (pos_ - labels_[0]->width() + 20 ) / 2, 0 );



        //On dessine ">"
        painter->drawLine( pos_, 0, pos_ + 20, 25 );
        painter->drawLine( pos_, 50, pos_ + 20, 25 );
        painter->drawLine( 20, 0, pos_, 0 );
        painter->drawLine( 20, 50, pos_ , 50 );

        pos_ += 20;
        painter->drawLine( 0, 25, pos_, 25 );
        posUpAnchor_.setX( pos_ / 2 );



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

                prepareGeometryChange();
                pos_ += 50;
                labels_.insert( labels_.size() - 1, new LabelItem( "", 150, 25, 25, this, scene() ) );

        }else if( actions_["SupprimerA"] == action){

                LabelItem* tmp;

                foreach( tmp, labels_ ){
                         if( ( tmp != labels_.at(0) ) &&
                               tmp->contains( event->pos() - tmp->pos() ) ){
                                 prepareGeometryChange();
                                 labels_.removeOne( tmp );
                                 delete tmp;
                                 break;
                         }
                }

        }else{
                Pictogramme::processAction( action, event );
        }
}
