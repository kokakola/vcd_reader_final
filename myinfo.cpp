#include "myinfo.h"
#include "ui_myinfo.h"

myInfo::myInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myInfo)
{
    ui->setupUi(this);
}

myInfo::~myInfo()
{
    delete ui;
}

void myInfo::paintEvent(QPaintEvent *e1)
{
    QPainter painter(this);
    int x=20, y=50;

    if(work_time==1){
        QString s222;
        std::string s123 = "Number of signals: " + std::to_string(myinfo_count_graphics);
        s222 = QString::fromUtf8(s123.c_str());

        painter.drawText(x, y, s222);
        y += 30;

        for(int i=0; i<myinfo_sig_names.size(); i++){
            s222 = QString::fromUtf8((std::to_string(i+1) + ". " + myinfo_sig_names[i]).c_str());
            painter.drawText(x ,y, s222);
            y += 15;
        }
    }
    else{
        painter.drawText(x, y, "File is no selected.");
    }
}

void myInfo::on_pushButton_clicked()
{
    this->close();
}
