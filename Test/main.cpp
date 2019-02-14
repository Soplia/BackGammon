#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 300
#define TRUE 1

/*--------------------OH_PRA用于存放7个影响Lb的参数以及Lb---------------------*/
typedef struct
{
   int area;                                             //地区(市区-0.郊区-1.
   //开阔区-2)
   int city;                                             //城市(中.小城市-0,
   //大城市-1)
   double d;                                             //收发天线之间的距离,
   //km
   double f;                                             //工作频率,MHz
   double Hb;                                            //基站天线有效高度,m
   double Hm;                                            //移动台天线高度,m
   double AHm;                                           //移动台天线高度校
   //正因子,dB
   double Lb;                                            //基本传输损耗,dB
}OH_PRA;
/*-------------------------------全局变量-------------------------------------*/

OH_PRA data[SIZE];//数据组最大容量300组
int Number=0;

/*-------------------------------函数列表-------------------------------------*/

void InitOH();                                            //初始化界面
void RET();                                               //返回主程序
int read();                                               //从OH读入数据到data
//数组
void write();                                             //测试值写入文件OH
void ADD();                                               //添加测试值
double Aa(int city,double f,double Hm);                   //计算移动台天线高度
//校正因子
double L(int area,double f,double d,double Hb,double AHm);//计算Lb基本传输损耗
//函数
void LIST();                                              //查看测试值

/*-------------------------------主程序---------------------------------------*/
int main()
{
   FILE *fp;
   int choose=0;
   char yesorno;
   if( (fp=fopen("OH","rb"))!= 0)
   {
      Number=read();//从文件读入数据,并返回读入数据的个数给Number,
      //若文件原来有两组数据,则Number为3
   }
   else
   {
      printf("\n=========>提示：文件不存在，是否要创建一个?(y/n)\n");
      scanf("%c",&yesorno);
      if( yesorno=='y' )
      {
         fp=fopen("OH","wb");
         fclose(fp);
      }
      else
      {
         exit(0);
      }
   }//创建新文件
   system("cls");
   while(TRUE)//始终显示主界面
   {
      InitOH();
      scanf("%d",&choose);
      system("cls");
      switch(choose)
      {
         case 1:ADD();RET();break;
         case 2:LIST();RET();break;
         case 0: return 0;
         default:break;
      }
      fflush(stdin);
      getchar();
      system("cls");
   }
       return 0;
}

void InitOH()
{
   printf("\t*************************************************************\n");
   printf("\t* *\n");
   printf("\t* Okumura-Hata预测系统 *\n");
   printf("\t* *\n");
   printf("\t* [1] 增加预测值          [2] 查看预测值      *\n");
   printf("\t*                         [0] 退出系统          *\n");
   printf("\t*************************************************************\n");
}

void RET()
{
   printf("\t===>按Enter键返回主菜单\n");
}

int read()
{
   FILE *fp=NULL;
   int i=0;
   fp=fopen("OH","rb");
   while(fread(&data[i],sizeof(OH_PRA),1,fp))//if an error occurs or if the
      //end of the file is encountered before reaching count.
      i++;
   fclose(fp);
   return i;
}

void write()
{
   FILE *fp;
   fp=fopen("OH","ab+");
   fwrite(&data[Number],sizeof(OH_PRA),1,fp);
   fclose(fp);
}

void ADD()
{
   printf("ADD a new dataum:\n");
   printf(">>请输入地区类型(市区-0.郊区-1.开阔区-2):\n");
   scanf("%d",&data[Number].area);
   printf(">>请输入城市类型(中.小城市-0,大城市-1):\n");
   scanf("%d",&data[Number].city);
   printf(">>请输入收发天线之间的距离d(km):\n");
   scanf("%lf",&data[Number].d);
   printf(">>请输入工作频率f(MHz):\n");
   scanf("%lf",&data[Number].f);
   printf(">>请输入基站天线有效高度Hb(m):\n");
   scanf("%lf",&data[Number].Hb);
   printf(">>请输入移动台天线高度(m):\n");
   scanf("%lf",&data[Number].Hm);
   data[Number].AHm=Aa(data[Number].city,data[Number].f,data[Number].Hm);
   data[Number].Lb=L(data[Number].area,data[Number].f,data[Number].d,
                     data[Number].Hb,data[Number].AHm);
   printf("the contents that you wanted to add is:\n");
   
   printf("area city\td\tf\tHb\tHm\tAHM\tLb\n");
   printf("%4d%5d\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n",
          data[Number].area,data[Number].city,data[Number].d,data[Number].f,
          data[Number].Hb,data[Number].Hm,data[Number].AHm,data[Number].Lb);
   write();
   Number++;
}

double Aa(int city,double f,double Hm)
{
   double AHm=0;
   switch(city)
   {
      case 0:AHm=(1.1*log10(f)-0.7)*Hm-1.56*log10(f)+0.8;break;
      case 1:
         if(f<=300)
         {
            AHm=8.29*((log10(1.54*Hm))*(log10(1.54*Hm)))-1.1;
         }
         else
         {
            AHm=3.2*((log10(11.75*Hm))*(log10(11.75*Hm)))-4.97;
         }
         break;
      default:break;
   }
   return AHm;
}

double L(int area,double f,double d,double Hb,double AHm)
{
   double Lb=0,Lb0=0;
   Lb0=69.55+29.16*log10(f)-13.82*log10(Hb)-AHm+(44.9-6.55*log10(Hb))*log10(d);
   switch(area)
   {
      case 0:Lb=Lb0;
         break;
      case 1:Lb=Lb0-2*((log10(f/28))*(log10(f/28)))-5.4;
         break;
      case 2:Lb=Lb0-4.78*(log10(f)*log10(f))+18.33*log10(f)-40.98;
         break;
      default:
         break;
   }
   return  Lb;
}

void LIST()
{
   int i=0;
   printf("area city\td\tf\tHb\tHm\tAHM\tLb\n");
   for(i=0;i<Number;i++)
   {
      printf("%4d%5d\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n",
             data[i].area,data[i].city,data[i].d,data[i].f,
             data[i].Hb,data[i].Hm,data[i].AHm,data[i].Lb);
   }
}
