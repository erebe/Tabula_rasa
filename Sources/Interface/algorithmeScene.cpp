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
#include "Pictogramme/pictogramme.hpp"
#include "Pictogramme/ancreItem.hpp"
#include "Pictogramme/pictoBuilder.hpp"
#include "Pictogramme/pictoCondition.hpp"
#include "Pictogramme/pictoConditionMultiple.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>


/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
AlgorithmeScene::AlgorithmeScene( qreal x, qreal y, qreal width, qreal height, QObject* parent ):
     QGraphicsScene( x, y, width, height, parent ),
     mode_( MoveItem ), name_( "Algorithme" ),
     line_( 0 ), root_( 0 ), crown_( 0 )
{/*{{{*/
     icoCrown_ = QPixmap( ":/Icones/croix.ico" );
}/*}}}*/

AlgorithmeScene::~AlgorithmeScene()
{/*{{{*/

     if( crown_ )
          { delete crown_; }

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

     if( root_ == item ) {
          delete crown_;
          root_ = 0;
          crown_ = 0;
     }

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


     root_->toXml( doc, elements );


     root.appendChild( elements );
     doc.save( out, 2 );

}/*}}}*/

void AlgorithmeScene::loadFromXml( const QDomDocument& doc )
{/*{{{*/
     QDomElement racine = doc.documentElement();
     name_ = racine.firstChildElement( "nom" ).firstChild().toText().data();

     racine = racine.firstChildElement( "Elements" ).firstChildElement();

     root_ = PictoBuilder::fromXml( racine, this );
     icoCrown_ = QPixmap( ":/Icones/croix.ico" );
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
          QGraphicsScene::mouseMoveEvent( mouseEvent );
     }

}/*}}}*/

void AlgorithmeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent )
{/*{{{*/

     mouseEvent->accept();

     if( mouseEvent->button() != Qt::LeftButton ) {
          return;
     }

     if( mode_ == SetRoot ) {
          QList<QGraphicsItem*> liste = items( mouseEvent->scenePos() );

          QGraphicsItem* item;

          foreach( item, liste ) {
               if( qgraphicsitem_cast<LiaisonItem*>( item ) ||
                   qgraphicsitem_cast<LabelItem*>( item ) ) {
                    liste.removeOne( item );
               }
          }

          if( !liste.count() )
               { return; }

          root_ = static_cast<Pictogramme*>( liste.at( 0 ) );
          delete crown_;
          crown_ = addPixmap( icoCrown_ );
          crown_->setParentItem( root_ );
          crown_->setPos( -8, -8 );
          setMode( AlgorithmeScene::MoveItem );
          emit modeChanged( AlgorithmeScene::MoveItem );

     }

     if( line_ != 0 && mode_ == EditLink ) {

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

          QGraphicsItem* item;

          foreach( item, startItems ) {
               if( qgraphicsitem_cast<LiaisonItem*>( item ) ) {
                    startItems.removeOne( item );
               }
          }

          foreach( item, endItems ) {
               if( qgraphicsitem_cast<LiaisonItem*>( item ) ) {
                    endItems.removeOne( item );
               }
          }


          if( startItems.count() && endItems.count() ) {

               AncreItem* enfant, *parent;
               enfant = parent = 0;

               if( startItems.first()->parentItem() != 0 ) {
                    enfant =  static_cast<AncreItem*>( startItems.first()->parentItem() );
               }

               else {
                    enfant = static_cast<AncreItem*>( startItems.first() );
               }


               if( endItems.first()->parentItem() != 0 &&
                   !qgraphicsitem_cast<PictoCondition*>( endItems.first()->parentItem() )
                   && !qgraphicsitem_cast<PictoConditionMultiple*>( endItems.first()->parentItem() ) ) {

                    parent = static_cast<AncreItem*>( endItems.first()->parentItem() );

               } else if( !qgraphicsitem_cast<PictoCondition*>( endItems.first() )
                          && !qgraphicsitem_cast<PictoConditionMultiple*>( endItems.first() ) ) {

                    parent = static_cast<AncreItem*>( endItems.first() );
               }

               if( ( parent != 0 ) && ( enfant != parent ) ) {
                    enfant->setParent( parent );
               }

          }

     }


     if( ( mode_ != EditLink ) && ( mode_ != MoveItem ) ) {

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
     }

     QGraphicsScene::mouseReleaseEvent( mouseEvent );
}/*}}}*/
