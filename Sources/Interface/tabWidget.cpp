/*
 * =====================================================================================
 *
 *       Filename:  tabWidget.cpp
 *
 *    Description:  Tabula Rasa : Implementation d'un onglet
 *
 *        Version:  1.0
 *        Created:  16/08/2011 03:43:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "tabWidget.hpp"
#include "Algorithme/algorithmeScene.hpp"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>

TabWidget::TabWidget()
{/*{{{*/
     scene_ = new AlgorithmeScene( 0, 0, 2000, 2000, this );
     scene_->setBackgroundBrush( Qt::white );

     vue_ = new QGraphicsView( this );
     vue_->setResizeAnchor( QGraphicsView::NoAnchor );
     vue_->setTransformationAnchor( QGraphicsView::NoAnchor );
     vue_->setRenderHint( QPainter::Antialiasing );
     vue_->setFont( QFont( "times", 10 ) );
     vue_->setScene( scene_ );

     layout_ = new QHBoxLayout( this );
     layout_->addWidget( vue_ );
     layout_->setMargin( 0 );
}/*}}}*/
