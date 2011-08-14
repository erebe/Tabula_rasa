#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QInputDialog>
#include "Pictogramme/labelItem.hpp"
#include "algorithmeScene.hpp"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AlgorithmeScene* scene_;
    void selectQAction( AlgorithmeScene::Mode mode );

private slots:
    void on_action_Ouvrir_triggered();
    void on_actionMode_Edition_triggered( bool checked );
    void on_actionMode_Insertion_triggered( bool checked );
    void on_actionEnregistrer_triggered();
    void on_actionAction_triggered( bool checked );
    void on_actionIteration_triggered( bool checked );
    void on_actionProcedure_triggered( bool checked );
    void on_actionCondition_triggered( bool checked );
    void on_actionConditionMultiple_triggered( bool checked );
    void on_actionSortie_triggered( bool checked );

public slots:
    void setMode( AlgorithmeScene::Mode mode );

    void changeLabel( LabelItem* item ){

        bool ok;
        QString test = QInputDialog::getText( this, "Changer le label", "Nouvel intitulé", QLineEdit::Normal, item->label(), &ok );

        if( ok )
                item->setLabel( test );

    }

};

#endif // MAINWINDOW_HPP
