#include "pictoSortie.hpp"
#include <QPainter>

PictoSortie::PictoSortie( QGraphicsItem* parent,
                          QGraphicsScene* scene ):
        Pictogramme( parent, scene )
{
        posBottomAnchor_.setX( 25 );
        posBottomAnchor_.setY( 50 );
        posUpAnchor_.setX( 25 );
        posUpAnchor_.setY( 0 );
}


void PictoSortie::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ){

        Q_UNUSED( option );
        Q_UNUSED( widget );

        painter->drawRect( 0, 0, 50, 50 );
        painter->drawLine( 15, 5, 15, 27 );
        painter->drawLine( 35, 5, 35, 27 );
        painter->drawLine( 5, 25, 25, 45 );
        painter->drawLine( 25, 45, 45, 25 );


        Pictogramme::paint( painter, option, widget );

}

QRectF PictoSortie::boundingRect() const {


        return QRectF( 0, 0, 50, 50 );
}

void PictoSortie::updateDimension() {


}
