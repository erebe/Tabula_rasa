#include "pictoProcedure.hpp"
#include <QPainter>


PictoProcedure::PictoProcedure( QString titre,
                                QString preCondition,
                                QString postCondition,
                                QGraphicsItem* parent,
                                QGraphicsScene* scene) :
    Pictogramme( parent, scene ), detail_(true)
{
    labels_ << new LabelItem( preCondition, 150, 15, 50, this, scene );
    labels_ << new LabelItem( titre, 200, 50, 50, this, scene );
    labels_ << new LabelItem( postCondition, 150, 15, 50, this, scene );
    actions_["Details"] = contexteMenu_.addAction( tr("Afficher/Masquer les détails") );
}

void PictoProcedure::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ){

    Q_UNUSED( option );
    Q_UNUSED( widget );

    pos_ = drawDetails( painter, labels_.at( 0 ), 5 );

    posBottomAnchor_ = QPoint( pos_ + ( labels_.at( 1 )->width() +20 ) / 2, 55 );
    posUpAnchor_ = QPoint( pos_ + ( labels_.at( 1 )->width() +20 ) / 2, 5 );

    painter->drawRect( pos_, 5,
                       labels_.at( 1 )->width() + 20, 50 );
    pos_ += 10;
    painter->drawLine( pos_, 5,
                       pos_, 55 );
    painter->drawLine( pos_ + labels_.at( 1 )->width(), 5,
                       pos_ + labels_.at( 1 )->width(), 55 );

    labels_.at( 1 )->setPos( pos_, 5 );

    pos_ += labels_.at( 1 )->width() + 25;

    pos_ = drawDetails( painter, labels_.at( 2 ), pos_ );


    Pictogramme::paint( painter, option, widget );
}

int PictoProcedure::drawDetails( QPainter* painter, LabelItem* texte, int pos ) const {

    if( detail() ){
            //Accolade gauche
            painter->drawArc( pos, 5, 10, 25, 90 * 16, 179 * 16 );
            painter->drawArc( pos - 6, 30, 15, 2, 90 * 16, 180 * 16 );
            painter->drawArc( pos, 32, 10, 25, 90 * 16, 179 * 16 );
            pos += 15;

            //On écrit le texte
            texte->setPos( pos, 4 );
            texte->setEnabled( true );
            texte->setVisible( true );
            pos += texte->width() + 5;

            //Accolade droite
            painter->drawArc( pos, 5, 10, 25, 90 * 16, -179 * 16 );
            painter->drawArc( pos + 1, 30, 15, 2, 90 * 16, -180 * 16 );
            painter->drawArc( pos, 32, 10, 25, 90 * 16, -179 * 16 );
            pos += 25;
    }else{
            texte->setEnabled( false );
            texte->setVisible( false );
    }


    return pos;

}

QRectF PictoProcedure::boundingRect() const {

        return QRectF( 0, 0, pos_, 60 );
}

void PictoProcedure::processAction( QAction* action, QGraphicsSceneContextMenuEvent *event ){


        if( action == actions_["Details"] ){
                prepareGeometryChange();
                pos_ += labels_.at( 0 )->width() + labels_.at( 2 )->width() + 100;
                detail_ = !detail_;
        }else{
                Pictogramme::processAction( action, event );
        }
}
