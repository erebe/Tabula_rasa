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
#include "ViewModel/DictionaryTableViewModel.hpp"
#include "Model/Algorithm.hpp"
#include "Pictogramme/pictogramme.hpp"
#include "XML/AlgorithmParser.hpp"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QFileDialog>
#include <QtSvg/QSvgGenerator>
#include <QPrinter>
#include <QTabWidget>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QToolBar>

TabWidget::TabWidget(Algorithm *algorithm)
{/*{{{*/
     scene_ = new AlgorithmeScene( algorithm, 0, 0, 2000, 2000, this );
     scene_->setBackgroundBrush( Qt::white );
     connect( scene_, SIGNAL( algorithmeChanged() ), this, SLOT( changeHappened() ) );

     vue_ = new QGraphicsView( this );
     vue_->setResizeAnchor( QGraphicsView::NoAnchor );
     vue_->setTransformationAnchor( QGraphicsView::NoAnchor );
     vue_->setRenderHint( QPainter::Antialiasing );
     vue_->setFont( QFont( "times", 10 ) );
     vue_->setScene( scene_ );

     // construct the dock that will be used to display the dictionary corresponding to this algorithm
     dictionaryDock_ = new QDockWidget(tr("Dictionnaire des éléments"), this);
     dictionaryDock_->setFeatures(QDockWidget::DockWidgetClosable);
     dictionaryDock_->setAllowedAreas(Qt::BottomDockWidgetArea);

     // the child of a dock must be a widget, so create this fake one
     QWidget *fakeWidget = new QWidget(dictionaryDock_);
     QHBoxLayout *dictionaryLayout = new QHBoxLayout(fakeWidget);

     QToolBar *dictionaryToolbar = new QToolBar(fakeWidget);
     dictionaryToolbar->setOrientation(Qt::Vertical);
     dictionaryToolbar->addAction(QIcon(":/Icones/add.png"), "Add row", this, SLOT(addNewRow()));
     dictionaryLayout->addWidget(dictionaryToolbar);

     QTableView *dictionaryView = new QTableView(fakeWidget);
     this->dictionaryViewModel = new DictionaryTableViewModel(scene_->algorithm()->dictionary());
     dictionaryView->setModel(this->dictionaryViewModel);
     dictionaryView->setSelectionMode(QTableView::SingleSelection);
     dictionaryView->setEditTriggers(QTableView::SelectedClicked | QTableView::DoubleClicked);
     dictionaryView->setMinimumHeight(70);
     dictionaryView->horizontalHeader()->setStretchLastSection(true);
     dictionaryLayout->addWidget(dictionaryView);

     fakeWidget->setLayout(dictionaryLayout);
     dictionaryDock_->setWidget(fakeWidget);

     layout_ = new QHBoxLayout(this);
     layout_->addWidget( vue_ );
     layout_->setMargin( 0 );

     svgPath_ = "algorithme.svg";
     pngPath_ = "algorithme.png";
     pdfPath_ = "algorithme.pdf";
     tbrPath_ = "";

}/*}}}*/

void TabWidget::addNewRow()
{
    dictionaryViewModel->appendEmptyEntryRow();
}

void TabWidget::exportToSvg()
{/*{{{*/


     QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                       svgPath_, "Fichiers SVG (*.svg)" );

     if( fichier.isEmpty() ) {
          return;
     }

     svgPath_ = fichier;

     QRectF sceneSize = scene()->sceneRect();
     scene()->adjust( 10 );

     QSvgGenerator generator;
     generator.setFileName( fichier );
     generator.setSize( QSize( scene()->width(), scene()->height() ) );
     generator.setViewBox( QRect( 0, 0, scene()->width(), scene()->height() ) );

     QPainter painter( &generator );
     scene()->clearSelection();
     scene()->render( &painter );

     scene()->setSceneRect( sceneSize );

}/*}}}*/


void TabWidget::exportToPng()
{/*{{{*/

     QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                       pngPath_, "Images (*.png *.gif *.jpg *.jpeg)" );

     if( fichier.isEmpty() ) {
          return;
     }

     pngPath_ = fichier;

     QRectF sceneSize = scene()->sceneRect();
     scene()->adjust( 50 );

     QPixmap image( scene()->width(), scene()->height() );
     QPainter painter( &image );
     painter.setRenderHint( QPainter::Antialiasing );

     scene()->clearSelection();
     scene()->render( &painter );

     image.save( fichier );
     scene()->setSceneRect( sceneSize );


}/*}}}*/

void TabWidget::exportToPrinter( QPrinter* printer, int delta )
{/*{{{*/

     QRectF sceneSize = scene()->sceneRect();
     scene()->adjust( delta );

     QPainter painter( printer );
     painter.setRenderHint( QPainter::Antialiasing );

     QFont font = scene()->font();
     font.setPixelSize( 10 );
     painter.setFont(  font );


     scene()->clearSelection();
     scene()->render( &painter );
     scene()->setSceneRect( sceneSize );


}/*}}}*/

void TabWidget::exportToPdf()
{/*{{{*/

     QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                       pdfPath_, "Pdf (*.pdf)" );

     if( fichier.isEmpty() ) {
          return;
     }

     pdfPath_ = fichier;

     QRectF sceneSize = scene()->sceneRect();
     scene()->adjust( 10 );


     QPrinter* printer = new QPrinter( QPrinter::HighResolution );
     printer->setOutputFormat( QPrinter::PdfFormat );
     printer->setOrientation( QPrinter::Portrait );

     printer->setPaperSize( QSizeF( scene()->width(), scene()->height() ),
                            QPrinter::Point );
     printer->setOutputFileName( fichier );
     printer->setPageMargins( 0, 0, 0, 0, QPrinter::Point );

     scene()->setSceneRect( sceneSize );
     exportToPrinter( printer, 0 );
     delete printer;
}/*}}}*/

void TabWidget::save()
{/*{{{*/

     if( tbrPath_.isEmpty() ) {

          QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                            QString( scene()->name() + ".tbr" ), "Tabula Rasa (*.tbr *.xml  )" );

          if( fichier.isEmpty() ) {
               return;
          }

          tbrPath_ = fichier;
     }

     QFile file( tbrPath_ );

     if ( !file.open( QIODevice::Truncate | QIODevice::WriteOnly ) )
          { return; }

     QTextStream out( &file );

     scene()->saveToXml( out );
     file.close();

     QTabWidget* tab = static_cast<QTabWidget*>( this->parent()->parent() );
     tab->setTabText( tab->currentIndex(), scene()->name() );

}/*}}}*/

void TabWidget::saveAs()
{/*{{{*/

     tbrPath_.clear();
     save();

}/*}}}*/

void TabWidget::changeHappened()
{/*{{{*/

     QTabWidget* tab = static_cast<QTabWidget*>( this->parent()->parent() );
     tab->setTabText( tab->currentIndex(), scene()->name() + '*' );
}/*}}}*/
