#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Pictogramme/pictoSortie.hpp"
#include "algorithmeScene.hpp"

#include <QFileDialog>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action_Ouvrir->setIcon( QApplication::style()->standardIcon(
                                   QStyle::SP_DialogOpenButton ) );

    ui->actionEnregistrer->setIcon( QApplication::style()->standardIcon(
                                 QStyle::SP_DialogSaveButton ) );

    scene_ = new AlgorithmeScene( 0, 0, 2000, 2000, this );
    connect( scene_, SIGNAL(modeChanged(AlgorithmeScene::Mode)), this, SLOT(setMode(AlgorithmeScene::Mode)));
    scene_->setBackgroundBrush( Qt::white );
    ui->graphicsView->setScene( scene_ );
    scene_->setFont( QFont( "Cantarell,11,-1,5,50,0,0,0,0,0" ) );

    ui->graphicsView->setResizeAnchor( QGraphicsView::NoAnchor );
    ui->graphicsView->setTransformationAnchor( QGraphicsView::NoAnchor );
    ui->graphicsView->setRenderHint( QPainter::Antialiasing );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene_;
}

void MainWindow::on_action_Ouvrir_triggered(){

        static_cast<AlgorithmeScene*>(ui->graphicsView->scene())->setMode( AlgorithmeScene::EditLink );

}

void MainWindow::on_actionMode_Edition_triggered( bool checked ){
        if( checked )
                selectQAction( AlgorithmeScene::EditLink );
        else
                selectQAction( AlgorithmeScene::MoveItem );

}


void MainWindow::on_actionMode_Insertion_triggered( bool checked ){
        if( checked )
                selectQAction( AlgorithmeScene::MoveItem );
        else
                selectQAction( AlgorithmeScene::MoveItem );
}

void MainWindow::on_actionAction_triggered( bool checked ){
        if( checked )
                selectQAction( AlgorithmeScene::InsertAction );
        else
                selectQAction( AlgorithmeScene::MoveItem );

}

void MainWindow::on_actionIteration_triggered( bool checked ){
        if( checked )
                selectQAction( AlgorithmeScene::InsertLoop );
        else
                selectQAction( AlgorithmeScene::MoveItem );
}

void MainWindow::on_actionProcedure_triggered( bool checked ){
        if( checked )
                selectQAction( AlgorithmeScene::InsertProcedure );
        else
                selectQAction( AlgorithmeScene::MoveItem );
}

void MainWindow::on_actionCondition_triggered( bool checked ){
        if( checked )
                selectQAction( AlgorithmeScene::InsertCondition );
        else
                selectQAction( AlgorithmeScene::MoveItem );
}

void MainWindow::on_actionConditionMultiple_triggered( bool checked ){
    if( checked )
            selectQAction( AlgorithmeScene::InsertMultiCondition );
    else
            selectQAction( AlgorithmeScene::MoveItem );

}

void MainWindow::on_actionSortie_triggered( bool checked ){
    if( checked )
            selectQAction( AlgorithmeScene::InsertExit );
    else
            selectQAction( AlgorithmeScene::MoveItem );

}


void MainWindow::on_actionEnregistrer_triggered(){


        scene_->setSceneRect(0, 0, 500, 500);
        QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer l'algorithme", QString("algo.png"), "Images (*.png *.gif *.jpg *.jpeg)");
        QPixmap image( scene_->width(), scene_->height() );

        QPainter painter( &image );
        painter.setRenderHint(QPainter::Antialiasing);
        scene_->render( &painter );

        image.save( fichier );
}

void MainWindow::selectQAction( AlgorithmeScene::Mode mode ){

    scene_->setMode( mode );

    if( mode != AlgorithmeScene::InsertAction )
            ui->actionAction->setChecked( false );
    if( mode != AlgorithmeScene::InsertLoop )
            ui->actionIteration->setChecked( false );
    if( mode != AlgorithmeScene::InsertProcedure )
            ui->actionProcedure->setChecked( false );
    if( mode != AlgorithmeScene::InsertCondition )
            ui->actionCondition->setChecked( false );
    if( mode != AlgorithmeScene::EditLink )
            ui->actionMode_Edition->setChecked( false );
    if( mode != AlgorithmeScene::MoveItem )
            ui->actionMode_Insertion->setChecked( false );
    if( mode != AlgorithmeScene::InsertMultiCondition )
            ui->actionConditionMultiple->setChecked( false );
    if ( mode != AlgorithmeScene::InsertExit )
            ui->actionSortie->setChecked( false );
}

void MainWindow::setMode( AlgorithmeScene::Mode mode ){

        if( mode == AlgorithmeScene::MoveItem )
                ui->actionMode_Insertion->setChecked( true );

        selectQAction( mode );
}
