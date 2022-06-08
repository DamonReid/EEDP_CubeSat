#include <math.h>

void setup() {
    Serial.begin(9600);
    int tempPin = A1;
}
void loop() {
    double sensorIn, value, value1, tempVal;

    sensorIn = analogRead(tempPin);
    value = (sensorIn/1023)*5;
    value1 = (5-value)/value*4700;
    tempVal = 1/(log(value1/10000)/3950 + 1/(25+273.15)) - 273.15;
}


