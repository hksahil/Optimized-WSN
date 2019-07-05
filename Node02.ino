/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
        == Node 02 (Child of Master node 00) ==    
*/
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 02;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t node00 = 00;    // Address of the other node in Octal format
const unsigned long interval = 10;  //ms  // How often to send data to the other unit
unsigned long last_sent;            // When did we last send?
int val = 0;
int sensor = 7;
void setup() {
  pinMode(sensor, INPUT);
  SPI.begin();
  Serial.begin(9600);
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}
void loop() {
  network.update();
  //===== Sending =====//
  unsigned long now = millis();
  if (now - last_sent >= interval) {   // If it's time to send a data, send it!
    last_sent = now;
    //unsigned long potValue = analogRead(A0);
    //unsigned long ledBrightness = map(potValue, 0, 1023, 0, 255);
    val = digitalRead(sensor);
    RF24NetworkHeader header(node00);   // (Address where the data is going)
    if(val==1)
    {
    bool ok = network.write(header, &val, sizeof(val)); // Send the data
    }
  }
}
