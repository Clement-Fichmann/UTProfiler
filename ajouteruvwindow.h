#ifndef AJOUTERUVWINDOW_H
#define AJOUTERUVWINDOW_H

#include <QDialog>

namespace Ui {
class ajouterUVWindow;
}

class ajouterUVWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterUVWindow(QWidget *parent = 0);
    ~ajouterUVWindow();

public slots:
    void on_btnAnnuler_clicked();

private:
    Ui::ajouterUVWindow *ui;
};

#endif // AJOUTERUVWINDOW_H
