/*
 * =====================================================================================
 *
 *       Filename:  pictoCondition.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant une Condition simple
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:23:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOCONDITION_HPP
#define PICTOCONDITION_HPP

#include "pictogramme.hpp"

class AlgorithmeScene;

class PictoCondition : public Pictogramme {

     public:
          enum { Type = UserType + 3 };

          PictoCondition( const QString& titre,
                          QGraphicsItem* parent,
                          QGraphicsScene* scene );

          PictoCondition( const QDomElement& node,
                          AlgorithmeScene* scene = 0 );

          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;
          void updateDimension();

          QVariant itemChange( GraphicsItemChange change, const QVariant& value );
          virtual int type() const {
               return Type;
          }

          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );
          void toXml( QDomDocument& doc, QDomNode& node ) const;

          inline QString label() const {
               return labels_.at( 0 )->label();
          }

     private :
          bool isForeverAlone_;


};

#endif // PICTOCONDITION_HPP
