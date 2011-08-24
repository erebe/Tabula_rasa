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
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

PictoIteration::PictoIteration( QString titre, QGraphicsItem* parent, QGraphicsScene* scene ):
    Pictogramme( parent, scene ), isNumberedLoop_( true )
{
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
}


void PictoIteration::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{

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
}

QRectF PictoIteration::boundingRect() const
{

     return QRectF( 0, 0, pos_ , 55 );
}

void PictoIteration::updateDimension()
{

    if( isNumberedLoop_ )
        pos_ = labels_.at( 0 )->width() + 55;
    else
        pos_ = 60;
}

void PictoIteration::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event ){

    if( action == actions_["InfiniteLoop"] ) {
         isNumberedLoop_ = !isNumberedLoop_;
         prepareGeometryChange();
         updateDimension();
    } else {
              Pictogramme::processAction( action, event );
   }
}
