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
          enum AnchorType { None = 0, Up = 1, Down = 2, Both = 3  };

          AncreItem(QGraphicsItem* parent = 0);
          AncreItem( const AncreItem& ancre );
          virtual ~AncreItem();

          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          inline QPointF positionAncreBasse() const { return posBottomAnchor_; }
          inline QPointF positionAncreHaute() const { return posUpAnchor_; }


          bool addChild( AncreItem* child );
          void updateLink(); //Mets à jour le lien

          virtual int type() const { return Type; }
          inline bool isChild() { return ( parent_ ) ? true : false; }
          inline bool isParent() { return ( children_.count() ) ? true : false; }
          inline AnchorType anchorType() const { return anchorType_; }
          inline void setAnchorType( AnchorType type ) { anchorType_ = type; }

          void detach();//Appelle les deux methodes en dessous
          void deleteLink(); //Supprime la liaison
          void deleteParent();//Supprime les liaisons vers les enfants
          void setLinkStyle( LiaisonItem::Style style ) {
               if( liaison_ )
                    { liaison_->setStyle( style );}

          }
          inline LiaisonItem::Style linkStyle( ) const { return liaison_->style(); }
          inline bool hasLink() const { return ( liaison_ ); }

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
          AnchorType anchorType_;

          AncreItem* parent_;
          QList<AncreItem*> children_;
          LiaisonItem* liaison_;

          virtual void setParent( AncreItem* parent ); //Définit le parent de l'element
          virtual void createLink( );
          virtual void onChildrenChange();
          bool childExist( AncreItem* parent, AncreItem* child );

    private:
          AncreItem& operator =(const AncreItem& copy);

};

#endif // ANCREITEM_HPP
