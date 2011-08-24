/*
 * =====================================================================================
 *
 *       Filename:  resizeDialog.cpp
 *
 *    Description:  Tabula Rasa : Implémentation de la boite de Dialogue
 *
 *        Version:  1.0
 *        Created:  16/08/2011 10:29:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "resizeDialog.hpp"
#include "ui_resizeDialog.h"

ResizeDialog::ResizeDialog( int width, int height, QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::ResizeDialog )
{
    ui->setupUi( this );
    ui->largeurSpinBox->setValue( width );
    ui->hauteurSpinBox->setValue( height );
}

ResizeDialog::~ResizeDialog()
{
    delete ui;
    destroy( true );
}

void ResizeDialog::on_buttonBox_accepted()
{
    emit requestSizeChange( ui->largeurSpinBox->value(),
                            ui->hauteurSpinBox->value() );
}
