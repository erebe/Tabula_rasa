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
class AlgorithmeScene;

class PictoAction: public Pictogramme {

     public:
          enum { Type = UserType + 2 };

          PictoAction(QString titre = QString( "?" ),
                       QString preCondition = QString( "∅" ),
                       QString postCondition = QString( "∅" ),
                       QGraphicsItem* parent = 0);

          PictoAction(const PictoAction& item);


          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }
          virtual Pictogramme* clone();


          void toXml( QDomDocument& doc, QDomNode& node ) const;
          void updateDimension();
          inline bool detail() const { return detail_; }
          void setDetailsVisible(bool visible);
          void setEmptyDetailsVisible(bool visible);

     protected:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          bool detail_;
          bool emptyDetail_;

          /*-----------------------------------------------------------------------------
           *  Méthodes privées
           *-----------------------------------------------------------------------------*/
          int drawDetails( QPainter* painter, LabelItem* texte, int pos ) const;
          void createLink();

          /*-----------------------------------------------------------------------------
           *  Gestionnaire d'évènements
           *-----------------------------------------------------------------------------*/
          void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );

    private:
          PictoAction& operator= (const PictoAction& item);

};

#endif // PICTOACTION_HPP
