/*
 * =====================================================================================
 *
 *       Filename:  pictoAction.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant un item du type Action
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:21:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOACTION_HPP
#define PICTOACTION_HPP
#include <QGraphicsItem>
#include "pictogramme.hpp"

class LabelItem;

class PictoAction: public Pictogramme {

     public:
          enum { Type = UserType + 2 };

          PictoAction( QString titre = QString( "?" ),
                       QString preCondition = QString( "∅" ),
                       QString postCondition = QString( "∅" ),
                       QGraphicsItem* parent = 0,
                       QGraphicsScene* scene = 0 );

          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;

          inline QString label() const { return labels_.at( 0 )->label(); }
          inline QString preCondition() const { return labels_.at( 1 )->label();; }
          inline QString postCondition() const { return labels_.at( 2 )->label(); }
          inline bool detail() const { return detail_; }
          virtual int type() const { return Type; }
          void updateDimension();

          //void setLabel( const QString& titre );
          //void setPreCondition( const QString& preCondition );
          //void setPostCondition( const QString& postCondition );
          inline void setDetail( const bool detail ) { detail_ = detail; update(); }

     private:
          bool detail_;
          bool emptyDetail_;

          int drawDetails( QPainter* painter, LabelItem* texte, int pos ) const;
          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );

};

#endif // PICTOACTION_HPP
