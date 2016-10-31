#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#include "Utils.h"
#include "Sensor.h"
#include "States.h"
#include "BehaviorLights.h"

// IR
const int IR_pins[] = {
	A0, A1, A14, A15};
float dist[4] = {};
Sensor IR("IR", IR_pins, 4, ANALOG);

float IR_dist(int val){
	//sensor reading to distance
	float volts = val* (5./1024);   //convert to volts
	float range = 65*pow(volts, -1.10);   //approximate exp data graph function
	return range;
}

// E-STOP
const int E_STOP_pins[] = {
	6};
Sensor E_STOP("E-STOP", E_STOP_pins, 1, DIGITAL);

// LIGHTS
const char light_types[] = {
	RING,RING};
const int light_pins[] = {
	5,4};
BehaviorLights lights(2,light_types, light_pins);

struct Motor{
	int pos;
	int dir;
	const int pin;
	Servo s;

	Motor(const int pin):
		pos(90),dir(5),pin(pin){

		}
	void begin(){
		s.attach(pin);
	}
	void sweep(){
		if(pos >= 180)
			dir = -5;
		else if (pos <= 0)
			dir = 5;

		pos += dir;
		s.write(pos);
	}
};
// Motors
Motor servo(8), motor_l(2), motor_r(3);

// State
State::State state = State::NORMAL;

void setup(){
	Serial.begin(9600);
	lights.setBrightness(30);

	servo.begin();
	motor_l.begin();
	motor_r.begin();

}

void loop(){
	// Sense
	E_STOP.read();
	IR.read();

	// Think

	// State Transition
	if(*E_STOP.get() == LOW){
		state = State::E_STOP;
	}
	else{
		state = State::NORMAL;
	}

	lights.set(state);

	// Act

	switch(state){
		case State::NORMAL:
			servo.sweep();
			motor_l.sweep();
			motor_r.sweep();

			Serial.print("DIST : ");
			for(int i=0; i<4; ++i){
				dist[i] = IR_dist(IR.get()[i]);
			}
			printN(dist, 4);

			Serial.print("Servo : ");
			Serial.println(servo.pos);
			break;
		case State::E_STOP:
			// do nothing
			break;
	}

	lights.shine();
	delay(100);
}
