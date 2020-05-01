#include"Banker.h"



void Banker:: start(int A,int B,int *x,int **y){
    resNum=A;
    proNum=B;

    Available=new int [resNum] ; //系统可用（剩余）资源初始化
    for(int i=0;i<resNum;i++){
        Available[i]=x[i];
    }

    work=new int [resNum] ; //系统可用（剩余）资源初始化
    for(int i=0;i<resNum;i++){
       work[i]=0;
    }

    MAX=new int *[proNum];  //进程的最大需求
    for(int i=0;i<proNum;i++){
        MAX[i]=new int [resNum];
    }

    for(int i=0;i<proNum;i++){
        for(int j=0;j<resNum;j++){
            MAX[i][j]=y[i][j];
        }
    }

    Allocation=new int *[proNum];     //进程已经占有（分配）资源
    for(int i=0;i<proNum;i++){
        Allocation[i]=new int [resNum];
    }

    for(int i=0;i<proNum;i++){
        for(int j=0;j<resNum;j++){
            Allocation[i][j]=0;
        }
    }


    Need=new int *[proNum];      //进程还需要资源
    for(int i=0;i<proNum;i++){
        Need[i]=new int [resNum];
    }

    for(int i=0;i<proNum;i++){
        for(int j=0;j<resNum;j++){
            Need[i][j]=y[i][j];
        }
    }
    Finish=new bool [proNum];
    for(int i=0;i<proNum;i++)
        Finish[i]=false;

    safeSeries=new int [proNum];
    for(int i=0;i<proNum;i++)
        safeSeries[i]=0;



}

int Banker::  pro_request(int p,int *x)  //进程申请资源
{

    for(int i=0;i<resNum;i++){
           if (x[i] > Need[p][i])
        {
            return -3;
        }
        if (x[i] > Available[i])
        {
            return -2;
        }
    }
    int t=0;
    for (int i = 0; i <resNum; i++)
    {
        //以下是试探性分配
        Available[i] -= x[i];
        Allocation[p][i]+=x[i];
        Need[p][i] -= x[i];
        if(Need[p][i]==0)
            t++;
    }
    if(t==resNum){
        //释放已完成资源
        for(int i = 0; i < resNum; i++ )
        {
            Available[i] += Allocation[p][i];
        }
    }

   bool res=security_check();
   if(res==true){
       QString fff=QStringLiteral("安全序列 ");
       for(int i = 0; i < pNum; i++)
           {   fff+="P";
               QString x=QString::number(safeSeries[i]+1);
               fff+=x;
               fff+=" ";
           }
    logtext=fff;
     return 0;
   }
   else{
       for (int i = 0; i <resNum; i++)
       {
           //收回资源
           Available[i] += x[i];
           Allocation[p][i]-=x[i];
           Need[p][i] += x[i];
       }
      return -1;
   }
}
bool Banker:: isAllZero(int P)
{
    int num = 0;
    for(int i = 0; i < resNum; i++ )
    {
        if(Need[P][i] == 0)
        {
            num ++;
        }
    }
    if(num == resNum)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool  Banker:: security_check(){
    int safeIndex = 0;
    int allFinish = 0;
    int r = 0;
    int temp = 0;
     pNum = 0;
    for(int i=0;i<resNum;i++){
        work[i]=Available[i];
    }
    //把未完成进程置为false
        for(int i = 0; i < proNum; i++)
        {
            bool result = isAllZero(i);
            if(result == true)
            {
                Finish[i] = true;
                allFinish++;
            }
            else
            {
                Finish[i] = false;
            }
        }
        //预分配开始
            while(allFinish != proNum)
            {
                int num = 0;
                for(int i = 0; i < resNum; i++)
                {
                    if(Need[r][i] <= work[i] && Finish[r] == false)
                    {
                        num ++;
                    }
                }
                if(num == resNum)
                {
                    for(int i = 0; i < resNum; i++ )
                    {
                        work[i] = work[i] + Allocation[r][i];
                    }
                    allFinish ++;
                    //SafeInfo(work,r);
                    safeSeries[safeIndex] = r;
                    safeIndex ++;
                    Finish[r] = true;
                }
                r ++;//该式必须在此处
                if(r >= proNum)
                {
                    r = r % proNum;
                    if(temp == allFinish)
                    {
                        break;
                    }
                    temp = allFinish;
                }
                pNum = allFinish;
            }
            //判断系统是否安全
            for(int i = 0; i < proNum; i++)
            {
                if(Finish[i] == false)
                {
                    return false;
                }
            }

            for(int i = 0; i < proNum; i++)
            {
                bool result = isAllZero(i);
                if(result == true)
                {
                    pNum --;
                }
            }
            return true;
}
