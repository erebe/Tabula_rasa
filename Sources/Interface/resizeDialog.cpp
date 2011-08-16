#include "resizeDialog.hpp"
#include "ui_resizeDialog.h"

ResizeDialog::ResizeDialog( int width, int height, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeDialog)
{
    ui->setupUi(this);
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
