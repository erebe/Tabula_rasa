/*
 * =====================================================================================
 *
 *       Filename:  algorithmeScene.hpp
 *
 *    Description:  Tabula Rasa : Classe gérant la scène où l'on edite l'algorithme
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:10:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef ALGORITHMESCENE_HPP
#define ALGORITHMESCENE_HPP

#include <QGraphicsScene>
#include <QtXml>

class QTextStream;
class Pictogramme;

class AlgorithmeScene: public QGraphicsScene {

          Q_OBJECT

     public:
          //Représente les modes d'interactions avec la scène
          enum Mode { MoveItem, EditLink, SelectArea,
                      InsertAction, InsertProcedure, InsertLoop,
                      InsertCondition, InsertMultiCondition, InsertExit
                    };

          AlgorithmeScene( qreal x, qreal y, qreal width, qreal height, QObject* parent = 0 );
          ~AlgorithmeScene();


          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          inline void setMode( Mode mode )
          { mode_ = mode; }
          inline void setName( const QString& name )
          { name_ = name;}

          void deleteItem( Pictogramme* item );
          void newItem( Pictogramme* ); //appelé par PictoBuilder

          //Sauvegarde et chargement au format XML
          void saveToXml( QTextStream& out ) const;
          void loadFromXml( const QDomDocument& doc );
          void selectAll();

     signals:
          void modeChanged( AlgorithmeScene::Mode mode ); //emit lorsqu'on change de mode
          void itemAdded( Pictogramme* picto ); //emit lors de l'ajout d'un Pictogramme sur la scène
          void liaisonError(); //Lorsqu'une liaison est impossible



     private:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          Mode mode_;
          QString name_; //Nom de l'agorithme
          QGraphicsLineItem* line_; //Line créée dans le mode edition lien
          QPair<QPointF, QGraphicsRectItem*> selectionArea_;
          QList<Pictogramme*> items_; //Liste de tous les pictogrammes de la scène (sans les liaisons)


          /*-----------------------------------------------------------------------------
           *  Gestionnaire évènements
           *-----------------------------------------------------------------------------*/
          void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent );
          void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent );
          void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent );
};
#endif // ALGORITHMESCENE_HPP
