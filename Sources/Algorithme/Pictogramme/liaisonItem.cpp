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
#include "pictoAction.hpp"
#include <QPainter>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
LiaisonItem::LiaisonItem( AncreItem* parent, QList<AncreItem*>& enfants ):
     parent_( parent ), children_( enfants ), style_( Linear )
{/*{{{*/
     setEnabled( 0 );
     updatePath();
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void LiaisonItem::updatePath()
{/*{{{*/
     path_ = QPainterPath();

     switch( style_ ) {

        case Simple: drawSimpleLiaison();
                    break;
        case Double: drawDoubleLiaison();
                    break;
        case Linear: drawLinearLiaison();
                    break;
     }

     setPath( path_ );
}/*}}}*/

void LiaisonItem::drawLinearLiaison()
{/*{{{*/

      AncreItem* ancre;
      foreach( ancre, children_ ) {
           path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                         parent_->scenePos().y() + parent_->positionAncreBasse().y() );
           path_.lineTo( ancre->scenePos().x() + ancre->positionAncreHaute().x(),
                         ancre->scenePos().y() + ancre->positionAncreHaute().y() );
      }

}/*}}}*/

void LiaisonItem::drawDoubleLiaison()
{/*{{{*/

       //Watch if there is only one child and just below the parent
       if( children_.size() == 1 &&
           parent_->scenePos().x() + parent_->positionAncreBasse().x() - 20 
           < children_[0]->scenePos().x() + children_[0]->positionAncreHaute().x()

          &&  parent_->scenePos().x() + parent_->positionAncreBasse().x() + 20
           > children_[0]->scenePos().x() + children_[0]->positionAncreHaute().x() )
       {
           drawFullDouble();
           return;
       }

       //Normal behaviour -- Little rectangle + line
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


      qreal minX, maxX;
      minX = maxX = parent_->scenePos().x() + parent_->positionAncreBasse().x();
      foreach( AncreItem* ancre, children_ ) {
           if( ( ancre->scenePos().x() + ancre->positionAncreHaute().x() ) < minX ) {
                minX = ancre->scenePos().x() + ancre->positionAncreHaute().x();
           }

           if( ancre->scenePos().x() + ancre->positionAncreHaute().x() > maxX ) {
                maxX = ancre->scenePos().x() + ancre->positionAncreHaute().x();
           }

           path_.moveTo( ancre->scenePos().x() + ancre->positionAncreHaute().x(),
                         parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );
           path_.lineTo( ancre->scenePos().x() + ancre->positionAncreHaute().x(),
                         ancre->scenePos().y() + ancre->positionAncreHaute().y() );
      }

      path_.moveTo( minX,
                    parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );
      path_.lineTo( maxX,
                    parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );


}/*}}}*/

void LiaisonItem::drawSimpleLiaison()
{/*{{{*/

       path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                     parent_->scenePos().y() + parent_->positionAncreBasse().y() );
       path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                     parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

      qreal minX, maxX;
      minX = maxX = parent_->scenePos().x() + parent_->positionAncreBasse().x();

      foreach( AncreItem* ancre, children_ ) {
           if( ( ancre->scenePos().x() + ancre->positionAncreHaute().x() ) < minX ) {
                minX = ancre->scenePos().x() + ancre->positionAncreHaute().x();
           }

           if( ancre->scenePos().x() + ancre->positionAncreHaute().x() > maxX ) {
                maxX = ancre->scenePos().x() + ancre->positionAncreHaute().x();
           }

           path_.moveTo( ancre->scenePos().x() + ancre->positionAncreHaute().x(),
                         parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );
           path_.lineTo( ancre->scenePos().x() + ancre->positionAncreHaute().x(),
                         ancre->scenePos().y() + ancre->positionAncreHaute().y() );
      }

      path_.moveTo( minX,
                    parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );
      path_.lineTo( maxX,
                    parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

}/*}}}*/

void LiaisonItem::drawFullDouble()
{/*{{{*/

       //Point en haut à gauche
       path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x() - 5,
                     parent_->scenePos().y() + parent_->positionAncreBasse().y() );

       // //Point en bas à gauche
       path_.lineTo( children_[0]->scenePos().x() + children_[0]->positionAncreHaute().x() - 5,
                     children_[0]->scenePos().y() + children_[0]->positionAncreHaute().y() );

       // //Point en bas à droite
       path_.lineTo( children_[0]->scenePos().x() + children_[0]->positionAncreHaute().x() + 5,
                     children_[0]->scenePos().y() + children_[0]->positionAncreHaute().y() );

       //Point en haut à droite
       path_.lineTo( parent_->scenePos().x() + parent_->positionAncreBasse().x() + 5,
                     parent_->scenePos().y() + parent_->positionAncreBasse().y() );

       //On ferme le rectangle
       path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                     parent_->scenePos().y() + parent_->positionAncreBasse().y() + 25 );

}/*}}}*/
