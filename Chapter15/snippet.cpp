void setup() { 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    if (inByte == '1') {
      Serial.print("Turn LED on\n");
      digitalWrite(LED_BUILTIN, HIGH);
    } else if (inByte == '0') {
      Serial.print("Turn LED off\n");
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      Serial.print("Ignore byte ");
      Serial.print(inByte);
      Serial.print("\n");
    }
    delay(500);
  }
}

