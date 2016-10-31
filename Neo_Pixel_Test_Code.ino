#include <Adafruit_NeoPixel.h>
#define left_light 5
#define right_light 4
Adafruit_NeoPixel left_Headlight = Adafruit_NeoPixel(15,left_light);
Adafruit_NeoPixel right_Headlight = Adafruit_NeoPixel(15,right_light);
void setup() {
  // put your setup code here, to run once:
  left_Headlight.begin();
  left_Headlight.show();
  right_Headlight.begin();
  right_Headlight.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  //if in normal use:
  //rainbow();
  // if estop:
  left_Headlight.setBrightness(30);
  right_Headlight.setBrightness(30);
  for(int n = 0; n<15; n++){
    left_Headlight.setPixelColor(n, 255, 0, 0);
    right_Headlight.setPixelColor(n, 255, 0, 0);
  }
  left_Headlight.show();
  right_Headlight.show();
  delay(100);
  for(int n = 0; n<15; n++){
    left_Headlight.setPixelColor(n, 0, 0, 0);
    right_Headlight.setPixelColor(n, 0, 0, 0);
    left_Headlight.show();
    right_Headlight.show();
  }
  delay(100);
}

void rainbow(){
  for(int i = 0; i < 15; i++){
    int blue = random(125);
    int red = random(125);
    int green = random(125);
    left_Headlight.setPixelColor(i, red, green, blue);
    right_Headlight.setPixelColor(i, red, green, blue);
    left_Headlight.setBrightness(30);
    right_Headlight.setBrightness(30);
    left_Headlight.show();
    right_Headlight.show();
    delay(50);
  }
  for(int i = 15; i>0; i--){
    left_Headlight.setPixelColor(i, 0,0,0);
    right_Headlight.setPixelColor(i,0,0,0);
    left_Headlight.setBrightness(30);
    right_Headlight.setBrightness(30);
    left_Headlight.show();
    right_Headlight.show();
  }
  
}

