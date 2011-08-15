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
#include <QPainter>

PictoCondition::PictoCondition( const QString& label,
                                QGraphicsItem* parent,
                                QGraphicsScene* scene ) :
     Pictogramme( parent, scene )
{
     labels_ << new LabelItem( label, 150, 25, 50, this, scene );
     labels_ << new LabelItem( "Sinon", 150, 25, 50, this, scene );
     posUpAnchor_.setY( 0 );
     updateDimension();
}

void PictoCondition::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{

     Q_UNUSED( option );
     Q_UNUSED( widget );

     int pos = 0;

     //On dessine "<"
     painter->drawLine( pos, 25, 20, 0 );
     painter->drawLine( pos, 25, 20, 50 );

     labels_.at( 0 )->setPos( 25, 0 );
     pos += labels_.at( 0 )->width() + 35;


     //On dessine la barre vecticale
     painter->drawLine( pos, 0, pos, 50 );

     labels_.at( 1 )->setPos( pos + 10, 0 );
     pos += labels_.at( 1 )->width() + 10;

     //on dessine la barre supérieure
     painter->drawLine( 20, 0, pos, 0 );

     //On dessine la barre inférieure
     painter->drawLine( 20, 50, pos, 50 );

     //On dessine ">"
     painter->drawLine( pos, 0, pos + 20, 25 );
     painter->drawLine( pos, 50, pos + 20, 25 );

     pos += 20;

     Pictogramme::paint( painter, option, widget );
}

QRectF PictoCondition::boundingRect() const
{

     return QRectF( 0, 0, pos_, 50 );
}

QVariant PictoCondition::itemChange( GraphicsItemChange change, const QVariant& value )
{


     if ( change == QGraphicsItem::ItemPositionChange ) {

          updateLink();
          AncreItem* ancre;
          foreach( ancre, labels_ )
          ancre->AncreItem::itemChange( change, value );
     }

     return value;
}


void PictoCondition::updateDimension()
{

     qreal posAncre;
     pos_ = labels_.at( 1 )->width()
            + labels_.at( 0 )->width() + 65;

     posAncre = ( pos_ / 2 );

     posBottomAnchor_.setX( posAncre );
     posUpAnchor_.setX( posAncre );
     updateLink();

     AncreItem* item;

     foreach( item, labels_ )
     item->updateLink();

}
