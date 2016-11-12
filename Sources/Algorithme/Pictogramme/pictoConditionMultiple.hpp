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
          // empty picto
          PictoConditionMultiple();
          // default picto : ? / sinon
          PictoConditionMultiple(const QString& titre);
          PictoConditionMultiple( const PictoConditionMultiple& item);


          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }
          virtual Pictogramme* clone();


          void toXml( QDomDocument& doc, QDomNode& node ) const;
          void updateDimension();
          void addLabel(LabelItem *item);

     protected:
          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );
          QVariant itemChange( GraphicsItemChange change, const QVariant& value );
          LiaisonItem::Style linkStyle() const;

    private:
          PictoConditionMultiple& operator= (const PictoConditionMultiple& item);
};

#endif // PICTOCONDITIONMULTIPLE_HPP
