#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    red_colour   = {255, 21, 255, 0, 255, 14, 253, 255, 189};
    green_colour = {21, 255, 255, 255, 68, 154, 2, 255, 63};
    blue_colour  = {21, 21, 40, 255, 0, 238, 177, 128, 237};

    //GetCurrentDirectory(sizeof(directory), directory);
    //GetModuleFileName(NULL, directory, sizeof(directory));
    directory =  QApplication::applicationDirPath();

    ui->setupUi(this);

    //QPalette pallete;
    //pallete.setColor(QPalette::Background, Qt::black);
    //pallete.setColor(ui->label_1->backgroundRole(), Qt::black);
    //ui->label_1->setPalette(pallete);
    //ui->label_1->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                directory,
                "All Files (*.*);;Text File (*.vcd)"
                );

    readVCDfiles(filename);
    //QMessageBox::information(this, tr("File Name"), filename);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::readVCDfiles(QString catalog)
{
    //QMessageBox::information(this, tr("File Name"), catalog);
    QFile file(catalog);

    std::string word, letter, line2;
    //std::vector<std::string> TRS;

    std::string map_1, map_2;
    //std::map<std::string, std::string> signal_work;
    int mode_work = 1;

    signal_name.clear();
    signal_alias.clear();
    signal_type.clear();

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString line;
        do{
            line = stream.readLine();
            line2 = line.toStdString();

            word = "\0";

            if(mode_work==1){
                for(int i=0; i<line2.size(); i++){
                    letter = line2[i];
                    if(letter!=" "){
                        word = word + letter;
                    }
                    else if(letter==" " || letter=="\n"){
                        word = "\0";
                    }
                    if(word=="$var"){
                        word = "\0";
                        for(int j=0; j<line2.size(); j++){
                            letter = line2[j];
                            if(letter=="1"){
                                int ms = 0;
                                for(int k=j+2; k<line2.size(); k++){
                                    letter = line2[k];
                                    //if(letter!="$"){
                                        if(letter!=" "){
                                            if(ms==0){
                                                map_1 = map_1 + letter;
                                            }
                                            else if(ms==1){
                                                map_2 = map_2 + letter;
                                            }
                                        }
                                        else{
                                            ms++;
                                        }
                                    //}
                                    if(k==line2.size()-1){
                                        signal_name.insert(std::pair<std::string, std::string>(map_1, map_2));
                                        map_1 = "\0", map_2 = "\0";
                                        ms = 0, j=line2.size();
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(word=="$dumpvars"){
                        mode_work = 2;
                        break;
                    }
                }
            }
            else if(mode_work==2){
                std::string s1, s2;
                for(int i=0; i<line2.size(); i++){
                    letter = line2[i];
                    word = word + letter;
                    if(i==0){
                        s1 = line2[i];
                    }
                    else if(i==1){
                        s2 = line2[i];
                    }
                }
                if(word!="$end"){
                    //signal_work.insert(std::pair<std::string, std::string>(s1, s2));
                    if(s1!="#"){
                        signal_type.push_back(s1);
                        signal_alias.push_back(s2);
                    }
                }
            }
        }
        while(!line.isNull());

        file.close();
    }
    work_time = 1;

    /*FILE *f;
    f = fopen("C://mydocuments//supertask_2//result.txt", "wb");
    for(auto it=signal_name.begin(); it!=signal_name.end(); ++it)
    {
        fprintf(f, "%s: ", (it->second).c_str());
        for(int i=0; i<signal_type.size(); i++){
            if(signal_alias[i]==it->first){
                fprintf(f, "%s ", signal_type[i].c_str());
            }
        }
        fprintf(f, "\n");
    }
    fclose(f);*/
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    int midd_y = 80, start_x1 = 50, start_x2 = 80;
    int x1_f = start_x1, y1_f = midd_y, x2_f = start_x2, y2_f = midd_y;

    int x1 = this->width();
    int y1 = this->height();

    QPoint q1, q2;
    q1.setX(x1_f); q1.setY(y1_f);
    q2.setX(x2_f); q2.setY(y2_f);

    QString qs;
    QPainter painter(this);
    //painter.drawLine(q1, q2);
    std::vector<std::string> vrt;

    //QPainter painter_2(this);

    //painter.setPen(pen2);
    //painter_2.setPen(pen);

    //QPen pen;
    //pen.setStyle(Qt::DashDotLine);
    //painter.setPen(pen);
    int end_x = 0, end_size = 0;
    std::string main_info;
    int color_choose = 0;
    int vert_size_dash = 0;

    if(work_time==1){
        //QPainter painter123(this);
        //painter123.setPen(QColor(0, 0, 0));
        //painter123.drawRect(50, 50, 1250, 1250);

        int size_md = 0;

        for(auto it=signal_name.begin(); it!=signal_name.end(); ++it)
        {
            for(int i=0; i<signal_type.size(); i++){
                if(signal_alias[i]==it->first){
                    vrt.push_back("1");
                }
            }
            if(vrt.size()>size_md){
                size_md = vrt.size();
            }
            vrt.clear();
        }

        int x_coub = (x1-100)/size_md;
        int y_coub = (y1-150)/signal_name.size();

        QBrush brush;
        painter.setBrush(QColor(0, 0, 0));
        painter.drawRect(rect());

        QPen pen, pen2, pen3;
        pen.setStyle(Qt::DashDotLine);
        pen.setWidth(1);

        pen2.setStyle(Qt::SolidLine);
        pen2.setWidth(2);

        pen3.setStyle(Qt::SolidLine);
        pen3.setWidth(1);

        vert_size_dash = 40 + signal_name.size()*50;

        pen.setColor(QColor(225, 225, 225, 255)); //пунктир
        painter.setPen(pen);
        painter.drawLine(x2_f, midd_y - y_coub/4 - 5, x2_f, 80 + y_coub*signal_name.size());

        //main_info = "Graphics: " + std::to_string(signal_name.size()) + "\n";
        count_graphics = signal_name.size();
        //y2_f = y2_f + y_coub/2;

        for(auto it=signal_name.begin(); it!=signal_name.end(); ++it)
        {
            //if(it==signal_name.begin()){
            pen2.setColor(QColor(red_colour[color_choose], green_colour[color_choose], blue_colour[color_choose], 255));
            color_choose++;
            if(color_choose==9){
                color_choose = 0;
            }
            painter.setPen(pen2);

            for(int i=0; i<signal_type.size(); i++){
                if(signal_alias[i]==it->first){
                    vrt.push_back(signal_type[i]);
                }
            }
            qs = QString::fromUtf8((it->second).c_str());
            //painter.drawText(30, midd_y + 5, qs);
            QRect rec(25, midd_y - 7, 45, 16);
            painter.drawText(rec, Qt::AlignRight, qs);

            int count_fronts_neg = 0, count_fronts_positive = 0;

            for(int i=0; i<vrt.size(); i++){
                if(i!=0){
                    if(vrt[i]=="0" && vrt[i-1]=="1"){
                        count_fronts_neg++;
                    }
                    else if(vrt[i]=="1" && vrt[i-1]=="0"){
                        count_fronts_positive++;
                    }
                }
            }

            main_info = "Signal name: " + it->second + ";\t" + "Pos: " + std::to_string(count_fronts_positive) + ";\t" + "Neg: " + std::to_string(count_fronts_neg) + ";";
            int t1=0;
            if(sig_names.size()==0){
                sig_names.push_back(main_info);
            }
            else{
                t1 = 0;
                for(int k=0; k<sig_names.size(); k++){
                    if(sig_names[k]==main_info){
                        t1 = 1;
                    }
                    if(k==sig_names.size()-1 && t1==0){
                        sig_names.push_back(main_info);
                    }
                }
            }
            main_info = "";

            //count_neg.push_back(count_fronts_neg);
            //count_pos.push_back(count_fronts_positive);

            for(int i=0; i<vrt.size(); i++){
                //if(i>0){
                    if(vrt[i]=="0" && vrt[i-1]=="1"){
                        painter.drawLine(x2_f, y2_f, x2_f, y2_f + y_coub/2);    //20
                    }
                    else if(vrt[i]=="1" && vrt[i-1]=="0"){
                        painter.drawLine(x2_f, y2_f, x2_f, y2_f - y_coub/2);    //20
                    }
                //}
                //else{
                    else if(vrt[i]=="x" && vrt[i+1]=="1"){
                        painter.drawLine(x2_f + x_coub, midd_y, x2_f + x_coub, midd_y - y_coub/4);
                    }
                    else if(vrt[i]=="x" && vrt[i+1]=="0"){
                        painter.drawLine(x2_f + x_coub, midd_y, x2_f + x_coub, midd_y + y_coub/4);
                    }
                //}
                if(vrt[i]=="0"){
                    y1_f = midd_y + y_coub/4; y2_f = midd_y + y_coub/4;
                }
                else if(vrt[i]=="1"){
                    y1_f = midd_y - y_coub/4; y2_f = midd_y - y_coub/4;
                }
                else if(vrt[i]=="x"){
                    y1_f = midd_y; y2_f = midd_y;
                }

                //painter.drawLine(5, 40, 5, 50);

                if(work_select==1 && vrt[i]!="x"){
                    QRect rec_sig(x2_f, midd_y - 10, x_coub, 20);
                    if(vrt[i]=="0"){
                        painter.drawText(rec_sig, Qt::AlignCenter, "0");
                    }
                    else if(vrt[i]=="1"){
                        painter.drawText(rec_sig, Qt::AlignCenter, "1");
                    }
                }
                else if(work_select==2){
                    // hide
                }
                x1_f = x2_f;
                x2_f += x_coub;

                q1.setX(x1_f); q1.setY(y1_f);
                q2.setX(x2_f); q2.setY(y2_f);

                painter.drawLine(q1, q2);       //горизонт.линия уровня сигнала

                pen.setColor(QColor(205, 205, 205, 255)); //пунктир
                painter.setPen(pen);
                painter.drawLine(x2_f, midd_y - y_coub/4 - 5, x2_f, 80 + y_coub*signal_name.size());
                painter.setPen(pen2);
            }
            if(end_x<vrt.size()*30){
                end_x = vrt.size()*30;
                end_size = vrt.size();
            }

            pen3.setColor(QColor(205, 205, 205, 255));    //уровни нуля и единицы
            painter.setPen(pen3);
            painter.drawLine(start_x2, midd_y - y_coub/4 -3, x1 - 30, midd_y - y_coub/4 - 3);
            painter.drawLine(start_x2, midd_y + y_coub/4 + 2, x1 - 30, midd_y + y_coub/4 + 2);

            midd_y += y_coub;
            x1_f = start_x1; x2_f = start_x2;

            vrt.clear();
            //}
        }
        painter.setPen(pen3);
        painter.drawLine(start_x2, midd_y,  x1 - 30, midd_y);

        std::string ss;
        char sst2[3];
        for(int i=0; i<end_size; i++)
        {
            if(i%5==0){
                ss = i;
                sprintf(sst2, "%d", i);
                QString qss = QString::fromUtf8(sst2);
                painter.drawLine(start_x2 + i*x_coub, midd_y + 2, start_x2 + i*x_coub, midd_y - 2);
                painter.drawText(start_x2 + i*x_coub - 3, midd_y + 15, qss);
            }
        }
        painter.drawText(x1 - 40, midd_y + 15, "(ns)");
    }

}

void MainWindow::on_actionShow_data_triggered()
{
    work_select = 1;
    update();
}

void MainWindow::on_actionHide_data_triggered()
{
    work_select = 2;
    update();
}

void MainWindow::on_actionInfo_triggered()
{
    myinfo = new myInfo(this);
    myinfo->work_time = work_time;

    if(work_time==1){
        myinfo->myinfo_count_graphics = count_graphics;

        for(int i=0; i<sig_names.size(); i++){
            myinfo->myinfo_sig_names.push_back(sig_names[i]);
        }
    }
    myinfo->show();
}

void MainWindow::on_actionAbout_triggered()
{
    myabout = new myAbout(this);
    myabout->show();
}
