/*
 * =====================================================================================
 *
 *       Filename:  aboutDialog.hpp
 *
 *    Description:  Tabula Rasa : Boite du dialogue de A propos
 *
 *        Version:  1.0
 *        Created:  16/08/2011 10:31:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog {
          Q_OBJECT

     public:
          explicit AboutDialog( QWidget* parent = 0 );
          ~AboutDialog();

     private:
          Ui::AboutDialog* ui;
};

#endif // ABOUTDIALOG_HPP
