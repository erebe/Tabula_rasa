#include "ancreItem.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

AncreItem::AncreItem( QGraphicsItem* parent, QGraphicsScene* scene ):
        QGraphicsItem( parent, scene ), parent_(0), liaison_(0)
{}

AncreItem::~AncreItem(){

        detach();
}

void AncreItem::setParent( AncreItem* parent ){

        parent_ = parent;
        parent_->addChild( this );

        if( liaison_ )
                delete liaison_;

        liaison_ = new LiaisonItem( parent_, this );
        scene()->addItem( liaison_ );
}

void AncreItem::addChild( AncreItem* child ){

        children_.append( child );
}

void AncreItem::updateLink(){

        if( liaison_ )
                liaison_->updatePath();
}

QVariant AncreItem::itemChange( GraphicsItemChange change, const QVariant &value ){

         if ( change == QGraphicsItem::ItemPositionChange ){
                 updateLink();
                 AncreItem* ancre;
                 foreach( ancre, children_ )
                         ancre->updateLink();
         }

         return value;
}

void AncreItem::detach(){

        deleteLink();

        AncreItem* tmp;
        foreach( tmp, children_ )
               tmp->deleteLink();

         children_.clear();


}

void AncreItem::deleteLink(){

    if( liaison_ ){
           delete liaison_;
           parent_->children_.removeOne( this );
           liaison_ = 0;
           parent_ = 0;
    }

}
