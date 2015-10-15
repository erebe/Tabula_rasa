/*
 * =====================================================================================
 *
 *       Filename:  pictoIteration.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant une iteration
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:36:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOITERATION_HPP
#define PICTOITERATION_HPP

#include "pictogramme.hpp"

class QGraphicsItem;
class AlgorithmeScene;

class PictoIteration : public Pictogramme {

     public:
          enum { Type = UserType + 4 };

          PictoIteration( QString titre = QString( "?" ));

          PictoIteration( const QDomElement& node,
                          AlgorithmeScene* scene = 0 );

          PictoIteration( const PictoIteration& item );
          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          void paint( QPainter* painter,
                      const QStyleOptionGraphicsItem* option,
                      QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }
          virtual Pictogramme* clone();

          void updateDimension();
          void toXml( QDomDocument& doc, QDomNode& node ) const;
          void createLink();

     private:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          QPointF points_[3];
          bool isNumberedLoop_;


          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );

    private:
          PictoIteration& operator=(const PictoIteration& item);
};

#endif // PICTOITERATION_HPP
