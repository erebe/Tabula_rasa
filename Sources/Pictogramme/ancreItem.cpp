/*
 * =====================================================================================
 *
 *       Filename:  ancreItem.cpp
 *
 *    Description:  Tabula Rasa : Implementation de classe permettant les liaisons entre
 *                  items
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:16:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "ancreItem.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

AncreItem::AncreItem( QGraphicsItem* parent, QGraphicsScene* scene ):
     QGraphicsItem( parent, scene ), parent_( 0 ), liaison_( 0 )
{}

AncreItem::~AncreItem()
{

     detach();
}

void AncreItem::setParent( AncreItem* parent )
{
     deleteLink();
     parent_ = parent;
     parent_->addChild( this );

     liaison_ = new LiaisonItem( parent_, this );
     scene()->addItem( liaison_ );
}

void AncreItem::addChild( AncreItem* child )
{

     children_.append( child );
}

void AncreItem::updateLink()
{

     if( liaison_ )
          { liaison_->updatePath(); }

     AncreItem* ancre;
     foreach( ancre, children_ )
     ancre->liaison_->updatePath();
}

QVariant AncreItem::itemChange( GraphicsItemChange change, const QVariant& value )
{

     if ( change == QGraphicsItem::ItemPositionChange ) {
          updateLink();
          AncreItem* ancre;
          foreach( ancre, children_ )
          ancre->updateLink();
     }

     return value;
}

void AncreItem::detach()
{
     deleteLink();
     deleteChildren();
}

void AncreItem::deleteLink()
{

     if( liaison_ ) {
          delete liaison_;
          parent_->children_.removeOne( this );
          liaison_ = 0;
          parent_ = 0;
     }

}

void AncreItem::deleteChildren()
{

     AncreItem* child;

     foreach( child, children_ )
     child->deleteLink();

     children_.clear();

}
