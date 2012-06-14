/*
 * =====================================================================================
 *
 *       Filename:  liaisonItem.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant une liaison entre deux items
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:20:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef LIAISONPICTO_HPP
#define LIAISONPICTO_HPP

#include <QGraphicsItem>

class AncreItem;

class LiaisonItem : public QGraphicsPathItem {

     public:
          enum { Type = UserType + 8 };
          enum Style { Linear, Simple, Double };

          LiaisonItem( AncreItem* parent, QList<AncreItem*>& enfants );


          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          virtual int type() const { return Type; }
          void updatePath();
          inline void setStyle( LiaisonItem::Style style ) { style_ = style; updatePath(); }
          inline Style style() { return style_; }

     protected:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          AncreItem* parent_;
          QList<AncreItem*>& children_;
          QPainterPath path_;
          Style style_;

          /*-----------------------------------------------------------------------------
           *  Methodes protégées
           *-----------------------------------------------------------------------------*/
           void drawLinearLiaison();
           void drawDoubleLiaison();
           void drawSimpleLiaison();
           void drawFullDouble();
};



#endif // LIAISONPICTO_HPP
