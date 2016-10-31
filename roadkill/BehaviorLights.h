#ifndef __BEHAVIOR_LIGHTS_H__
#define __BEHAVIOR_LIGHTS_H__

// include Adafruit_NeoPixel.h before usage
#include <Arduino.h>
#include "States.h"

#define RING 12
#define STRIP 8


struct BehaviorLights{
    const int n;
    const char* type;
    const int* pin;
    char mode;
    int cnt;

    Adafruit_NeoPixel lights[2];
    BehaviorLights(const int n, const char* type, const int* pin):
    n(n), type(type), pin(pin), mode(State::NORMAL), cnt(0){
        for(int i=0; i<2; ++i){
            lights[i] = Adafruit_NeoPixel(type[i], pin[i]);   
            lights[i].begin();
            lights[i].setBrightness(0); // default dark
        }


    }


    void setBrightness(int n){
        for(int i=0; i<n; ++i){
            lights[i].setBrightness(n); 
        }  
    }

    void show(){
        for(int i=0; i<n; ++i){
            lights[i].show();   
        }
    }

    void normal(){

        if(cnt & 1){
            for(int i=0; i<n; ++i){ // number of rings/strips
                for(int pxl=0; pxl<type[i]; ++pxl){ // number of pixels per ring/strip
                    lights[i].setPixelColor(i, 0,0,0);
                }            
            }

        }
        else{
            for(int i=0; i<n; ++i){ // number of rings/strips

                for(int pxl=0; pxl<type[i]; ++pxl){ // number of pixels per ring/strip
                    int blue = random(125);
                    int red = random(125);
                    int green = random(125);

                    lights[i].setPixelColor(i, red, green, blue);
                }            

            }

        }

        show();
    }


    void e_stop(){

        if(cnt & 1){
            for(int i=0; i<n; ++i){ // number of rings/strips
                for(int pxl=0; pxl<type[i]; ++pxl){ // number of pixels per ring/strip
                    lights[i].setPixelColor(i,255,0,0);
                }            
            }

        }
        else{
            for(int i=0; i<n; ++i){ // number of rings/strips
                for(int pxl=0; pxl<type[i]; ++pxl){ // number of pixels per ring/strip
                    lights[i].setPixelColor(i,0,0,0);
                }            
            }

        }
        show();
    }

    void set(char _mode){
        mode = _mode;
    }

    void shine(){
        ++cnt;
        
        switch(mode){
            case State::NORMAL:
            normal();
            break;
            case State::E_STOP:
            e_stop();
            break;
        default:
            break;
        }    
    }
};


#endif


