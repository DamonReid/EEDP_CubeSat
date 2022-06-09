#include <QMC5883LCompass.h>

QMC5883LCompass smag;

void setup() {
    Serial.begin(9600);
    smag.init();
}

void loop() {
    float xVal, yVal, zVal;

    switch (smagAxis) {
        case 'x':
            xVal = smag.getX();
            Serial.print(xVal);
            return xVal;
        case 'y':
            yVal = smag.getY();
            Serial.print(yVal);
            return yVal;
        case 'z':
            zVal = smag.getZ();
            Serial.print(zVal);
            return zVal;
        default:
            return "fail, 1";
    }
}
