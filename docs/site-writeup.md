---
layout: page
permalink: /projects/attention-button
permalink_name: /attention-button
title: Attention Button Project
---

<link rel="stylesheet" href="/assets/css/projects.css">

## The Concept

Handling academics and commitments often means ignoring digital distractions. The Attention Button was created to offer a solution. The physical push button I modeled and printed, when pressed, triggers the lights in my room to turn bright pink, providing an immediate visual cue that someone is trying to get my attention.

## Technology Stack

<div class="tags-container">
    <div class="language-tag" style="color: black;">Arduino MKR 1010</div>
    <div class="language-tag" style="color: black;">WiFiNINA</div>
    <div class="language-tag" style="color: black;">Fusion360</div>
    <div class="language-tag" style="color: black;">IFTTT</div>
</div>

## Give it a Try

Pressing this button will change the color of the lights in my room! Please don't abuse this feature.
{% raw %}

<style>
  .push-button {
    display: inline-block;
    padding: 10px 20px;
    background-color: #4CAF50;
    color: white;
    font-size: 16px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
  }

  .push-button:hover {
    background-color: #45a049;
  }
</style>

<form method="post" action="https://maker.ifttt.com/trigger/short_press/with/key/REDACTED">
  <button class="push-button" type="submit">Press to Activate</button>
</form>
{% endraw %}
## Code Snippet

```cpp
#include <WiFiNINA.h>

char ssid[] = ""; //insert your network name
char pass[] = ""; //insert your network password

int status = WL_IDLE_STATUS;  // the Wifi radio's status
int HTTP_PORT = 80;
String HTTP_METHOD = "GET";            // or "POST"
char HOST_NAME[] = "maker.ifttt.com";  // hostname of web server:
String PATH_NAME1 = "/trigger/";
String PATH_NAME2 = "/json/with/key/REDACTED";
WiFiClient client;
int ledPin = 5;
int ButtonValue = 0;
int Button = 3;

void setup() {
  pinMode(ledPin, OUTPUT); // set the pin as an output
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  pinMode(Button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //Initialize serial and wait for port to open:
  //Serial.begin(9600);
  //while (!Serial);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    //Serial.print("Attempting to connect to network: ");
    //Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  //Serial.println("You're connected to the network");
   for (int i = 0; i < 10; i++) { // blink the LED 10 times
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(100); // wait for 100 milliseconds
    digitalWrite(ledPin, LOW); // turn the LED off
    delay(100); // wait for 100 milliseconds
  }
  //Serial.println("----------------------------------------");
}

void loop() {
  ButtonValue = digitalRead(Button);
  if (ButtonValue == 0) {
    //Serial.println("button pressed!");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      //Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println(HTTP_METHOD + " " + PATH_NAME1 + "short_press" + PATH_NAME2 + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println();  // end HTTP header


      while (client.connected()) {
        if (client.available()) {
          // read an incoming byte from the server and print it to serial monitor:
          char c = client.read();
          Serial.print(c);
          //should say Congratulations! You've fired the short_press json event
        }
      }
        digitalWrite(ledPin, HIGH); // turn the LED on
        delay(1000); // wait for one second
        digitalWrite(ledPin, LOW); // turn the LED off
        delay(1000); // wait for one second
        digitalWrite(ledPin, HIGH); // turn the LED on
        delay(1000); // wait for one second
        digitalWrite(ledPin, LOW); // turn the LED off
        delay(1000); // wait for one second
        digitalWrite(ledPin, HIGH); // turn the LED on
        delay(1000); // wait for one second
        digitalWrite(ledPin, LOW); // turn the LED off
        delay(1000); // wait for one second
      // the server's disconnected, stop the client:
      client.stop();
      //Serial.println();
      //Serial.println("disconnected");
    } else {  // if not connected:
      //Serial.println("connection failed");
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  }
  delay(1000);
}
```
