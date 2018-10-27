#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
 /* int i;*/
  wiringPiSetup () ;
  pinMode(3, INPUT);
  while(1) {
    printf("Waiting for reset\n");
    while(digitalRead(3) == 1);
    printf("Waiting for event\n");
    while(digitalRead(3) == 0);
    printf("Alarm\n");
  }
  /*NOTREACHED*/
  return 0 ;
}
