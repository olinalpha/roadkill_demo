//Basic Hind Brain Roadkill Test Code
//Version 2.0 10/31/16 1am WHEEEE :)

//Set up Arduino Ports and Pins to support Robot
int ledPin = 13;      // Robot alive blinky light pin
int actOutPin = 11;   // create name for a binary output port 
int eStopPin = 6;      //create name for E-Stop reading pin
int delayPeriod = 50; // Hindbrain loop delay
int sharpDistance1 = 0; // create name for sharp IR 1 analog input 0
char command = 'g';   // 'g' is go command from midbrain 's' is stop
char hBrainStatus = 'r'; // Hindbrain status 'r' running, 's' stopped, 'e' E-Stopped

void setup() {
  // put your setup code here, to run once:
  pinMode (ledPin, OUTPUT); // Sets up Blinky "alive" light
  pinMode (actOutPin, OUTPUT); // Sets Act binary output port
  pinMode (eStopPin, INPUT); // Sets up sense unput of E-Stop button
  Serial.begin(9600);       // Send and recieve at 9600 baud
  Serial.println ("Have Midbrain send 1 or 0 to Hindbrain pin 4");

}

//Run Hindbrain loop until commanded to stop by Midbrain
void loop() {
  //Read Midbrain commands
  if (Serial.available()) {
    command = Serial.read();     // Read character command from serial monitor
    Serial.println ("Midbrain sent:");
    Serial.println (command);     // Print Midbrain command in serial monitor
  }
  //Serial.println(digitalRead(eStopPin));
  //Serial.println(command);
  
  
  //Sense: Read Robot Sensors
  //Serial.println(readEstop());  // read and print
  if (readEstop() == 0)  {
    hBrainStatus = 'e'; //IF e-sTOP SWITCH TRIGGERED SET hINDBRAIN STATUS to E-Stopped
  }
  else hBrainStatus = 'r';  // else set status to running
  //Serial.println (sharpRange(sharpDistance1));  //Print range from Sharp1 ***************(debug only)
  float SharpRange1 = sharpRange(sharpRange(sharpDistance1)); // Read Sharp range 1
  Serial.println(SharpRange1);
  
  //Think: Run low level cognition and safety code
  if (command != 's')  {
    blink();  //blink Hindbrain running LED
  }


  //Act: Run actuators and behavior lights
  toggleActPin4(command);   //print hindbriain status on serial monitor

  //Write status data up to Midbrain
  if (hBrainStatus == 'e') {
    Serial.println(" Hindbrain e-stopped."); // Print hindbrain status on serial monitor
  }
  if (hBrainStatus == 's') {
    Serial.println(" Hindbrain stopped.");
  }
  
}


//Hindbrain Functions*****************************

//Sense Functions
boolean readEstop(){
  boolean eStopTriggered = digitalRead(eStopPin);
  return eStopTriggered;
}
float sharpRange (int sensornum) {  //Read Sharp range, return rangeg in cm
  int rawData = analogRead(sensornum);  //V is 0-1023
  float volts = rawData*0.0048828125;   //convert to volts
  float range = 65*pow(volts, -1.10);   //approximate exp data graph function
  return range;
}

//Think Functions
void blink() {
    digitalWrite (ledPin, HIGH);
    delay (delayPeriod);
    digitalWrite(ledPin, LOW);
    delay (delayPeriod);
}


//Act Functions
void toggleActPin4 (char pinState) {  //this function sets Act pin 4 to either HIGH or LOW
  if (pinState == '1') {
    digitalWrite(actOutPin, HIGH);
  }
  else if (pinState != '1') {
    digitalWrite(actOutPin, LOW);
  }
}

