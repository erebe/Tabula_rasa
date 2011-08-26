/*
 * =====================================================================================
 *
 *       Filename:  aboutDialog.cpp
 *
 *    Description:  Tabula Rasa : Boite de dialogue du A propos
 *
 *        Version:  1.0
 *        Created:  16/08/2011 10:31:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "aboutDialog.hpp"
#include "ui_aboutDialog.h"

AboutDialog::AboutDialog( QWidget* parent ) :
     QDialog( parent ),
     ui( new Ui::AboutDialog )
{
     ui->setupUi( this );
}

AboutDialog::~AboutDialog()
{
     delete ui;
}
