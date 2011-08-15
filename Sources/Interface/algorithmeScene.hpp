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
#include "Pictogramme/pictogramme.hpp"

class AlgorithmeScene: public QGraphicsScene {

          Q_OBJECT

     public:
          enum Mode { MoveItem, EditLink,
                      InsertAction, InsertProcedure, InsertLoop,
                      InsertCondition, InsertMultiCondition, InsertExit
                    };

          AlgorithmeScene( qreal x, qreal y, qreal width, qreal height, QObject* parent = 0 );
          ~AlgorithmeScene();
          inline void setMode( Mode mode ) { mode_ = mode; }
          void deleteItem( Pictogramme* item );

     signals:
          void modeChanged( AlgorithmeScene::Mode mode );

     private:
          Mode mode_;
          QGraphicsLineItem* line_;
          QList<Pictogramme*> items_;

          void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent );
          void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent );
          void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent );
};

#endif // ALGORITHMESCENE_HPP
