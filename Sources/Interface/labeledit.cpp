#include "labeledit.hpp"
#include "ui_labeledit.h"

LabelEdit::LabelEdit( QWidget* parent, const QString& label ) :
     QDialog( parent ),
     ui( new Ui::LabelEdit )
{/*{{{*/
     ui->setupUi( this );
     ui->plainTextEdit->setPlainText( label );
     ui->plainTextEdit->selectAll();
     this->setMaximumHeight( 150 );
}/*}}}*/

LabelEdit::~LabelEdit()
{/*{{{*/
     delete ui;
}/*}}}*/

QString LabelEdit::label() const
{/*{{{*/
     return ui->plainTextEdit->toPlainText();
}/*}}}*/
