#ifndef MYINFO_H
#define MYINFO_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class myInfo;
}

class myInfo : public QDialog
{
    Q_OBJECT

public:
    explicit myInfo(QWidget *parent = 0);
    ~myInfo();

protected:
    void paintEvent(QPaintEvent *e1);

public:
    int myinfo_count_graphics;
    int work_time = 0;

    std::vector<std::string> myinfo_sig_names;
    //std::vector<int> myinfo_count_neg;
    //std::vector<int> myinfo_count_pos;

private slots:
    void on_pushButton_clicked();

private:
    Ui::myInfo *ui;
};

#endif // MYINFO_H
