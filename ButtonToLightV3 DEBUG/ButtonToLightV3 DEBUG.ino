#include <WiFiNINA.h>

//char ssid[] = "";
//char pass[] = "";
char ssid[] = "";
char pass[] = "";
int status = WL_IDLE_STATUS;  // the Wifi radio's status
int HTTP_PORT = 80;
String HTTP_METHOD = "GET";            // or "POST"
char HOST_NAME[] = "maker.ifttt.com";  // hostname of web server:
String PATH_NAME1 = "/trigger/";
String PATH_NAME2 = "/json/with/key/yourkeygoeshere";
WiFiClient client;
int ButtonValue = 0;
int Button = 3;

void setup() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  pinMode(Button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(2000);

  Serial.println("----------------------------------------");
}

void loop() {
  ButtonValue = digitalRead(Button);
  if (ButtonValue == 0) {
    Serial.println("button pressed!");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
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

      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } else {  // if not connected:
      Serial.println("connection failed");
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  }
  delay(1000);
}