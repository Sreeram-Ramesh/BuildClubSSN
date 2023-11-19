// Transmitter Code

// Push button pin D4
// Flow Sensor pin A0
// Receiver pin 2
// Transmitter pin 3

#include <SoftwareSerial.h>

SoftwareSerial link(5, 6); // Rx, Tx

const int flowsensorPin = A0;
const int pushButton = 4;
int flowsensorValue;
int buttonState;
bool stateVariable = true;

void setup() {
  // put your setup code here, to run once.
  pinMode(flowsensorPin, INPUT);
  pinMode(pushButton, INPUT);

  // begin serial communication between transmitter (Uno 3) and receiver (esp32).
  link.begin(9600);
  // begin serial communication to use the serial monitor.
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly.

  flowsensorValue = analogRead(flowsensorPin);
  buttonState = digitalRead(pushButton);

  // if condition to prevent continuous writing of data on pressing the momentary switch.  
  if (buttonState == HIGH && stateVariable == true) {
    write_data();
    stateVariable = false;
  }
  else if (buttonState == LOW && stateVariable == false) {
    stateVariable = true;
  }

}

// write_data function to write the recorded data of the water flow sensor
// into the serial monitor and transmit it to the esp32. 
void write_data() {
  Serial.print("Flow sensor value: ");
  Serial.println(flowsensorValue);
  
  link.println(flowsensorValue);

}