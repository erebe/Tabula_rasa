/*
 * =====================================================================================
 *
 *       Filename:  pictogramme.cpp
 *
 *    Description:  Tabula Rasa : Implementation de base des items de l'algorithme
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:36:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "pictogramme.hpp"
#include "algorithmeScene.hpp"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
Pictogramme::Pictogramme( QGraphicsItem* parent, QGraphicsScene* scene ):
     AncreItem( parent, scene ), pos_( 0 )
{/*{{{*/
     setFlags( QGraphicsItem::ItemIsMovable |
               QGraphicsItem::ItemIsSelectable |
               QGraphicsItem::ItemSendsGeometryChanges );

     actions_["Supprimer"] = contexteMenu_.addAction( tr( "Supprimer" ) );
     contexteMenu_.addSeparator();
     actions_["DelierP"] = contexteMenu_.addAction( tr( "Délier du parent" ) );
     actions_["DelierE"] = contexteMenu_.addAction( tr( "Délier des enfants" ) );
     actions_["Delier"] = contexteMenu_.addAction( tr( "Délier de tous" ) );
     contexteMenu_.addSeparator();
}/*}}}*/

Pictogramme::~Pictogramme()
{/*{{{*/

     LabelItem* label;

     foreach( label, labels_ )
     delete label;

}/*}}}*/



/*-----------------------------------------------------------------------------
 * Méthodes
 *-----------------------------------------------------------------------------*/
void Pictogramme::paint( QPainter* painter,
                         const QStyleOptionGraphicsItem* option,
                         QWidget* widget )
{/*{{{*/

     Q_UNUSED( option );
     Q_UNUSED( widget );

     if( isSelected() ) {
          painter->setPen( QColor( 0, 0, 255 ) );
          painter->drawRect( boundingRect() );
     }
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Gestionnaires d'évènements
 *-----------------------------------------------------------------------------*/
void Pictogramme::mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event )
{/*{{{*/

     LabelItem* label;
     foreach( label, labels_ ) {
          if( label->contains( event->pos() - label->pos() ) && label->isVisible() ) {
               ungrabMouse();
               emit doubleClick( label );
               prepareGeometryChange();
               updateDimension();
               break;
          }
     }
}/*}}}*/

void Pictogramme::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{/*{{{*/

     event->accept();

     scene()->clearSelection();
     setSelected( true );
     ungrabMouse();
     QAction* selectedAction = contexteMenu_.exec( event->screenPos() );

     processAction( selectedAction, event );


}/*}}}*/

void Pictogramme::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     Q_UNUSED( event );

     if( actions_["Supprimer"] == action ) {

          static_cast<AlgorithmeScene*>( scene() )->deleteItem( this );
          return;

     } else if( actions_["Delier"] == action ) {

          detach();
          LabelItem* item;
          foreach( item, labels_ )
          item->detach();

     } else if( actions_["DelierE"] == action ) {

          deleteChildren();

     } else if( actions_["DelierP"] == action ) {

          deleteLink();
     }
}/*}}}*/

