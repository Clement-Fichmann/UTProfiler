#ifndef UVWINDOW_H
#define UVWINDOW_H

#include <QDialog>

namespace Ui {
class UVWindow;
}

class UVWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UVWindow(QWidget *parent = 0);
    ~UVWindow();

public slots:
    void on_btnFermer_clicked();

private:
    Ui::UVWindow *ui;
};

#endif // UVWINDOW_H
