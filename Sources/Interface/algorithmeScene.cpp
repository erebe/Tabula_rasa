#include "algorithmeScene.hpp"
#include "Pictogramme/ancreItem.hpp"
#include "Pictogramme/pictoCondition.hpp"
#include "Pictogramme/pictoAction.hpp"
#include "Pictogramme/pictoIteration.hpp"
#include "Pictogramme/pictoProcedure.hpp"
#include "Pictogramme/pictoSortie.hpp"
#include "Pictogramme/pictoConditionMultiple.hpp"

#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>

AlgorithmeScene::AlgorithmeScene( qreal x, qreal y, qreal width, qreal height, QObject * parent ):
        QGraphicsScene( x, y, width, height, parent ), mode_(MoveItem), line_(0)
{
}

AlgorithmeScene::~AlgorithmeScene(){

        Pictogramme* picto;

        foreach( picto, items_)
                delete picto;

}



void AlgorithmeScene::mousePressEvent( QGraphicsSceneMouseEvent *mouseEvent )
{

    mouseEvent->accept();

    if ( mouseEvent->button() == Qt::LeftButton && mode_ == EditLink ){

        line_ = new QGraphicsLineItem( QLineF( mouseEvent->scenePos(),
                                               mouseEvent->scenePos() ) );

        QGraphicsScene::addItem(line_);
    }

    QGraphicsScene::mousePressEvent( mouseEvent );

}


void AlgorithmeScene::mouseMoveEvent( QGraphicsSceneMouseEvent *mouseEvent ){

    mouseEvent->accept();

    if ( mode_ == EditLink && line_ != 0 ) {
        QLineF newLine( line_->line().p1(), mouseEvent->scenePos() );
        line_->setLine( newLine );

    } else if ( mode_ == MoveItem ) {
        QGraphicsScene::mouseMoveEvent( mouseEvent );
    }

}


void AlgorithmeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent *mouseEvent ){

        mouseEvent->accept();

        if( mouseEvent->button() != Qt::LeftButton )
                return;

        if( line_ != 0 && mode_ == EditLink ){

            QList<QGraphicsItem *> startItems = items( line_->line().p1() );
            QList<QGraphicsItem *> endItems = items( line_->line().p2() );

            if( startItems.count() && startItems.first() == line_ )
                startItems.removeFirst();

            if( endItems.count() && endItems.first() == line_ )
                endItems.removeFirst();

            removeItem( line_ );
            delete line_;
            line_ = 0;

            QGraphicsItem* item;

            foreach( item, startItems ){
                if( qgraphicsitem_cast<LiaisonItem*>( item ) )
                        startItems.removeOne( item );
            }

            foreach( item, endItems ){
                if( qgraphicsitem_cast<LiaisonItem*>( item ) )
                        endItems.removeOne( item );
            }


            if( startItems.count() && endItems.count() ){

                   AncreItem *enfant, *parent;
                   enfant = parent = 0;

                   if( startItems.first()->parentItem() != 0 )
                            enfant =  static_cast<AncreItem*>( startItems.first()->parentItem() );
                   else
                            enfant = static_cast<AncreItem*>( startItems.first() );


                  if( endItems.first()->parentItem() != 0 &&
                      !qgraphicsitem_cast<PictoCondition*>( endItems.first()->parentItem() )
                       && !qgraphicsitem_cast<PictoConditionMultiple*>( endItems.first()->parentItem() ) ) {

                         parent = static_cast<AncreItem*>( endItems.first()->parentItem() );

                  }else if( !qgraphicsitem_cast<PictoCondition*>( endItems.first() )
                            && !qgraphicsitem_cast<PictoConditionMultiple*>( endItems.first() ) ){

                          parent = static_cast<AncreItem*>( endItems.first() );
                  }

                    if( (parent != 0) && (enfant != parent) )
                         enfant->setParent( parent );

            }

        }


        if( (mode_ != EditLink) && (mode_ != MoveItem) ){

                Pictogramme* picto = 0;

                if( mode_ == InsertAction ){
                    picto = new PictoAction( "", "", "", 0, this );

                }else if( mode_ == InsertLoop ){
                    picto = new PictoIteration( "", 0, this );

                }else if( mode_ == InsertProcedure ){
                    picto = new PictoProcedure( "", "", "", 0, this );

                }else if( mode_ == InsertCondition ){
                    picto = new PictoCondition( "", 0, this );

                }else if( mode_ == InsertExit ){
                    picto = new PictoSortie( 0, this );

                }else if( mode_ == InsertMultiCondition ){
                    picto = new PictoConditionMultiple("", 0, this );

                }

                if( picto ){
                    QRectF size = picto->boundingRect();

                    picto->setPos( mouseEvent->scenePos().x() - ( size.width() / 2 ),
                                   mouseEvent->scenePos().y() - ( size.height() / 2) );
                    picto->update();
                    connect( picto, SIGNAL(doubleClick( LabelItem* )),
                             this->parent(), SLOT(changeLabel( LabelItem* )) );

                    items_.push_back( picto );
                    update();

                    if( mouseEvent->modifiers() != Qt::ControlModifier ){
                        setMode( AlgorithmeScene::MoveItem );
                        emit modeChanged( AlgorithmeScene::MoveItem );
                    }


                }
        }

        QGraphicsScene::mouseReleaseEvent( mouseEvent );
}

void AlgorithmeScene::deleteItem( Pictogramme* item ){

        items_.removeOne( item );
        removeItem( item );
        delete item;
}
