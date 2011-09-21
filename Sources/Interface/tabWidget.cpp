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
#include <QFileDialog>
#include <QtSvg/QSvgGenerator>
#include <QPrinter>


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

     svgPath_ = "algorithme.svg";
     pngPath_ = "algorithme.png";
     pdfPath_ = "algorithme.pdf";

}/*}}}*/


void TabWidget::exportToSvg() {


    QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                        svgPath_, "Fichiers SVG (*.svg)" );

    if( fichier.isEmpty() ) {
         return;
    }
    svgPath_ = QFileInfo( fichier ).path();

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

}


void TabWidget::exportToPng() {

    QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                      pngPath_, "Images (*.png *.gif *.jpg *.jpeg)" );

    if( fichier.isEmpty() ) {
         return;
    }

    pngPath_ = QFileInfo( fichier ).path();

    QRectF sceneSize = scene()->sceneRect();
    scene()->adjust( 50 );

    QPixmap image( scene()->width(), scene()->height() );
    QPainter painter( &image );
    painter.setRenderHint( QPainter::Antialiasing );

    scene()->clearSelection();
    scene()->render( &painter );

    image.save( fichier );
    scene()->setSceneRect( sceneSize );


}

void TabWidget::exportToPrinter( QPrinter* printer ) {

         QRectF sceneSize = scene()->sceneRect();
         scene()->adjust( 50 );

         QPainter painter( printer );
         painter.setRenderHint( QPainter::Antialiasing );

         QFont font = scene()->font();
         font.setPixelSize( 10 );
         painter.setFont(  font );


         scene()->clearSelection();
         scene()->render( &painter );
         scene()->setSceneRect( sceneSize );


}

void TabWidget::exportToPdf() {

    QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                      pdfPath_, "Pdf (*.pdf)" );

    if( fichier.isEmpty() ) {
         return;
    }

    pdfPath_ = QFileInfo( fichier ).path();

    QPrinter* printer = new QPrinter( QPrinter::HighResolution );
    printer->setOutputFormat( QPrinter::PdfFormat );
    printer->setOrientation( QPrinter::Portrait );
    printer->setPaperSize( QSizeF( scene()->width(), scene()->height() ),
                           QPrinter::Point );
    printer->setOutputFileName( fichier );
    printer->setPageMargins( 0, 0, 0, 0, QPrinter::Point );


    exportToPrinter( printer );
    delete printer;
}

void TabWidget::save() {

    if( tbrPath_.isEmpty() ){

        QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                      QString( "algo.tbr" ), "Tabula Rasa (*.tbr *.xml  )" );

        if( fichier.isEmpty() ) {
             return;
        }

        tbrPath_ = QFileInfo( fichier ).path();
   }
    QFile file( tbrPath_ );

    if ( !file.open( QIODevice::Truncate | QIODevice::WriteOnly ) )
         { return; }

    QTextStream out( &file );

    scene()->saveToXml( out );
    file.close();

}

void TabWidget::saveAs() {

    QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                  QString( "algo.tbr" ), "Tabula Rasa (*.tbr *.xml  )" );

    if( fichier.isEmpty() ) {
         return;
    }

    tbrPath_ = fichier;
    QFile file( tbrPath_ );

    if ( !file.open( QIODevice::Truncate | QIODevice::WriteOnly ) )
         { return; }

    QTextStream out( &file );

    scene()->saveToXml( out );
    file.close();

}
