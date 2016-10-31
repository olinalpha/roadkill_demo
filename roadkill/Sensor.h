#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <Arduino.h>
#define nullptr NULL

enum {
    ANALOG, DIGITAL};

//generic multi-sensor interface
struct Sensor{
    const int n;
    char type;
    const char* name;
    const int* pins;
    int* vals;
    Sensor(const char* _name, const int* _pins, int _n, char _type):
    name(_name), pins(_pins),n(_n), type(_type){
        for(int i=0; i<n; ++i){
            pinMode(pins[i], INPUT);   
        }
        // allocate vals
        vals = (int*)malloc(sizeof(int) * n);
    }
    ~Sensor(){
        if(vals){
            free(vals);
            vals = nullptr;   
        }
    }
    void read(){
        for(int i=0; i<n; ++i){
            vals[i] = (type == ANALOG)? analogRead(pins[i]) : digitalRead(pins[i]);
        }
    }
    const int* get(){
        return vals;
    }
    void print(){
        Serial.print(name);
        Serial.print(" : ");
        for(int i=0; i<n; ++i){
            Serial.print(vals[i]);
            if(i != n-1)
                Serial.print(',');
        } 
        Serial.print('\n');
    }
};
#endif
