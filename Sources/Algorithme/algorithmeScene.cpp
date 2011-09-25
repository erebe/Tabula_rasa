/*
 * =====================================================================================
 *
 *       Filename:  algorithmeScene.cpp
 *
 *    Description:  Tabula Rasa : Implémentation de la classe gérant la scène
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:13:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "algorithmeScene.hpp"
#include "pictoBuilder.hpp"

#include "Pictogramme/pictogramme.hpp"
#include "Pictogramme/pictoCondition.hpp"
#include "Pictogramme/pictoConditionMultiple.hpp"
#include "Pictogramme/pictoSortie.hpp"
#include "Pictogramme/pictoIteration.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
AlgorithmeScene::AlgorithmeScene( qreal x, qreal y, qreal width, qreal height, QObject* parent ):
     QGraphicsScene( x, y, width, height, parent ),
     mode_( MoveItem ), name_( "Algorithme" ),
     line_( 0 )
{/*{{{*/
     selectionArea_.second = 0;
}/*}}}*/

AlgorithmeScene::~AlgorithmeScene()
{/*{{{*/
     Pictogramme* picto;
     foreach( picto, items_ )
     delete picto;
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void AlgorithmeScene::deleteItem( Pictogramme* item )
{/*{{{*/
     items_.removeOne( item );
     removeItem( item );
     delete item;
}/*}}}*/

void AlgorithmeScene::newItem( Pictogramme* picto )
{/*{{{*/
     if( picto ) {
          items_.push_back( picto );
          emit itemAdded( picto );
     }
}/*}}}*/

void AlgorithmeScene::saveToXml( QTextStream& out ) const
{/*{{{*/
     QDomDocument doc( "Tabula_Rasa" );

     QDomNode noeud = doc.createProcessingInstruction( "xml", "version=\"1.0\"" );
     doc.insertBefore( noeud, doc.firstChild() );

     QDomElement root = doc.createElement( "Algorithme" );
     doc.appendChild( root );

     QDomElement name = doc.createElement( "nom" );
     name.appendChild( doc.createTextNode( name_ ) );
     root.appendChild( name );

     QDomElement date = doc.createElement( "date_creation" );
     date.appendChild( doc.createTextNode( QDateTime::currentDateTime().toString( "d/M/yyyy hh:mm" ) ) );
     root.appendChild( date );

     QDomElement elements = doc.createElement( "Elements" );

     Pictogramme* picto;
     foreach( picto, items_ ) {
          if( !picto->isChild() ) {
               picto->toXml( doc, elements );
          }
     }
     root.appendChild( elements );
     doc.save( out, 2 );
}/*}}}*/

void AlgorithmeScene::loadFromXml( const QDomDocument& doc )
{/*{{{*/
     QDomElement racine = doc.documentElement();
     name_ = racine.firstChildElement( "nom" ).firstChild().toText().data();

     const QDomNodeList nodes = racine.firstChildElement( "Elements" ).childNodes();

     for( int i = 0; i < nodes.count(); i++ ) {
          if( nodes.at( i ).isElement() ) {
               PictoBuilder::fromXml( nodes.at( i ).toElement() , this );
          }
     }
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Gestionnaires d'évènements
 *-----------------------------------------------------------------------------*/
void AlgorithmeScene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent )
{/*{{{*/
     mouseEvent->accept();

     if ( mouseEvent->button() == Qt::LeftButton && mode_ == EditLink ) {

          line_ = new QGraphicsLineItem( QLineF( mouseEvent->scenePos(),
                                                 mouseEvent->scenePos() ) );
          QGraphicsScene::addItem( line_ );

     } else if ( mouseEvent->button() == Qt::LeftButton && mode_ == MoveItem ) {
          if( !items( mouseEvent->scenePos() ).count() ) {

               selectionArea_.first = mouseEvent->scenePos();
               selectionArea_.second = new QGraphicsRectItem( mouseEvent->scenePos().x(),
                         mouseEvent->scenePos().y(),
                         0, 0 );
               QGraphicsScene::addItem( selectionArea_.second );

          }
     }

     QGraphicsScene::mousePressEvent( mouseEvent );
}/*}}}*/

void AlgorithmeScene::mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent )
{/*{{{*/
     mouseEvent->accept();

     if ( mode_ == EditLink && line_ != 0 ) {
          QLineF newLine( line_->line().p1(), mouseEvent->scenePos() );
          line_->setLine( newLine );

     } else if ( mode_ == MoveItem ) {
          if( selectionArea_.second != 0 ) {

               QPointF topLeft( ( selectionArea_.first.x() < mouseEvent->scenePos().x() ) ?
                                selectionArea_.first.x() : mouseEvent->scenePos().x(),

                                ( selectionArea_.first.y() < mouseEvent->scenePos().y() ) ?
                                selectionArea_.first.y() : mouseEvent->scenePos().y() );

               QPointF bottomRight( ( selectionArea_.first.x() > mouseEvent->scenePos().x() ) ?
                                    selectionArea_.first.x() : mouseEvent->scenePos().x(),

                                    ( selectionArea_.first.y() > mouseEvent->scenePos().y() ) ?
                                    selectionArea_.first.y() : mouseEvent->scenePos().y() );


               QRectF rect( topLeft, bottomRight );
               selectionArea_.second->setRect( rect );

          }

          QGraphicsScene::mouseMoveEvent( mouseEvent );
     }
}/*}}}*/

void AlgorithmeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent )
{/*{{{*/
     mouseEvent->accept();
     emit algorithmeChanged();

     if( mouseEvent->button() != Qt::LeftButton ) {
          return;
     }

     if( selectionArea_.second != 0 ) {
          foreach( QGraphicsItem * item, items( selectionArea_.second->rect() ) ) {
               item->setSelected( true );
          }
          delete selectionArea_.second;
          selectionArea_.second = 0;
     }

     /*-----------------------------------------------------------------------------
      *  Mode d'edition des liaisons
      *-----------------------------------------------------------------------------*/
     if( line_ != 0 && mode_ == EditLink ) {/*{{{*/
          QList<QGraphicsItem*> startItems = items( line_->line().p2() );
          QList<QGraphicsItem*> endItems = items( line_->line().p1() );

          if( startItems.count() && startItems.first() == line_ ) {
               startItems.removeFirst();
          }

          if( endItems.count() && endItems.first() == line_ ) {
               endItems.removeFirst();
          }

          removeItem( line_ );
          delete line_;
          line_ = 0;



          foreach( QGraphicsItem * item, startItems ) {
               if( !item->isEnabled() ) {
                    startItems.removeOne( item );
               }
          }
          foreach( QGraphicsItem * item, endItems ) {
               if( !item->isEnabled() ) {
                    endItems.removeOne( item );
               }
          }

          if( startItems.count() && endItems.count() ) {
               Pictogramme* enfant, *parent;
               enfant = parent = 0;

               if( startItems.first()->parentItem() != 0 ) {
                    enfant =  static_cast<Pictogramme*>( startItems.first()->parentItem() );

               } else {
                    enfant = static_cast<Pictogramme*>( startItems.first() );
               }

               if( endItems.first()->parentItem() != 0 &&
                   !qgraphicsitem_cast<PictoCondition*>( endItems.first()->parentItem() )
                   && !qgraphicsitem_cast<PictoConditionMultiple*>( endItems.first()->parentItem() ) ) {
                    parent = static_cast<Pictogramme*>( endItems.first()->parentItem() );

               } else if( !qgraphicsitem_cast<PictoCondition*>( endItems.first() )
                          && !qgraphicsitem_cast<PictoConditionMultiple*>( endItems.first() ) ) {
                    parent = static_cast<Pictogramme*>( endItems.first() );
               }

               if( qgraphicsitem_cast<PictoIteration*>( parent ) &&
                   qgraphicsitem_cast<PictoSortie*>( enfant ) ) {

                    emit liaisonError();
                    return;
               }

               if( ( parent != 0 ) && ( enfant != parent ) ) {
                    if( !parent->addChild( enfant ) ) {

                         emit liaisonError();
                    }
               }
          }
     }/*}}}*/


     /*-----------------------------------------------------------------------------
      *  Mode d'insertion d'item
      *-----------------------------------------------------------------------------*/
     if( ( mode_ != EditLink ) && ( mode_ != MoveItem ) ) {/*{{{*/
          Pictogramme* picto = PictoBuilder::fromMode( mode_, this );

          if( picto ) {
               QRectF size = picto->boundingRect();
               picto->setPos( mouseEvent->scenePos().x() - ( size.width() / 2 ),
                              mouseEvent->scenePos().y() - ( size.height() / 2 ) );
          }

          if( mouseEvent->modifiers() != Qt::ControlModifier ) {
               setMode( AlgorithmeScene::MoveItem );
               emit modeChanged( AlgorithmeScene::MoveItem );
          }
     }/*}}}*/


     QGraphicsScene::mouseReleaseEvent( mouseEvent );
}/*}}}*/

void AlgorithmeScene::selectAll()
{/*{{{*/

     foreach( Pictogramme * picto, items_ ) {
          picto->setSelected( true );
     }

}/*}}}*/

void AlgorithmeScene::adjust( int delta )
{/*{{{*/

     qreal maxX, maxY, minX, minY;
     maxX = maxY = 0;
     minX = width();
     minY = height();

     Pictogramme* item;
     QPointF point;

     foreach( item, items_ ) {

          point = item->scenePos();

          if( maxX < ( point.x() + item->width() ) ) {
               maxX = point.x() + item->width();
          }

          if( maxY < point.y() ) {
               maxY = point.y();
          }

          if( minX > point.x() ) {
               minX = point.x();
          }

          if( minY > point.y() ) {
               minY = point.y();
          }
     }


     setSceneRect( minX - delta , minY - delta,
                   maxX - minX + ( 2 * delta ),
                   maxY - minY + 50 + ( 2 * delta ) );

}/*}}}*/
