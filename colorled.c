#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"
#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2
#define PWM_PERIOD_NS 1000000 //ns. = 1ms = 1khz 

int slowly_DARK(void)
{
int i;
for(i =100; i>0 ; i--) {
pwmSetPercent_RED(i);
pwmSetPercent_BLUE(i);
pwmSetPercent_GREEN(i);
usleep(30000);
}
}

int slowly_WHITE(void)
{
int i;
for(i =0; i<100 ; i++) {
pwmSetPercent_RED(i);
pwmSetPercent_BLUE(i);
pwmSetPercent_GREEN(i);
usleep(30000);
}
}

void ColorLED_OFF(void)
{
pwmSetPercent_RED(0);
pwmSetPercent_BLUE(0);
pwmSetPercent_GREEN(0);
}





int pwmActiveAll(void)
{
int fd = 0;
fd = open ( COLOR_LED_DEV_R_ PWM_EXPORT, O_WRONLY);
write(fd,&"0",1);
close(fd);
fd = open ( COLOR_LED_DEV_G_ PWM_EXPORT, O_WRONLY);
write(fd,&"0",1);
close(fd);
fd = open ( COLOR_LED_DEV_B_ PWM_EXPORT, O_WRONLY);
write(fd,&"0",1);
close(fd);
return 1;
}

int pwmInactiveAll(void)
{
int fd = 0;
fd = open ( COLOR_LED_DEV_R_ PWM_UNEXPORT, O_WRONLY);
write(fd,&"0",1);
close(fd);
fd = open ( COLOR_LED_DEV_G_ PWM_UNEXPORT, O_WRONLY);
write(fd,&"0",1);
close(fd);
fd = open ( COLOR_LED_DEV_B_ PWM_UNEXPORT, O_WRONLY);
write(fd,&"0",1);
close(fd);
return 1;
}

int pwmSetDuty(int dutyCycle, int pwmIndex)
{
int fd = 0;
switch (pwmIndex)
{
case 2:
fd = open ( COLOR_LED_DEV_R_ PWM_DUTY, O_WRONLY);
break;
case 1:
fd = open ( COLOR_LED_DEV_G_ PWM_DUTY, O_WRONLY);
break;
case 0:
default:
fd = open ( COLOR_LED_DEV_B_ PWM_DUTY, O_WRONLY);
break;
}
dprintf(fd, "%d", dutyCycle);
close(fd);
return 1;
}

int pwmSetPeriod(int Period, int pwmIndex)
{
int fd = 0;
switch (pwmIndex)
{
case 2:
fd = open ( COLOR_LED_DEV_R_ PWM_PERIOD, O_WRONLY);
break;
case 1:
fd = open ( COLOR_LED_DEV_G_ PWM_PERIOD, O_WRONLY);
break;
case 0:
default:
fd = open ( COLOR_LED_DEV_B_ PWM_PERIOD, O_WRONLY);
break;
}
//printf ("Set pwm%d, Period:%d\r\n",pwmIndex, Period);
dprintf(fd, "%d", Period);
close(fd);
return 1;
}

int pwmSetPercent(int percent, int ledColor)
{
if ((percent <0) || (percent > 100))
{
printf ("Wrong percent: %d\r\n",percent);
return 0;
}
int duty = (100- percent) * PWM_PERIOD_NS / 100;
//LED Sinking.
pwmSetDuty(duty, ledColor);
return 0;
}

int pwmStartAll(void)
{
int fd = 0;
fd = open ( COLOR_LED_DEV_R_ PWM_ENABLE, O_WRONLY);
write(fd,&"1",1);
close(fd);
fd = open ( COLOR_LED_DEV_G_ PWM_ENABLE, O_WRONLY);
write(fd,&"1",1);
close(fd);
fd = open ( COLOR_LED_DEV_B_ PWM_ENABLE, O_WRONLY);
write(fd,&"1",1);
close(fd);
return 1;
}

int pwmLedInit(void)
{ //Initialize
pwmActiveAll();
pwmSetDuty(0, 0); //R<-0
pwmSetDuty(0, 1); //G<-0
pwmSetDuty(0, 2); //B<-0
pwmSetPeriod(PWM_PERIOD_NS, 0); pwmSetPeriod(PWM_PERIOD_NS, 1); pwmSetPeriod(PWM_PERIOD_NS, 2);
pwmStartAll();
return 0;
}

//---------------colorled 단일 색상 컨트롤 관련 함수-------------------//
int pwmSetPercent_RED(int percent)
{
if ((percent <0) || (percent > 100))
{
printf ("Wrong percent: %d\r\n",percent);
return 0;
}
int duty = (100- percent) * PWM_PERIOD_NS / 100;
//LED Sinking.
pwmSetDuty(duty, 2);
return 0;
}

int pwmSetPercent_GREEN(int percent)
{
if ((percent <0) || (percent > 100))
{
printf ("Wrong percent: %d\r\n",percent);
return 0;
}
int duty = (100- percent) * PWM_PERIOD_NS / 100;
//LED Sinking.
pwmSetDuty(duty, 1);
return 0;
}

int pwmSetPercent_BLUE(int percent)
{
if ((percent <0) || (percent > 100))
{
printf ("Wrong percent: %d\r\n",percent);
return 0;
}
int duty = (100- percent) * PWM_PERIOD_NS / 100;
//LED Sinking.
pwmSetDuty(duty, 0);
return 0;
}

int ColorLED_White(void)
{
pwmSetPercent_RED(100);
pwmSetPercent_BLUE(100);
pwmSetPercent_GREEN(100);
}

int ColorLED_Red(void)
{
pwmSetPercent_RED(100);
pwmSetPercent_BLUE(0);
pwmSetPercent_GREEN(0);
}
int ColorLED_Green(void)
{
pwmSetPercent_RED(0);
pwmSetPercent_BLUE(0);
pwmSetPercent_GREEN(100);
}
int ColorLED_Blue(void)
{
pwmSetPercent_RED(0);
pwmSetPercent_BLUE(100);
pwmSetPercent_GREEN(0);
}


//---------------Colorled 끄고 종료 --------------------------------//
int pwmLedOff(void)
{
    pwmActiveAll();
    pwmSetDuty(PWM_PERIOD_NS, 0); //R<-0
    pwmSetDuty(PWM_PERIOD_NS, 1); //G<-0
    pwmSetDuty(PWM_PERIOD_NS, 2); //B<-0
    pwmSetPeriod(PWM_PERIOD_NS, 0); pwmSetPeriod(PWM_PERIOD_NS, 1); pwmSetPeriod(PWM_PERIOD_NS, 2);
    pwmStartAll();
    pwmInactiveAll();

    return 0;
}

//-------입력받은 온도에 따라 색깔이 달라지는 모드----------//
int pwmLed_thermalcheckmode(double a)
{
    pwmLedInit();
    if(a>29)
    {
    pwmSetPercent(0,0);
    pwmSetPercent(0,1);
    pwmSetPercent(100,2);
    }
    else if(a>28)
    {
    pwmSetPercent(100,0);
    pwmSetPercent(100,1);
    pwmSetPercent(100,2);
    }
    else if(a>27)
    {
    pwmSetPercent(0,0);
    pwmSetPercent(100,1);
    pwmSetPercent(0,2);
    }
    else   
    {
    pwmSetPercent(100,0);
    pwmSetPercent(0,1);
    pwmSetPercent(0,2);
    }
    return 0;
}
