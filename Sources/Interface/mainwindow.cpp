/*
 * =====================================================================================
 *
 *       Filename:  mainwindow.cpp
 *
 *    Description:  Tabula Rasa : Implementation de la classe gérant l'interface
 *
 *        Version:  1.0
 *        Created:  15/08/2011 02:20:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "tabWidget.hpp"
#include "resizeDialog.hpp"
#include "aboutDialog.hpp"
#include "Pictogramme/labelItem.hpp"
#include "Pictogramme/pictogramme.hpp"
#include "Pictogramme/liaisonItem.hpp"

#include <QFileDialog>
#include <QtGui>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
MainWindow::MainWindow( QWidget* parent )
     : QMainWindow( parent ), ui( new Ui::MainWindow )
{/*{{{*/
     ui->setupUi( this );
     createNewTab();
     connect( ui->actionA_propos_de_Qt, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );
     connect( ui->actionQuitter, SIGNAL( triggered() ), qApp, SLOT( quit() ) );
}/*}}}*/

MainWindow::~MainWindow()
{/*{{{*/
     delete ui;

     for( int i = 0; i < ui->tabWidget->count(); i++ ) {
          delete ui->tabWidget->widget( i );
     }
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Methodes privées
 *-----------------------------------------------------------------------------*/
void MainWindow::selectQAction( AlgorithmeScene::Mode mode )
{/*{{{*/
     AlgorithmeScene* scene = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                              ->scene();
     scene->setMode( mode );

     if( mode != AlgorithmeScene::InsertAction ) {
          ui->actionAction->setChecked( false );
     }

     if( mode != AlgorithmeScene::InsertLoop ) {
          ui->actionIteration->setChecked( false );
     }

     if( mode != AlgorithmeScene::InsertProcedure ) {
          ui->actionProcedure->setChecked( false );
     }

     if( mode != AlgorithmeScene::InsertCondition ) {
          ui->actionCondition->setChecked( false );
     }

     if( mode != AlgorithmeScene::EditLink ) {
          ui->actionMode_Edition->setChecked( false );
     }

     if( mode != AlgorithmeScene::MoveItem ) {
          ui->actionMode_Insertion->setChecked( false );
     }

     if( mode != AlgorithmeScene::InsertMultiCondition ) {
          ui->actionConditionMultiple->setChecked( false );
     }

     if ( mode != AlgorithmeScene::InsertExit ) {
          ui->actionSortie->setChecked( false );
     }
}/*}}}*/

TabWidget* MainWindow::createNewTab( QString name )
{/*{{{*/
     TabWidget* tab = new TabWidget();
     connect( tab->scene(), SIGNAL( modeChanged( AlgorithmeScene::Mode ) ), this, SLOT( setMode( AlgorithmeScene::Mode ) ) );
     connect( tab->scene(), SIGNAL( itemAdded( Pictogramme* ) ), this, SLOT( itemAdded( Pictogramme* ) ) );
     connect( tab->scene(), SIGNAL( liaisonError() ), this, SLOT( liaisonError() ) );

     ui->tabWidget->addTab( tab, name );
     ui->tabWidget->setCurrentWidget( tab );
     return tab;
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Slots des actions de la barre de droite
 *-----------------------------------------------------------------------------*/
void MainWindow::on_actionMode_Edition_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::EditLink );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionMode_Insertion_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::MoveItem );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionAction_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::InsertAction );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionIteration_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::InsertLoop );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionProcedure_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::InsertProcedure );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionCondition_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::InsertCondition );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionConditionMultiple_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::InsertMultiCondition );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/

void MainWindow::on_actionSortie_triggered( bool checked )
{/*{{{*/
     if( checked ) {
          selectQAction( AlgorithmeScene::InsertExit );

     } else {
          selectQAction( AlgorithmeScene::MoveItem );
     }
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Slots pour l'interface
 *-----------------------------------------------------------------------------*/
void MainWindow::on_tabWidget_tabCloseRequested( int index )
{/*{{{*/
     if ( QMessageBox::question( this, tr( "Fermer l'onglet ?" ),
                                 tr( "Voulez-vous vraiment fermer l'onglet ?" ),
                                 QMessageBox::Yes | QMessageBox::No ) == QMessageBox::Yes ) {
          delete ui->tabWidget->widget( index );

          if( ui->tabWidget->count() == 0 ) {
               createNewTab();
          }
     }
}/*}}}*/

void MainWindow::on_actionNouveau_triggered()
{/*{{{*/
     bool ok;
     QString name = QInputDialog::getText( this, tr( "Titre de l'agorithme" ),
                                           tr( "Quel est le titre de l'algorithme ?" ),
                                           QLineEdit::Normal, "", &ok );

     if( !ok ) {
          return;
     }

     createNewTab( name );
}/*}}}*/

void MainWindow::on_actionExporter_vers_une_image_triggered()
{/*{{{*/
     QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                       QString( "algo.png" ), "Images (*.png *.gif *.jpg *.jpeg)" );

     if( fichier.isEmpty() ) {
          return;
     }

     AlgorithmeScene* scene = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                              ->scene();
     qreal maxX, maxY, minX, minY;
     maxX = maxY = 0;
     minX = scene->width();
     minY = scene->height();
     QGraphicsItem* item;
     QPointF point;
     foreach( item, scene->items() ) {
          if( qgraphicsitem_cast<LiaisonItem*>( item ) ) {
               continue;
          }

          point = item->scenePos();

          if( maxX < ( point.x() + static_cast<Pictogramme*>( item )->width() ) ) {
               maxX = point.x() + static_cast<Pictogramme*>( item )->width();
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
     QRectF sceneSize = scene->sceneRect();
     scene->setSceneRect( minX - 50, minY - 50, maxX - minX + 100, maxY - minY + 150 );
     QPixmap image( scene->width(), scene->height() );
     QPainter painter( &image );
     painter.setRenderHint( QPainter::Antialiasing );
     scene->clearSelection();
     scene->render( &painter );
     image.save( fichier );
     scene->setSceneRect( sceneSize );
}/*}}}*/

void MainWindow::on_actionRenommer_l_algorithme_triggered()
{/*{{{*/
     bool ok;
     QString titre = QInputDialog::getText( this, tr( "Titre de l'agorithme" ), tr( "Quel est le titre de l'algorithme ?" ), QLineEdit::Normal,
                                            ui->tabWidget->tabText( ui->tabWidget->currentIndex() ), &ok );

     if( !ok ) {
          return;
     }

     ui->tabWidget->setTabText( ui->tabWidget->currentIndex(), titre );
     static_cast<TabWidget*>( ui->tabWidget->currentWidget() )->scene()->setName( titre );
}/*}}}*/

void MainWindow::on_actionFermer_l_onglet_triggered()
{/*{{{*/
     on_tabWidget_tabCloseRequested( ui->tabWidget->currentIndex() );
}/*}}}*/

void MainWindow::on_actionRedimensionner_l_Algorithme_triggered()
{/*{{{*/
     AlgorithmeScene* scene = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                              ->scene();
     dialog = new ResizeDialog( scene->sceneRect().width(),
                                scene->sceneRect().height(),
                                this );
     dialog->show();
     connect( dialog, SIGNAL( requestSizeChange( int, int ) ), this, SLOT( resizeScene( int, int ) ) );
}/*}}}*/

void MainWindow::on_actionA_propos_de_Tabula_Rasa_triggered()
{/*{{{*/
     about_ = new AboutDialog( this );
     about_->exec();
     delete about_;
}/*}}}*/

void MainWindow::on_actionImprimer_triggered()
{/*{{{*/
     QPrinter printer( QPrinter::HighResolution );
     QPrintPreviewDialog  preview( &printer, this );
     connect( &preview, SIGNAL( paintRequested( QPrinter* ) ), SLOT( print( QPrinter* ) ) );
     preview.exec();
}/*}}}*/

void MainWindow::on_actionEnregistrer_triggered()
{/*{{{*/
     QString fichier = QFileDialog::getSaveFileName( this, "Enregistrer l'algorithme",
                       QString( "algo.tbr" ), "Tabula Rasa (*.tbr *.xml  )" );

     if( fichier.isEmpty() ) {
          return;
     }

     QFile file( fichier );

     if ( !file.open( QIODevice::Truncate | QIODevice::WriteOnly ) )
          { return; }

     QTextStream out( &file );
     AlgorithmeScene* scene = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                              ->scene();
     scene->saveToXml( out );
     file.close();
}/*}}}*/

void MainWindow::on_actionOuvrir_triggered()
{/*{{{*/
     QString fichier = QFileDialog::getOpenFileName( this, tr( "Sélectionner un fichier à ouvrir" ), QString(),
                       "Tabula Rasa (*.tbr *.xml)" );
     QFile file( fichier );

     if( !file.open( QIODevice::ReadOnly ) )
          { return; }

     QDomDocument doc;

     if( !doc.setContent( &file ) ) {
          file.close();
          return;
     }

     QDomElement racine = doc.documentElement();
     QString name = racine.firstChildElement( "nom" ).firstChild().toText().data();
     TabWidget* tab = createNewTab( name );
     tab->scene()->loadFromXml( doc );
     file.close();
     setMode( AlgorithmeScene::MoveItem );
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Slots divers
 *-----------------------------------------------------------------------------*/

void MainWindow::resizeScene( int width, int height )
{/*{{{*/
     AlgorithmeScene* scene = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                              ->scene();
     QGraphicsView* view = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                           ->view();
     width = ( width < view->width() ) ? view->width() : width;
     height = ( height < view->height() ) ? view->height() : height;
     scene->setSceneRect( 0, 0, width, height );
     delete dialog;
     dialog = 0;
}/*}}}*/

void MainWindow::setMode( AlgorithmeScene::Mode mode )
{/*{{{*/
     if( mode == AlgorithmeScene::MoveItem ) {
          ui->actionMode_Insertion->setChecked( true );
     }

     selectQAction( mode );
}/*}}}*/

void MainWindow::print( QPrinter* printer )
{/*{{{*/
     AlgorithmeScene* scene = static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
                              ->scene();
     qreal maxX, maxY, minX, minY;
     maxX = maxY = 0;
     minX = scene->width();
     minY = scene->height();
     QGraphicsItem* item;
     QPointF point;
     foreach( item, scene->items() ) {
          if( qgraphicsitem_cast<LiaisonItem*>( item ) ) {
               continue;
          }

          point = item->scenePos();

          if( maxX < ( point.x() + static_cast<Pictogramme*>( item )->width() ) ) {
               maxX = point.x() + static_cast<Pictogramme*>( item )->width();
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
     QRectF sceneSize = scene->sceneRect();
     scene->setSceneRect( minX - 50, minY - 50, maxX - minX + 100, maxY - minY + 150 );
     QPainter painter( printer );
     painter.setRenderHint( QPainter::Antialiasing );
     QFont font = painter.font();
     font.setPixelSize( ( printer->pageRect().width() + printer->pageRect().height() ) / 2000 );
     painter.setFont( font );
     scene->clearSelection();
     scene->render( &painter );
     scene->setSceneRect( sceneSize );
}/*}}}*/

void MainWindow::itemAdded( Pictogramme* item )
{/*{{{*/
     connect( item, SIGNAL( doubleClick( LabelItem* ) ),
              this, SLOT( changeLabel( LabelItem* ) ) );
}/*}}}*/

void MainWindow::changeLabel( LabelItem* item )
{/*{{{*/
     bool ok;
     QString test = QInputDialog::getText( this, "Changer le label", "Nouvel intitulé",
                                           QLineEdit::Normal, item->label(), &ok );

     if( ok ) {
          item->setLabel( test );
     }
}/*}}}*/

void MainWindow::liaisonError()
{/*{{{*/

     QMessageBox::critical( this, tr( "Liaison impossible" ), tr( "Désolé mais vous ne pouvez relier ces deux éléments" ) );

}/*}}}*/
