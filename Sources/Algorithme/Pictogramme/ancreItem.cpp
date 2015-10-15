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
#include "liaisonItem.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
AncreItem::AncreItem( QGraphicsItem* parent):
     QGraphicsItem( parent), anchorType_( None ), parent_( 0 ), liaison_( 0 )
{
}


AncreItem::AncreItem( const AncreItem& item ):
    QGraphicsItem( item.parentItem()),
    posBottomAnchor_(item.posBottomAnchor_), posUpAnchor_(item.posUpAnchor_),
    anchorType_( item.anchorType() ), parent_( 0 ),
    liaison_(0)
{
    setPos(item.pos());
}

AncreItem::~AncreItem()
{/*{{{*/
     detach();
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void AncreItem::detach()
{/*{{{*/
     deleteParent();
     deleteLink();
}/*}}}*/

void AncreItem::deleteLink()
{/*{{{*/
     if( liaison_ ) {
          delete liaison_;
          liaison_ = 0;
          AncreItem* ancre;
          foreach( ancre, children_ ) {
               ancre->deleteParent();
          }
          children_.clear();
     }
}/*}}}*/

void AncreItem::deleteParent()
{/*{{{*/
     if( parent_ ) {
          parent_->children_.removeOne( this );

          if( parent_->children_.count() )
          {
              parent_->updateLink();
              parent_->onChildrenChange();
          }
          else
          { 
              parent_->deleteLink();
          }
     }

     parent_ = 0;
}/*}}}*/

void AncreItem::setParent( AncreItem* parent )
{/*{{{*/
     deleteParent();
     parent_ = parent;
}/*}}}*/

void AncreItem::updateLink()
{/*{{{*/

    if( liaison_ ) {
        liaison_->updatePath();

        if(scene() != NULL && !scene()->items().contains(liaison_)) {
            scene()->addItem(liaison_);
        }

    }

     if( parent_ && parent_->liaison_ ) {
          parent_->liaison_->updatePath();
     }
}/*}}}*/

bool AncreItem::addChild( AncreItem* child )
{/*{{{*/

     if( !( anchorType() & Down ) ||
         !( child->anchorType() & Up ) ) {
          return false;
     }

     if( childExist( this, child ) ) {
          return false;
     }

     children_.append( child );
     child->setParent( this );

     if( !liaison_ ) {
          createLink();

     } else {
          updateLink();
     }
     onChildrenChange();

     return true;
}/*}}}*/

void AncreItem::onChildrenChange()
/*{{{*/
{}
/*}}}*/

void AncreItem::createLink()
{/*{{{*/
     liaison_ = new LiaisonItem( this, children_ );
     updateLink();
}/*}}}*/

bool AncreItem::childExist( AncreItem* parent, AncreItem* child )
{/*{{{*/

     if( parent && parent->parentItem() ) {
          parent = static_cast<AncreItem*>( parent->parentItem() );
     }

     if( parent == 0 ) {
          return 0;

     } else if( parent == child ) {
          return 1;

     } else {
          return childExist( parent->parent_, child );
     }

}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Gestionnaire évènements
 *-----------------------------------------------------------------------------*/
QVariant AncreItem::itemChange( GraphicsItemChange change, const QVariant& value )
{/*{{{*/

     if ( change == QGraphicsItem::ItemPositionChange ) {
          updateLink();
     }

     return value;
}/*}}}*/

