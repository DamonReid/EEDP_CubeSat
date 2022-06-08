int CSSPin = A0; // change as required

void setup() {
   Serial.begin(9600);
}

void loop() {
  int value = analogRead(CSSPin);
  Serial.println(value);
  int V_css = value/204.6;
  
  return V_css;
}
