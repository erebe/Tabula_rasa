#include "pictoCondition.hpp"
#include <QPainter>

PictoCondition::PictoCondition( const QString& label,
                                QGraphicsItem* parent,
                                QGraphicsScene* scene ) :
    Pictogramme( parent, scene )
{
        labels_ << new LabelItem( label, 150, 25, 50, this, scene );
        labels_ << new LabelItem( "Sinon", 150, 25, 50, this, scene );
        posUpAnchor_.setY( 0 );
}

void PictoCondition::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {

        Q_UNUSED( option );
        Q_UNUSED( widget );

        pos_ = 0;

        //On dessine "<"
        painter->drawLine( pos_, 25, 20, 0 );
        painter->drawLine( pos_, 25, 20, 50 );

        labels_.at( 0 )->setPos( 25, 0 );
        pos_ += labels_.at( 0 )->width() + 35;


        //on dessine la barre supérieure
        painter->drawLine( 20, 0, pos_ + 60, 0 );

        //On dessine la barre inférieure
        painter->drawLine( 20, 50, pos_ + 60, 50 );

        //On dessine la barre vecticale
        painter->drawLine( pos_, 0, pos_, 50 );
        posUpAnchor_.setX( pos_ );

        pos_ += 10;
        labels_.at( 1 )->setPos( pos_, 0 );
        pos_ += 50;

        //On dessine ">"
        painter->drawLine( pos_, 0, pos_ + 20, 25 );
        painter->drawLine( pos_, 50, pos_ + 20, 25 );

        pos_ += 20;

        Pictogramme::paint( painter, option, widget );
}

QRectF PictoCondition::boundingRect() const {

        return QRectF( 0, 0, pos_, 50 );
}

QVariant PictoCondition::itemChange( GraphicsItemChange change, const QVariant &value ){


         if ( change == QGraphicsItem::ItemPositionChange ){

                 updateLink();
                 AncreItem* ancre;
                 foreach( ancre, labels_ )
                         ancre->AncreItem::itemChange( change, value );
         }

         return value;
}
