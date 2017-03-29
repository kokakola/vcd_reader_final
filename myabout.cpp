#include "myabout.h"
#include "ui_myabout.h"

myAbout::myAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myAbout)
{
    ui->setupUi(this);
    QPixmap pix("C://mydocuments//supertask_2//Flash.png");
    ui->label_pic->setPixmap(pix.scaled(179, 275, Qt::KeepAspectRatio));
}

myAbout::~myAbout()
{
    delete ui;
}

void myAbout::on_pushButton_clicked()
{
    this->close();
}
