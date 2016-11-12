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
Pictogramme::Pictogramme( QGraphicsItem* parent ):
     AncreItem( parent ), pos_( 0 )
{/*{{{*/
     setFlags( QGraphicsItem::ItemIsMovable |
               QGraphicsItem::ItemIsSelectable |
               QGraphicsItem::ItemSendsGeometryChanges );
     fillContextMenuWithDefaultActions();

}/*}}}*/

Pictogramme::Pictogramme(const Pictogramme &item):
    AncreItem(item),
    pos_(item.pos_)
{

    setFlags( QGraphicsItem::ItemIsMovable |
              QGraphicsItem::ItemIsSelectable |
              QGraphicsItem::ItemSendsGeometryChanges );
    fillContextMenuWithDefaultActions();

    foreach (const LabelItem* label, item.labels_) {
        LabelItem* tmp = new LabelItem(*label);
        tmp->setParentItem(this);
        labels_.append(tmp);
    }
}

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

void Pictogramme::fillContextMenuWithDefaultActions() {
    addContextMenuEntry("Supprimer", "Supprimer");
    sousMenu_ = contexteMenu_.addMenu( QIcon(), "Style des liaisons" );

    addContextMenuEntry(sousMenu_, "LSimple", "Simple");
    addContextMenuEntry(sousMenu_, "LDouble", "Double");
    addContextMenuEntry(sousMenu_, "LLineaire", "Linéaire");
    contexteMenu_.addSeparator();

    addContextMenuEntry("DelierP", "Délier du parent");
    addContextMenuEntry("DelierE", "Délier des enfants");
    addContextMenuEntry("Delier", "Délier de tous");
    contexteMenu_.addSeparator();
}

void Pictogramme::addContextMenuEntry(QMenu *menu, QString key, const char* text, bool checkable, bool checked) {
    QAction* action = actions_[key] = menu->addAction( tr( text ) );
    action->setCheckable( checkable );
    action->setChecked( checked );
}

void Pictogramme::addContextMenuEntry(QString key, const char* text, bool checkable, bool checked) {
    addContextMenuEntry(&contexteMenu_, key, text, checkable, checked);
}

QAction *Pictogramme::getContextMenuAction(QString key) {
    return actions_[key];
}

void Pictogramme::prepareContextMenu() {
    if( liaison_ ) {
         sousMenu_->setEnabled( true );
         actions_["DelierE"]->setEnabled( true );

    } else {
         bool enabled = false;
         foreach( LabelItem * item, labels_ ) {
              if( item->isParent() ) {
                   enabled = true;
                   break;
              }
         }

         if( enabled ) {
              sousMenu_->setEnabled( true );
              actions_["DelierE"]->setEnabled( true );

         } else {
              sousMenu_->setEnabled( false );
              actions_["DelierE"]->setEnabled( false );
         }
    }

    if( isChild() ) {
         actions_["DelierP"]->setEnabled( true );

    } else {
         actions_["DelierP"]->setEnabled( false );
    }

    if( actions_["DelierP"]->isEnabled() ||
        actions_["DelierE"]->isEnabled() ) {
         actions_["Delier"]->setEnabled( true );

    } else {
         actions_["Delier"]->setEnabled( false );
    }
}



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

     prepareContextMenu();
     QAction* selectedAction = contexteMenu_.exec( event->screenPos() );
     if (selectedAction) {
         // do not process if the menu has been closed (no selected action)
        processAction( selectedAction, event );
     }
}/*}}}*/

void Pictogramme::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     Q_UNUSED( event );

     if( actions_["Supprimer"] == action ) {
          static_cast<AlgorithmeScene*>( scene() )->deleteItem( this );
          return;

     } else if( actions_["Delier"] == action ) {
          detach();
          foreach( LabelItem * item, labels_ ) {
               item->detach();
          }

     } else if( actions_["DelierE"] == action ) {
          deleteLink();
          foreach( LabelItem * item, labels_ ) {
               item->deleteLink();
          }

     } else if( actions_["DelierP"] == action ) {
          deleteParent();

     } else if( actions_["LSimple"] == action ) {
          if( liaison_ ) {
               liaison_->setStyle( LiaisonItem::Simple );
          }

          foreach( LabelItem * item, labels_ ) {
               item->setLinkStyle( LiaisonItem::Simple );
          }

     } else if( actions_["LDouble"] == action ) {
          if( liaison_ ) {
               liaison_->setStyle( LiaisonItem::Double );
          }

          foreach( LabelItem * item, labels_ ) {
               item->setLinkStyle( LiaisonItem::Double );
          }

     } else if( actions_["LLineaire"] == action ) {
          if( liaison_ ) {
               liaison_->setStyle( LiaisonItem::Linear );
          }

          foreach( LabelItem * item, labels_ ) {
               item->setLinkStyle( LiaisonItem::Linear );
          }
     }
}/*}}}*/

