/*
 * =====================================================================================
 *
 *       Filename:  liaisonItem.cpp
 *
 *    Description:  Tabula Rasa : Implementation de la classe reliant deux items
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:20:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "liaisonItem.hpp"
#include "ancreItem.hpp"
#include "pictoAction.hpp"
#include <QPainter>


LiaisonItem::LiaisonItem( AncreItem* parent, AncreItem* enfant ):
    parent_( parent ), child_( enfant )
{
    updatePath();
}

void LiaisonItem::updatePath()
{

    path_ = QPainterPath();

    if( qgraphicsitem_cast<PictoAction*>(parent_)  ) {

        path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x() - 5,
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() );

        path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x() - 5,
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

        path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x() + 5,
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

        path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x() + 5,
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() );

        path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

    } else {

        path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() );

        path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                      parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

    }

    path_.lineTo( child_->scenePos().x() + child_->positionAncreHaute().x(),
                  parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

    path_.lineTo( child_->scenePos().x() + child_->positionAncreHaute().x(),
                  child_->scenePos().y() + child_->positionAncreHaute().y() );

    setPath( path_ );
}
