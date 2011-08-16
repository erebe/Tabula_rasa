#ifndef RESIZEDIALOG_HPP
#define RESIZEDIALOG_HPP

#include <QDialog>

namespace Ui {
    class ResizeDialog;
}

class ResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeDialog(int width = 0, int height = 0, QWidget *parent = 0);
    ~ResizeDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void requestSizeChange( int width, int height );

private:
    Ui::ResizeDialog *ui;
};

#endif // RESIZEDIALOG_HPP
