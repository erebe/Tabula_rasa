#include "sauvegarde.hpp"
#include "ui_sauvegarde.h"
#include <QStandardItemModel>
#include <QAbstractButton>
#include <QPushButton>
#include <QDebug>

Sauvegarde::Sauvegarde( QList< QPair<QString, bool> >& algos, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::Sauvegarde), algos_( algos )
{
    ui->setupUi(this);

    QStandardItemModel* liste = new QStandardItemModel( this );

     for( QList< QPair<QString, bool> >::const_iterator it = algos.constBegin();
          it != algos.constEnd(); it++ ) {

                QStandardItem* item = new QStandardItem( it->first );
                item->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
                if( it->second )
                        item->setData( QVariant( Qt::Checked ), Qt::CheckStateRole );
                else
                        item->setData( QVariant( Qt::Unchecked ), Qt::CheckStateRole );

                liste->appendRow( item );
    }

    ui->listView->setModel( liste );

    QStandardItemModel* items =  static_cast<QStandardItemModel*>(ui->listView->model());

    for( int i = 0; i < items->rowCount(); i++ ) {

            if( items->item(i)->checkState() == 0 ) {
                    ui->listView->setRowHidden( i , true );
            }
    }


    QAbstractButton* button =  ui->buttonBox->button(QDialogButtonBox::Discard);
    connect( button, SIGNAL(clicked()),
             this, SLOT( clickDiscard() ) );

    button = ui->buttonBox->button(QDialogButtonBox::Save);
    connect( button, SIGNAL(clicked()),
             this, SLOT( clickSave() ) );
}

Sauvegarde::~Sauvegarde()
{
    delete ui;
}

void Sauvegarde::clickDiscard( ) {

        done(-1);
}

void Sauvegarde::clickSave() {

    QStandardItemModel* items =  static_cast<QStandardItemModel*>( ui->listView->model() );

    for( int i = 0; i < items->rowCount(); i++ ) {

            if( items->item(i)->checkState() == 0 ) {
                    algos_.replace( i , qMakePair( algos_.at( i ).first, false ) );
            }
    }

}
