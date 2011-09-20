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
     parent_( parent ), children_( enfants ), style_( Double )
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

     if( style_ == Simple || style_ == Double  ) {
          if( style_ == Double  ) {
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

          qreal minX, maxX;
          minX = maxX = parent_->scenePos().x() + parent_->positionAncreBasse().x();
          AncreItem* ancre;
          foreach( ancre, children_ ) {
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
     }

     if( style_ == Linear ) {
          AncreItem* ancre;
          foreach( ancre, children_ ) {
               path_.moveTo( parent_->scenePos().x() + parent_->positionAncreBasse().x(),
                             parent_->scenePos().y() + parent_->positionAncreBasse().y() );
               path_.lineTo( ancre->scenePos().x() + ancre->positionAncreHaute().x(),
                             ancre->scenePos().y() + ancre->positionAncreHaute().y() );
          }
     }

     setPath( path_ );
}/*}}}*/
