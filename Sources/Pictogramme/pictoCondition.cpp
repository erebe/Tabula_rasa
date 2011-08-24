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
    Pictogramme( parent, scene ), isForeverAlone_( false )
{
    labels_ << new LabelItem( label, 150, 25, 50, this, scene );
    labels_ << new LabelItem( "Sinon", 150, 25, 50, this, scene );
    posUpAnchor_.setY( 0 );
    updateDimension();

    actions_["SingleOne"] = contexteMenu_.addAction( tr( "Condition unique" ) );
    actions_["SingleOne"]->setCheckable( true );
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




    if( !isForeverAlone_ ) {
        //On dessine la barre vecticale
        painter->drawLine( pos, 0, pos, 50 );
        labels_.at( 1 )->setPos( pos + 10, 0 );
        pos += labels_.at( 1 )->width() + 10;
        labels_.at( 1 )->setEnabled( true );
        labels_.at( 1 )->setVisible( true );
    } else {
        labels_.at( 1 )->setEnabled( false );
        labels_.at( 1 )->setVisible( false );
    }

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
    if( !isForeverAlone_ ) {
        pos_ = labels_.at( 1 )->width()
               + labels_.at( 0 )->width() + 65;
    } else {
        pos_ = labels_.at( 0 )->width() + 55;

    }
    posAncre = ( pos_ / 2 );

    posBottomAnchor_.setX( posAncre );
    posUpAnchor_.setX( posAncre );
    updateLink();

    AncreItem* item;

    foreach( item, labels_ )
    item->updateLink();

}

void PictoCondition::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{

    if( action == actions_["SingleOne"] ) {
        isForeverAlone_ = !isForeverAlone_;
        prepareGeometryChange();
        updateDimension();

    } else {
        Pictogramme::processAction( action, event );
    }
}
