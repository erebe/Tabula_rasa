#ifndef SAUVEGARDE_HPP
#define SAUVEGARDE_HPP

#include <QDialog>
class QAbstractButton;

namespace Ui {
    class Sauvegarde;
}

class Sauvegarde : public QDialog
{
    Q_OBJECT

public:
    Sauvegarde( QList< QPair<QString, bool> >& algo, QWidget *parent = 0 );
    ~Sauvegarde();

    private slots:
        void clickDiscard( );
        void clickSave( );
private:
    Ui::Sauvegarde *ui;
    QList< QPair<QString, bool> >& algos_;
};

#endif // SAUVEGARDE_HPP
