// the setup function runs once when you press reset or power the board
int ButtonValue = 0;
int Button = 3;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  ButtonValue = digitalRead(Button);
  if (ButtonValue != 0)
  {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
      delay(1000);
}
