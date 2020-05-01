#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include<QTableWidget>
#include"Banker.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void start(int resnum,int pronum,int *x,int **y);  //窗口初始化
    void myupdate();                                   //更新资源窗口


private slots:
    void send_request();                              //槽函数，发送线程资源请求

private:
    Ui::Form *ui;
    Banker mybank;
    int res;     //资源种类
    int pro;     //线程数目
    int cur;     //当前请求线程
};

#endif // FORM_H
