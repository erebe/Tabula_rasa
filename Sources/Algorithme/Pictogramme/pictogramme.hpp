/*
 * =====================================================================================
 *
 *       Filename:  pictogramme.hpp
 *
 *    Description:  Tabula Rasa : Classe mère de tous les élements de l'algorithme
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:34:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOGRAMME_HPP
#define PICTOGRAMME_HPP

#include <QMenu>
#include <QtXml>

#include "ancreItem.hpp"
#include "labelItem.hpp"

class QGraphicsItem;

class Pictogramme : public QObject, public AncreItem {

          Q_OBJECT

     public:
          Pictogramme( QGraphicsItem* parent = 0, QGraphicsScene* scene = 0 );
          virtual ~Pictogramme();


          /*-----------------------------------------------------------------------------
           *  Methodes
           *-----------------------------------------------------------------------------*/
          virtual void paint( QPainter* painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget );

          virtual void updateDimension() = 0; //met à jour la dimension de l'item
          inline unsigned int width() const { return pos_; }

          //A implémenter pour sauvegarder en XML
          virtual void toXml( QDomDocument& doc, QDomNode& node ) const = 0;



     signals:
          void doubleClick( LabelItem* item );//Pour renommer un labelItem


     protected:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          QList<LabelItem*> labels_; //liste des labels que contient le picto
          unsigned int pos_; //A renommer par width_

          QMenu contexteMenu_; //appelé lors du clic droit
          QMenu* sousMenu_;
          QMap<QString, QAction*> actions_;


          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event );
          void contextMenuEvent( QGraphicsSceneContextMenuEvent* event );
          virtual void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );

};

#endif // PICTOGRAMME_HPP
