#include "sumdays.h"
#define year2 22
#define mouth2 6
#define day2 7
#define sum2 156

uint caldays(uchar year1,uchar mouth1,uchar day1)        //计算给定两天间天数
{
    uint sum1=1,sum=0;
	uchar i;
    sum1=sumdays(year1,mouth1,day1);
    for(i=year1;i<year2;i++)
        if((i%4==0&&i%100!=0)||i%400==0)
            sum+=1;        //计算给定时间中闰年的天数
    sum+=sum2-sum1+365*(year2-year1);        //计算总天数
	return sum;
}

uchar code days[12]={0,31,58,90,120,151,181,212,243,273,304,334};

//此函数作用为计算指定一天到年初的天数
uint sumdays(uchar year,uchar mouth,uchar day)
{
    uchar leap=0;
	uint sum=0;
    if((year%4==0&&year%100!=0)||year%400==0)
        leap=1;        //判断是否为闰年
    sum=days[mouth-1];
    /*switch(mouth)         //按月份计算基础天数
        {
            case(1) :sum=0;break;
            case(2) :sum=31;break;
            case(3) :sum=59;break;
            case(4) :sum=90;break;
            case(5) :sum=120;break;
            case(6) :sum=151;break;
            case(7) :sum=181;break;
            case(8) :sum=212;break;
            case(9) :sum=243;break;
            case(10) :sum=273;break;
            case(11) :sum=304;break;
            default:sum=334;break;
        }
    */
    sum+=day;        //加上每月的天数
    if(mouth>2&&leap==1)
        sum+=leap;        //如果是闰年就加上1
    return sum;
}