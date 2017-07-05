#include <user_config.h>
#include <SmingCore/SmingCore.h>

#define INT_PIN 0   // GPIO0
#define say(a) ( Serial.print(a) )

int lastTime;
Timer tmr;

void IRAM_ATTR interruptHandler()
{	int currTime = millis();
	if(currTime-lastTime > 500){
		say(millis());
		say( "Pin changed, now   ");
		say( digitalRead(INT_PIN));
		Serial.println();
		lastTime = currTime;
	}
}

void timerInterrupt(){
	Serial.print("Timer activated: ");
	Serial.println(millis());
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 or 9600 by default
	lastTime = millis();
	delay(3000);

	say("======= Bring GPIO");
	say( INT_PIN);
	say( " low to trigger interrupt(s) =======");
	Serial.println();
	pinMode(INT_PIN,INPUT_PULLUP);
	attachInterrupt(INT_PIN, interruptHandler, FALLING);

	tmr.setCallback(timerInterrupt);
	tmr.setIntervalMs(2500);
	tmr.start(true);
}
