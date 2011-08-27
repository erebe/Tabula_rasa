/*
 * =====================================================================================
 *
 *       Filename:  pictoConditionMultiple.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant une condition Multiple
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:26:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOCONDITIONMULTIPLE_HPP
#define PICTOCONDITIONMULTIPLE_HPP

#include "pictogramme.hpp"
class AlgorithmeScene;

class PictoConditionMultiple : public Pictogramme {

     public:
          enum { Type = UserType + 7 };
          PictoConditionMultiple( const QString& titre,
                                  QGraphicsItem* parent,
                                  QGraphicsScene* scene );

          PictoConditionMultiple( const QDomElement& node,
                                  AlgorithmeScene* scene = 0 );


          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }


          void toXml( QDomDocument& doc, QDomNode& node ) const;
          void updateDimension();

     protected:
          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );
          QVariant itemChange( GraphicsItemChange change, const QVariant& value );
};

#endif // PICTOCONDITIONMULTIPLE_HPP
