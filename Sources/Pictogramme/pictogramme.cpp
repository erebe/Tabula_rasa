#include "pictogramme.hpp"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "algorithmeScene.hpp"


Pictogramme::Pictogramme( QGraphicsItem* parent, QGraphicsScene* scene ):
        AncreItem( parent, scene ), pos_(0)
{
    setFlags( QGraphicsItem::ItemIsMovable |
              QGraphicsItem::ItemIsSelectable |
              QGraphicsItem::ItemSendsGeometryChanges );

    actions_["Supprimer"] = contexteMenu_.addAction( tr("Supprimer") );
    actions_["Detacher"] = contexteMenu_.addAction( tr("Detacher") );
}

Pictogramme::~Pictogramme(){

        LabelItem* label;

        foreach( label, labels_ )
                delete label;

}

void Pictogramme::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ){

    Q_UNUSED( option );
    Q_UNUSED( widget );

    if( isSelected() ){
            painter->setPen( QColor( 0, 0, 255 ) );
            painter->drawRect( boundingRect() );
    }
}


void Pictogramme::mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event ){

        LabelItem* label;
        foreach( label, labels_ ){
                if( label->contains( event->pos() - label->pos() ) && label->isVisible() ){
                        ungrabMouse();
                        emit doubleClick( label );
                        prepareGeometryChange();
                        updateDimension();
                        break;
                 }
        }
}

 void Pictogramme::contextMenuEvent( QGraphicsSceneContextMenuEvent *event ){

         event->accept();

         scene()->clearSelection();
         setSelected( true );
         ungrabMouse();
         QAction* selectedAction = contexteMenu_.exec( event->screenPos() );

         processAction( selectedAction, event );


 }


 void Pictogramme::processAction( QAction* action, QGraphicsSceneContextMenuEvent *event ){

     if( actions_["Supprimer"] == action ){

             static_cast<AlgorithmeScene*>(scene())->deleteItem( this );
             return;

     }else if( actions_["Detacher"] == action ){

             detach();
             LabelItem* item;
             foreach( item, labels_)
                     item->detach();
     }
 }
