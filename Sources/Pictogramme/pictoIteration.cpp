#include "pictoIteration.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

PictoIteration::PictoIteration( QString titre, QGraphicsItem* parent, QGraphicsScene* scene ):
    Pictogramme( parent, scene )
{
        labels_ << new LabelItem( titre, 150, 50, 50, this, scene );
        points_[0].setX( 50 ); points_[0].setY( 10 );
        points_[1].setX( 45 ); points_[1].setY( 20 );
        points_[2].setX( 60 ); points_[2].setY( 15 );

        posBottomAnchor_ = QPoint( 27, 55 );
        posUpAnchor_ = QPoint( 27, 0 );
}


void PictoIteration::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ){

        Q_UNUSED( option );
        Q_UNUSED( widget );

        pos_ = 55;

        painter->drawEllipse( 0, 0, pos_, 55 );
        painter->setBrush( Qt::SolidPattern );
        painter->drawPolygon( points_, 3 );
        painter->setBrush( Qt::NoBrush );


        labels_.at( 0 )->setPos( pos_, 0 );
        pos_ += labels_.at( 0 )->width();


        Pictogramme::paint( painter, option, widget );
}

QRectF PictoIteration::boundingRect() const {

        return QRectF( 0, 0, pos_ , 55 );
}

