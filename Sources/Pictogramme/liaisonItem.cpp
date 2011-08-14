#include "liaisonItem.hpp"
#include "ancreItem.hpp"
#include <QPainter>


LiaisonItem::LiaisonItem( AncreItem* parent, AncreItem* enfant ):
        parent_(parent), child_(enfant)
{
        updatePath();
}

void LiaisonItem::updatePath(){

        path_ =	QPainterPath();
        path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() );

        path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() + 50 );

        path_.lineTo( child_->scenePos().x() + child_->positionAncreHaute().x(),
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() + 50 );

        path_.lineTo( child_->scenePos().x() + child_->positionAncreHaute().x(),
                      child_->scenePos().y() + child_->positionAncreHaute().y() );

        setPath( path_ );
}
