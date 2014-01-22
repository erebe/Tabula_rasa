/*
 * =====================================================================================
 *
 *       Filename:  labelItem.hpp
 *
 *    Description:  Tabula Rasa : Classe representant un item textuel
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:17:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef LABELITEM_HPP
#define LABELITEM_HPP
#include "ancreItem.hpp"

class LabelItem : public AncreItem {

     public:
          enum { Type = UserType + 1 };

          LabelItem( const QString& texte,
                     const int maxWidth = 150,
                     const int minWidth = 50,
                     const int height = 50,
                     QGraphicsItem* parent = 0,
                     QGraphicsScene* scene = 0 );
          LabelItem(const LabelItem& item);

          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          virtual void paint( QPainter* painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }

          void setLabel( const QString& texte );
          bool isEmpty() const;
          inline QString label() const { return label_.first; }
          inline unsigned int width() const { return label_.second; }


     protected:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          QPair<QString, unsigned int> label_; //texte et sa largeur
          unsigned int height_, maxWidth_, minWidth_;

          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          unsigned int calculLargeurTexte() const; //retourne la largeur du texte
          void formatString(); //retourne la largeur du texte
          virtual void onChildrenChange();


    private:
          LabelItem& operator= (const LabelItem& item);

};

#endif // LABELITEM_HPP
