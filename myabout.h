#ifndef MYABOUT_H
#define MYABOUT_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class myAbout;
}

class myAbout : public QDialog
{
    Q_OBJECT

public:
    explicit myAbout(QWidget *parent = 0);
    ~myAbout();

private slots:
    void on_pushButton_clicked();

private:
    Ui::myAbout *ui;
};

#endif // MYABOUT_H
