#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>
#include <QTreeView>
#include <QTableView>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->ui->pushButton_2->hide();
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(this->ui->pushButton_2,SIGNAL(clicked()),this,SLOT(moni()));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: start(){
    this->setFixedSize(QSize(900,407));
    this->ui->pushButton->hide();
    this->ui->spinBox->hide();
    this->ui->spinBox_2->hide();
    this->ui->label_2->hide();
    this->ui->label_3->hide();
    this->ui->pushButton_2->show();
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(this->ui->spinBox->value()+1);
    QStringList header;
    header<<tr("PID");
    for(int i=1;i<this->ui->spinBox->value()+1;i++){
        QString num=QString::number(i);
        QString name="R";
        QString  t=name+num;
       QByteArray ba2;
       ba2.append(t);     //也可以 ba2 = s2.toLatin1();
       const char *c = ba2.data();
       header<<tr(c);
    }
    this->ui->tableWidget->setHorizontalHeaderLabels(header);
    QFont font = this->ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    this->ui->tableWidget->horizontalHeader()->setFont(font);
    this->ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    int pnum=this->ui->spinBox_2->value();
    for(int i = 0; i <=pnum; i++)
     {
       this->ui->tableWidget->insertRow(i); //插入新行
       QTableWidgetItem *item = new QTableWidgetItem();
       QString num=QString::number(i);
       QString name="P";
       QString  t=name+num;
       item->setText(t);
       if(i==0)
            item->setText("MAX_NUM");
       this->ui->tableWidget->setItem(i, 0, item);
    }
}

void MainWindow:: moni(){
    int resourceNum;
    int processNum;
    resourceNum=this->ui->spinBox->value();
    processNum=this->ui->spinBox_2->value();

    qDebug()<<resourceNum<<" "<<processNum;

    for(int i=0;i<processNum+1;i++){
        for(int j=0;j<resourceNum+1;j++){
            if(this->ui->tableWidget->item(i,j)==nullptr){
                qDebug()<<i<<j<<" nulol";
                return;
            }
    }
    }
    Form *win;
    win=new Form();
    win->show();

    qDebug()<<"yes";
    int  *availableresourceNum;  //系统可用（剩余）资源
    int **maxRequest;  //进程的最大需求

    availableresourceNum=new int [resourceNum] ; //系统可用（剩余）资源初始化
    for(int i=0;i<resourceNum;i++){
        availableresourceNum[i]=this->ui->tableWidget->item(0,i+1)->text().toInt();
    }
    qDebug()<<" a";

    maxRequest=new int *[processNum];  //进程的最大需求
    for(int i=0;i<processNum;i++){
        maxRequest[i]=new int [resourceNum];
    }
    for(int i=0;i<processNum;i++){
        for(int j=0;j<resourceNum;j++){
            maxRequest[i][j]=this->ui->tableWidget->item(i+1,j+1)->text().toInt();
        }
    }
        qDebug()<<" b";
    win->start(resourceNum, processNum,availableresourceNum,maxRequest);
    this->hide();

}
