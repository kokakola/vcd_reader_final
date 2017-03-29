#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <vector>
#include <QTextStream>
#include <map>
#include <QtGui>
#include <fstream>
#include "myinfo.h"
#include "myabout.h"
#include <QPalette>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionShow_data_triggered();
    void on_actionHide_data_triggered();
    void on_actionInfo_triggered();

    void on_actionAbout_triggered();

private:
    int work_time = 0;
    int work_select = 0;

    QString directory;

    std::vector<std::string> signal_alias;
    std::vector<std::string> signal_type;

    std::map<std::string, std::string> signal_name;
    //std::map<std::string, int> count_front;

private:
    int count_graphics;
    std::vector<std::string> sig_names;

    std::vector<int> red_colour;
    std::vector<int> blue_colour;
    std::vector<int> green_colour;

    //std::vector<int> count_neg;
    //std::vector<int> count_pos;

private:
    void readVCDfiles(QString catalog);

protected:
    void paintEvent(QPaintEvent *e);

private:
    Ui::MainWindow *ui;
    myInfo *myinfo;
    myAbout *myabout;
};

#endif // MAINWINDOW_H
