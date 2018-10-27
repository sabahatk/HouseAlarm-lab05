#include <stdio.h>
#include <wiringPi.h>
#include <curl/curl.h>
#include "ifttt.h"
#include <time.h>

#define ALARM_OFF 1
#define ALARM_ARMING 2
#define ALARM_ARMED 3
#define ALARM_TRIGGERED 4
#define ALARM_SOUNDING 5


int alarmOff(int state);
int alarmArming(int state);
int alarmArmed(int state);
int alarmTriggered(int state);
int alarmSounding(int state);

int main(int argc, char *argv[]){
	int state;
	wiringPiSetup();
	pinMode(1, INPUT); /*button*/
	pullUpDnControl(1, PUD_UP) ;
	pinMode(2, OUTPUT);/*LED 1*/
	pinMode(0, OUTPUT);/*LED 2*/	
	pinMode(4, OUTPUT);/*buzzer*/
	pinMode(3, INPUT); /*ir scanner*/
	state = ALARM_OFF;
	while(1){
 
		state = alarmOff(state);
		state = alarmArming(state);
		state = alarmArmed(state);
	
		if(state == ALARM_TRIGGERED){
			state = alarmTriggered(state);
			printf("alarm triggered");

			if(state == ALARM_SOUNDING){
				printf("Alarm Sounding");
				state = alarmSounding(state);
			}
		}
	}
	return 0;

}

int alarmOff(int state){
         if(state ==  ALARM_OFF){
                printf("Case 1 entered");
		delay(5000);
                while(1){
			printf("ALARM 0\n");
                        digitalWrite(2, HIGH);
                        digitalWrite(0, LOW);
                        digitalWrite(4, LOW);
                
                	if(digitalRead(1) == 0){
                        	printf("alarm arming");
                        	return ALARM_ARMING;
                	}
		}
        }
                return 0;
}

int alarmArming(int state){
	int i;
	if(state == ALARM_ARMING){
        	printf("Case 2 entered");
		digitalWrite(4, LOW);
                for(i=0;i<5;i++){
                	digitalWrite(2, LOW); delay(1000);
                        digitalWrite(2, HIGH); delay(1000);
                }
                return ALARM_ARMED;
        }
	return 0;
}

int alarmArmed(int state){
	if(state == ALARM_ARMED){
		printf("ALARM ARMED\n");
		while(1){
		printf("VALUE OF TRIGGER ALARM: %d\n", digitalRead(3));
		digitalWrite(2,LOW);
		digitalWrite(0,HIGH);
		digitalWrite(4,LOW);
				
			if(digitalRead(1) == 0){
				printf("ALARM TURNED OFF\n");
				return ALARM_OFF;
			}
			if(digitalRead(3) == 1){
				printf("ALARM TRIGGERED\n");
				return ALARM_TRIGGERED;
			}
		}
	}
	return 0;
}

int alarmTriggered(int state){
	int j;
	digitalWrite(4, LOW);
	for(j=0;(j<5) && (digitalRead(1) == 1);j++){
	printf("ALARM TRIGGERED");
	digitalWrite(2, HIGH);
	digitalWrite(0, HIGH);
	delay(1000);
	digitalWrite(2, LOW);
	digitalWrite(0, LOW);
	delay(1000);
	}
	if(j==5){
		return ALARM_SOUNDING;
	}
	return ALARM_OFF;		
}

int alarmSounding(int state){
	printf("ALARM SOUNDING\n");
	ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/bYHA88jvpwt5C8E5p_m9j","Tested","1","2");
	if(state == ALARM_SOUNDING){
		while(digitalRead(1) == 1){
			digitalWrite(2, HIGH);
			digitalWrite(0, HIGH);
			digitalWrite(4, HIGH);
			delay(2000);
			digitalWrite(2, LOW);
			digitalWrite(0, LOW);
			digitalWrite(4, LOW);
			delay(2000);	
		}
	
		return ALARM_OFF;
	}
	return 0;
}
