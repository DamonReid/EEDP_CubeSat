String readString; //main captured String
String x_value;
String y_value;
String z_value;

int ind1; // locations
int ind2;
int ind3;
int ind4;

void setup() {
    Serial.begin(9600);
    Serial.println("Serial Delimit Test"); // so I can keep track of what is loaded
}

void loop() {
    if (Serial.available())  {
        char c = Serial.read();  //gets one byte from serial buffer
        if (c == '\n') {
            Serial.println();
            Serial.print("Captured String is: ");
            Serial.println(readString); //prints string to serial port out

            ind1 = readString.indexOf('x:');  //finds location of first ,
            ind2 = readString.indexOf('y:', ind1+1 );   //finds location of second ,
            ind3 = readString.indexOf('z:', ind2+1 );
            ind4 = readString.indexOf('c', ind3+1);

            x_value = readString.substring(ind1, ind2-1);   //captures first data String
            y_value = readString.substring(ind2, ind3-1);   //captures second data String
            z_value = readString.substring(ind3, ind4-1);

            Serial.print("X = ");
            Serial.println(x_value);
            Serial.print("Y = ");
            Serial.println(y_value);
            Serial.print("Z = ");
            Serial.println(z_value);

            Serial.println();

            readString = ""; //clears variable for new input
            x_value = "";
            y_value = "";
            z_value = "";
        }
        else {
            readString += c; //makes the string readString
        }
    }
}