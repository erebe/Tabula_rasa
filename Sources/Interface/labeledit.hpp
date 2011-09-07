#ifndef LABELEDIT_HPP
#define LABELEDIT_HPP

#include <QDialog>

namespace Ui {
class LabelEdit;
}/*}}}*/

class LabelEdit : public QDialog {
          Q_OBJECT

     public:
          LabelEdit( QWidget* parent, const QString& label );
          ~LabelEdit();
          QString label() const;

     private:
          Ui::LabelEdit* ui;
};

#endif // LABELEDIT_HPP
