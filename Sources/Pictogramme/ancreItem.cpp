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
#include <QDebug>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
AncreItem::AncreItem( QGraphicsItem* parent, QGraphicsScene* scene ):
     QGraphicsItem( parent, scene ), parent_( 0 ), liaison_( 0 )
{}

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
          //scene()->removeItem(liaison_);
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
               { parent_->updateLink(); }

          else
               { parent_->deleteLink(); }
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
     }

     if( parent_ && parent_->liaison_ ) {
          parent_->liaison_->updatePath();
     }
}/*}}}*/

void AncreItem::addChild( AncreItem* child )
{/*{{{*/

     children_.append( child );
     child->setParent( this );


     if( !liaison_ ) {
          createLink();

     } else {
          updateLink();
     }



}/*}}}*/

void AncreItem::createLink()
{/*{{{*/

     liaison_ = new LiaisonItem( this, children_ );
     scene()->addItem( liaison_ );

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

