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
#include "Algorithme/Pictogramme/labelItem.hpp"
#include "Algorithme/Pictogramme/pictogramme.hpp"
#include "Algorithme/Pictogramme/liaisonItem.hpp"
#include "labeledit.hpp"
#include "sauvegarde.hpp"

#include <QFileDialog>
#include <QtGui>
#include <QtSvg/QSvgGenerator>


/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
MainWindow::MainWindow( QWidget* parent )
     : QMainWindow( parent ), ui( new Ui::MainWindow )
{/*{{{*/
     ui->setupUi( this );
     createNewTab();
     connect( ui->actionA_propos_de_Qt, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );
     //connect( ui->actionQuitter, SIGNAL( triggered() ), qApp, SLOT( quit() ) );
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
     tab->scene()->setName( name );
     connect( tab->scene(), SIGNAL( modeChanged( AlgorithmeScene::Mode ) ), this, SLOT( setMode( AlgorithmeScene::Mode ) ) );
     connect( tab->scene(), SIGNAL( itemAdded( Pictogramme* ) ), this, SLOT( itemAdded( Pictogramme* ) ) );
     connect( tab->scene(), SIGNAL( liaisonError() ), this, SLOT( liaisonError() ) );

     ui->tabWidget->addTab( tab, name );
     ui->tabWidget->setCurrentWidget( tab );

     return tab;
}/*}}}*/

void MainWindow::setDisabled( bool state )
{/*{{{*/

     ui->actionAction->setDisabled( state );
     ui->actionCondition->setDisabled( state );
     ui->actionConditionMultiple->setDisabled( state );
     ui->actionEnregistrer->setDisabled( state );
     ui->actionExporter_en_PDF->setDisabled( state );
     ui->actionExporter_SVG->setDisabled( state );
     ui->actionExporter_vers_une_image->setDisabled( state );
     ui->actionFermer_l_onglet->setDisabled( state );
     ui->actionImprimer->setDisabled( state );
     ui->actionIteration->setDisabled( state );
     ui->actionMode_Edition->setDisabled( state );
     ui->actionMode_Insertion->setDisabled( state );
     ui->actionProcedure->setDisabled( state );
     ui->actionRedimensionner_l_Algorithme->setDisabled( state );
     ui->actionRenommer_l_algorithme->setDisabled( state );
     ui->actionSauvegarder_sous->setDisabled( state );
     ui->actionSortie->setDisabled( state );
     ui->actionTout_s_lectionner->setDisabled( state );

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
     int reponse = QMessageBox::Discard;
     QChar c = ui->tabWidget->tabText( index )
               .at( ui->tabWidget->tabText( index ).size() - 1 );


     if( c == '*' ) {

          QString name = static_cast<TabWidget*>( ui->tabWidget->widget( index ) )->scene()->name();

          reponse = QMessageBox::question( this, tr( "Fermer l'onglet ?" ),
                                           tr( "Voulez-vous vraiment fermer \"" ) + name + tr( "\" ?" ),
                                           QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
     }

     if( reponse == QMessageBox::Save ) {
          on_actionEnregistrer_triggered( index );
     }

     if( reponse != QMessageBox::Cancel ) {

          delete ui->tabWidget->widget( index );

          if( ui->tabWidget->count() == 0 ) {
               setDisabled( true );
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
     setDisabled( false );
}/*}}}*/

void MainWindow::on_actionExporter_vers_une_image_triggered()
{/*{{{*/

     TabWidget* tab = static_cast<TabWidget*>( ui->tabWidget->currentWidget() );
     tab->exportToPng();

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

void MainWindow::on_actionEnregistrer_triggered( int i )
{/*{{{*/
     TabWidget* tab;

     if( i == -1 ) {
          tab = static_cast<TabWidget*>( ui->tabWidget->currentWidget() );

     } else {
          tab = static_cast<TabWidget*>( ui->tabWidget->widget( i ) );
     }

     tab->save();

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
     tab->setTbrPath( fichier );
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
     TabWidget* tab = static_cast<TabWidget*>( ui->tabWidget->currentWidget() );
     tab->exportToPrinter( printer );
}/*}}}*/

void MainWindow::itemAdded( Pictogramme* item )
{/*{{{*/
     connect( item, SIGNAL( doubleClick( LabelItem* ) ),
              this, SLOT( changeLabel( LabelItem* ) ) );
}/*}}}*/

void MainWindow::changeLabel( LabelItem* item )
{/*{{{*/

     LabelEdit tmp( this, item->label() );

     if( tmp.exec() == QDialog::Accepted ) {
          item->setLabel( tmp.label() );
     }
}/*}}}*/

void MainWindow::liaisonError()
{/*{{{*/

     QMessageBox::critical( this, tr( "Liaison impossible" ), tr( "Désolé mais vous ne pouvez relier ces deux éléments" ) );

}/*}}}*/

void MainWindow::on_actionTout_s_lectionner_triggered()
{/*{{{*/
     static_cast<TabWidget*>( ui->tabWidget->currentWidget() )
     ->scene()->selectAll();
}/*}}}*/

void MainWindow::on_actionExporter_SVG_triggered()
{/*{{{*/

     TabWidget* tab = static_cast<TabWidget*>( ui->tabWidget->currentWidget() );
     tab->exportToSvg();

}/*}}}*/

void MainWindow::on_actionExporter_en_PDF_triggered()
{/*{{{*/
     TabWidget* tab = static_cast<TabWidget*>( ui->tabWidget->currentWidget() );
     tab->exportToPdf();
}/*}}}*/

void MainWindow::on_actionSauvegarder_sous_triggered()
{/*{{{*/
     TabWidget* tab = static_cast<TabWidget*>( ui->tabWidget->currentWidget() );
     tab->saveAs();
}/*}}}*/

void MainWindow::on_actionQuitter_triggered()
{/*{{{*/
     QList< QPair<QString, bool> > algos;
     int ASauvegarder = 0;

     for( int i = 0; i < ui->tabWidget->count(); i++ ) {
          const QString& tabText = ui->tabWidget->tabText( i );

          if( tabText.at( tabText.size() - 1 ) == '*' ) {
               algos << QPair<QString, bool>( static_cast<TabWidget*>( ui->tabWidget->widget( i ) )
                                              ->scene()->name(), true );
               ASauvegarder++;

          } else {
               algos << QPair<QString, bool>( static_cast<TabWidget*>( ui->tabWidget->widget( i ) )
                                              ->scene()->name(), false );
          }

     }

     if( ASauvegarder == 0 )
          { qApp->quit(); }


     Sauvegarde fenetreSauvegarde( algos , this );
     int action = fenetreSauvegarde.exec();

     if( action == -1 ) {
          qApp->quit();

     } else if( action == 1 ) {

          for( int i = 0; i < algos.size(); i++ ) {

               if( algos.at( i ).second ) {

                    on_actionEnregistrer_triggered( i );
               }
          }

          qApp->quit();
     }


}/*}}}*/
