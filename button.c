#include <wiringPi.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
  wiringPiSetup () ;
  pinMode (1, INPUT) ;
  pullUpDnControl(1, PUD_UP) ;
  for (;;)
  {
    int x = digitalRead(1);
    printf("Got a %d\n",x);
  }
  return 0 ;
}
