#ifndef BANKER_H
#define BANKER_H
#include <QWidget>
#include<stdio.h>


class Banker{
public:
    int resNum;        //资源类别数
    int proNum;        //线程数
    int  *Available;   //系统可用资源
    int **MAX;         //进程的最大需求
    int **Allocation;  //进程已经占有（分配）资源
    int **Need;        //进程还需要资源
    int *work;         //工作向量，保护 Available
    int *safeSeries;   //安全序列号
    int pNum;          //安全序列数目
    QString logtext;   //安全序列文本
    bool *Finish;      //进程是否结束

    void start(int resnum,int pronum,int *x,int **y); //初始化
    int pro_request(int ,int *);     //线程资源请求
    bool security_check();           //安全性检测
    bool isAllZero(int);             //判断线程是否结束
};
#endif // BANKER_H
