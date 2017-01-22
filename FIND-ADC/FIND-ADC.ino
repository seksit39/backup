void setup() {
  Serial.begin(115200);

}

void loop() {
  
  int input = analogRead(A0);
  if(input > 3)
    Serial.println(input);
}
