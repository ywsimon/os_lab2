#include "form.h"
#include "ui_form.h"

#include <QHeaderView>
#include <QTreeView>
#include<QDebug>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView* headerView =  ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
    QHeaderView* headerView2 =  ui->tableWidget_2->verticalHeader();
    headerView2->setHidden(true);
    QHeaderView* headerView3 =  ui->tableWidget_3->verticalHeader();
    headerView3->setHidden(true);
    QHeaderView* headerView4 =  ui->tableWidget_4->verticalHeader();
    headerView4->setHidden(true);
    QHeaderView* headerView5 =  ui->tableWidget_5->verticalHeader();
    headerView5->setHidden(true);

     connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(send_request()));
}

Form::~Form()
{
    delete ui;
}
void Form:: start(int resnum,int pronum,int *x,int **y){
    res=resnum;
    pro=pronum;
    mybank.start(resnum, pronum, x, y);
    this->ui->spinBox->setMaximum(pronum);
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(resnum);
    QStringList header;
    for(int i=1;i<resnum+1;i++){
        QString num=QString::number(i);
        QString name="R";
        QString  t=name+num;
       QByteArray ba2;
       ba2.append(t);     //也可以 ba2 = s2.toLatin1();
       const char *c = ba2.data();
       header<<tr(c);
    }
    this->ui->tableWidget->setHorizontalHeaderLabels(header);
    this->ui->tableWidget->insertRow(0); //插入新行
    for(int i=0;i<resnum;i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        QString num=QString::number(x[i]);
        item->setText(num);
        this->ui->tableWidget->setItem(0, i, item);
        ui->tableWidget->item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
     }

    this->ui->tableWidget_2->clear();
    this->ui->tableWidget_2->setColumnCount(resnum);
    this->ui->tableWidget_2->setHorizontalHeaderLabels(header);
      this->ui->tableWidget_2->insertRow(0); //插入新行
    for(int i=0;i<resnum;i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        QString num=QString::number(x[i]);
        item->setText(num);
        this->ui->tableWidget_2->setItem(0, i, item);
        ui->tableWidget_2->item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }


    QStringList header1;
    header1<<tr("PID");
    for(int i=1;i<resnum+1;i++){
        QString num=QString::number(i);
        QString name="R";
        QString  t=name+num;
       QByteArray ba2;
       ba2.append(t);     //也可以 ba2 = s2.toLatin1();
       const char *c = ba2.data();
       header1<<tr(c);
    }
    this->ui->tableWidget_4->clear();
    this->ui->tableWidget_4->setColumnCount(resnum+1);
    this->ui->tableWidget_4->setHorizontalHeaderLabels(header1);
    for(int i=0;i<pronum;i++){
         this->ui->tableWidget_4->insertRow(i); //插入新行
         for(int j=0;j<=resnum;j++){
               QTableWidgetItem *item = new QTableWidgetItem();
               item->setFlags(item->flags() & (~Qt::ItemIsEditable));
               if(j==0)
               {
                   QString num=QString::number(i+1);
                   QString name="P";
                   QString  t=name+num;
                   item->setText(t);
               }
               else{
                   item->setText(QString :: number(y[i][j-1]));
               }
              this->ui->tableWidget_4->setItem(i,j,item);
                ui->tableWidget_4->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         }
    }

     this->ui->tableWidget_3->clear();
     this->ui->tableWidget_3->setColumnCount(resnum+1);
    this->ui->tableWidget_3->setHorizontalHeaderLabels(header1);
    for(int i=0;i<pronum;i++){
         this->ui->tableWidget_3->insertRow(i); //插入新行
         for(int j=0;j<=resnum;j++){
               QTableWidgetItem *item = new QTableWidgetItem();
               item->setFlags(item->flags() & (~Qt::ItemIsEditable));
               if(j==0)
               {
                   QString num=QString::number(i+1);
                   QString name="P";
                   QString  t=name+num;
                   item->setText(t);
               }
               else{
                   item->setText(QString :: number(0));
               }
              this->ui->tableWidget_3->setItem(i,j,item);
                ui->tableWidget_3->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         }
    }


    this->ui->tableWidget_5->clear();
    this->ui->tableWidget_5->setColumnCount(resnum);
        this->ui->tableWidget_5->setHorizontalHeaderLabels(header);
    this->ui->tableWidget_5->insertRow(0); //插入新行
    for(int i=0;i<resnum;i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText("");
        this->ui->tableWidget_5->setItem(0, i, item);
        ui->tableWidget_5->item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
     }
    if(mybank.security_check()==true){
        this->ui->textBrowser->append("<font color=\"#00FF00\">"+QStringLiteral("当前系统安全")+"</3,QFont::Bold)> ");
    }
    else{
        this->ui->textBrowser->append("<font color=\"FF0000\">"+QStringLiteral("当前系统不安全")+"</3,QFont::Bold)> ");
    }
    }


void Form:: send_request(){
    for(int i=0;i<res;i++){
        if(this->ui->tableWidget_5->item(0,i)==nullptr || this->ui->tableWidget_5->item(0,i)->text()=="" )
        {
            this->ui->textBrowser->append("<font color=\"#FF0000\">"+QString("please input correct resources"));
            return;
        }
    }
    int *temp=new int [res];
    for(int i=0;i<res;i++)
        temp[i]=this->ui->tableWidget_5->item(0,i)->text().toInt();

    QString num=QString::number(this->ui->spinBox->value());
    QString str=" theard is requesting some resources";
    QString t="P"+num+str;
    qDebug()<<t;
    this->ui->textBrowser->append("<font color=\"#000000\">"+t);
     cur=this->ui->spinBox->value()-1;
     cur=this->ui->spinBox->value()-1;
    int x=mybank.pro_request(this->ui->spinBox->value()-1,temp);

    delete [] temp;
    if(x==-3){
        this->ui->textBrowser->append("<font color=\"#FF0000\">"+QString("Reject.Request over demand")+"</3,QFont::Bold)> ");
        return ;
    }
    if(x==-2){
        this->ui->textBrowser->append("<font color=\"#FF0000\">"+QString("Reject.Request over remainder")+"</3,QFont::Bold)> ");
        return ;
    }

    if(x==-1){
        this->ui->textBrowser->append("<font color=\"#FF0000\"> "+QString("Reject.The request makes the system unsafe.")+"</3,QFont::Bold)>");
         return ;
     }
    if(x==0){
        myupdate();
     }
    return ;
}
void Form:: myupdate(){
    this->ui->textBrowser->append("<font color=\"#00FF00\">"+QString("Request safe, executing")+"</3,QFont::Bold)> ");
    for(int j=0;j<res;j++){
        this->ui->tableWidget_2->item(0,j)->setText(QString::number(mybank.Available[j]));
       this->ui->tableWidget_3->item(cur,j+1)->setText(QString::number(mybank.Allocation[cur][j]));
         this->ui->tableWidget_4->item(cur,j+1)->setText(QString::number(mybank.Need[cur][j]));
    }
     this->ui->textBrowser->append("<font color=\"#00FF00\">"+QString(mybank.logtext)+"</3,QFont::Bold)> ");
}
