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

          PictoCondition( const QString& titre );

          PictoCondition( const QDomElement& node,
                          AlgorithmeScene* scene = 0 );

          PictoCondition( const PictoCondition& item);

          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }
          virtual Pictogramme* clone();

          void updateDimension();
          void toXml( QDomDocument& doc, QDomNode& node ) const;

     protected:
          bool isForeverAlone_; //Doit on afficher le sinon ou pas

          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          QVariant itemChange( GraphicsItemChange change, const QVariant& value );
          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );

    private:
          PictoCondition& operator=(const PictoCondition& item);

};

#endif // PICTOCONDITION_HPP
