#include "global.h"

uchar code days[12] = {0,31,58,90,120,151,181,212,243,273,304,334};

uint Sumdays(uchar year, mouth, day)
{
    uchar leap = 0;
	uint sum = 0;
    if(((year%4 == 0) && (year%100 != 0)) || (year%400 == 0))
        leap = 1;
    sum = days[mouth - 1];
    sum += day;
    if(mouth > 2 && leap ==1)
        sum += leap;
    return sum;
}

uint Caldays(uchar year1, uchar mouth1, uchar day1)
{
 	uint sum1 = 1, sum = 0,sum2 = 1;
	uchar i;
 	sum1 = Sumdays(year1, mouth1, day1);
	sum2 = Sumdays(CEEDAY[0], CEEDAY[1], CEEDAY[2]);
	
	if((year1 > CEEDAY[0] ) || ((year1 == CEEDAY[0]) && sum1 > sum2))
		return 0;

	for(i = year1; i < CEEDAY[0]; i++)
	if((i%4 ==0 && i%100 != 0) || i % 400 == 0)
		sum += 1;
	sum += sum2 - sum1 + 365 * (CEEDAY[0] - year1);
	return sum;
}
