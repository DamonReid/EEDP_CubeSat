String readString; //main captured String
String angle; //data String
String fuel;
String speed1;
String altidude;

int ind1; // , locations
int ind2;
int ind3;


void setup() {
    Serial.begin(9600);
    Serial.println("Serial Delimit Test"); // so I can keep track of what is loaded
}

void loop() {
    if (Serial.available())  {
        char c = Serial.read();  //gets one byte from serial buffer
        if (c == '\n') {
            Serial.println();
            Serial.print("Captured String is : ");
            Serial.println(readString); //prints string to serial port out

            ind1 = readString.indexOf('x:');  //finds location of first ,
            x_value = readString.substring(0, ind1);   //captures first data String
            ind2 = readString.indexOf('y:', ind1+1 );   //finds location of second ,
            y_value = readString.substring(ind1+1, ind2+1);   //captures second data String
            ind3 = readString.indexOf('z:', ind2+1 );
            z_value = readString.substring(ind2+1, ind3+1);

            Serial.print("angle = ");
            Serial.println(angle);
            Serial.print("fuel = ");
            Serial.println(fuel);
            Serial.print("speed = ");
            Serial.println(speed1);
            Serial.print("altidude = ");
            Serial.println(altidude);
            Serial.println();
            Serial.println();

            readString=""; //clears variable for new input
            angle="";
            fuel="";
            speed1="";
            altidude="";
        }
        else {
            readString += c; //makes the string readString
        }
    }
}