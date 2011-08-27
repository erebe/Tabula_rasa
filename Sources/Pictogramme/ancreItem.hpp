/*
 * =====================================================================================
 *
 *       Filename:  ancreItem.hpp
 *
 *    Description:  Tabula Rasa : classe représentant un item possédant des ancres (aimant)
 *                  Il peut avoir une liaison
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:14:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef ANCREITEM_HPP
#define ANCREITEM_HPP

#include <QEvent>
#include <QGraphicsItem>
#include "liaisonItem.hpp"

class AncreItem: public QGraphicsItem {

     public:
          AncreItem( QGraphicsItem* parent = 0, QGraphicsScene* scene = 0 );
          virtual ~AncreItem();

          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          inline QPointF positionAncreBasse() const { return posBottomAnchor_; }
          inline QPointF positionAncreHaute() const { return posUpAnchor_; }

          virtual void setParent( AncreItem* parent ); //Définit le parent de l'element
          virtual void updateLink(); //Mets à jour le lien

          virtual int type() const { return Type; }
          inline bool isChild() { return ( parent_ ) ? true : false; }
          inline bool isParent() { return ( children_.count() ) ? true : false; }

          void detach();//Appelle les deux methodes en dessous
          void deleteLink(); //Supprime la liaison
          void deleteChildren();//Supprime les liaisons vers les enfants

          QList<AncreItem*> childrenList() const { return children_; }

          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value );

     protected:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          QPointF posBottomAnchor_; //coord du point d'ancrage supérieur
          QPointF posUpAnchor_; //coord du point d'ancrage inférieur

          AncreItem* parent_;
          QList<AncreItem*> children_;
          LiaisonItem* liaison_;

          virtual void addChild( AncreItem* child );

};

#endif // ANCREITEM_HPP
