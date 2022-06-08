#include <QMC5883LCompass.h>

QMC5883LCompass smag;
boolean test;
char buffer[15]
char serialIn[100];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  test = true;
  float systemVersion = 1.2;
  int CSSPin = A0; // change as required
  smag.init();
}

static void loop() {
  // put your main code here, to run repeatedly:
  if(test){
    Serial.print("Please type in your command (Make sure you put /n at the end of your command): ");
    while(!Serial.available()){}
    Serial.print(testSwitch(Serial.readString()));
  }
}
i
String testSwitch(String command){
  int setVal;
  char axis;
  if(command.indexOf("get pmag") == 0){
    axis = command.charAt(9);
    switch (axis){
    case 'x':
      px = getPmag('x');
      return ("ok, " + px + "\n");
    case 'y':
      py = getPmag('y');
      return("ok, " + py + "\n");
    case 'z':
      pz = getPmag('z');
      return("ok, " + pz + "\n");
    }
  }
  else if(command.indexOf("get smag") == 0){
    axis = command.charAt(9);
    switch(axis){
    case 'x':
      //sx = getSmag('x');
      return("ok, " + sx + "\n");
    case 'y':
      //sy = getSmag('y');
      return("ok, " + sy + "\n");
    case 'z':
      //sz = getSmag('z');
      return("ok, " + sz + "\n");
    }
  }
  else if(command.indexOf("get css") == 0){
    V_css = getCSS();
    return("ok, " + V_css + "\n");
  }
  else if(command.indexOf("get temp") == 0){
    //Temp_S = getTemp();
    return("ok, " + Temp_S + "\n");
  }
  else if(command.indexOf("get version") == 0){
    return("ok, " + systemVersion + "\n");
  }
  else if(command.indexOf("set mtr") == 0){
    axis = command.charAt(7);
    setVal = command.substring(9,command.length()-3).toFloat();
    if(abs(setVal)>100){
     axis = 'e';
    }
    switch(axis){
      case 'x':
        float mx = setVal;
        return("ok, " + mx + "\n");
      case 'y':
        float my = setVal;
        return("ok, " + my + "\n");
      case 'z':
        float mz = setVal;
        return("ok, " + mz + "\n");
    }
  }
  else if(command.indexOf("set mode") == 0){
    if(command.indexOf("test") == 9){
      test = true;
      return("ok, test\n");
    }
    else if(command.indexOf("run") == 9){
      test = false;
      return("ok, run\n");
    }
  }
  else{
    return "fail, 1";
  }
}

float getPmag(char axis){
    float xVal, yVal, zVal;
  while (!Serial.available()) {}
  int input = Serial.readBytesUntil('\n', serialIn, sizeof(serialIn) - 1);

  Serial.println();
  Serial.print("Captured String is ");
  Serial.println(serialIn); //prints string to serial port out

  char *in1 = strtok(serialIn, ",");
  String i1 = String(in1);
  Serial.println(in1);

  char *in2 = strtok(NULL,  ",");
  String i2 = String(in2);
  Serial.println(in2);

  char *in3 = strtok(NULL,  ",");
  String i3 = String(in3);
  Serial.println(in3);

  switch (axis) {
    case 'x':
      if (i1.charAt(0) == 'x') {
        char *xLoc = strtok(in1, ": ");
        char *xLoc1 = strtok(NULL, " ");
        String xRoot =  String(xLoc1);
        xRoot.substring(4, sizeof(xRoot) - 1);

        Serial.println(xRoot);
        xVal = xRoot.toFloat();
      }
      else if (i2.charAt(0) == 'x' || i2.charAt(1) == 'x') {
        char *xLoc = strtok(in2, ": ");
        char *xLoc1 = strtok(NULL, " ");
        String xRoot =  String(xLoc1);
        xRoot.substring(4, sizeof(xRoot) - 1);

        Serial.println(xRoot);
        xVal = xRoot.toFloat();
      }
      else if (i3.charAt(0) == 'x' || i3.charAt(1) == 'x') {
        char *xLoc = strtok(in3, ": ");
        char *xLoc1 = strtok(NULL, " ");
        String xRoot =  String(xLoc1);
        xRoot.substring(4, sizeof(xRoot) - 1);

        Serial.println(xRoot);
        xVal = xRoot.toFloat();
      }

      return xVal;

    case 'y':
      if (i1.charAt(0) == 'y') {
        char *yLoc = strtok(in1, ": ");
        char *yLoc1 = strtok(NULL, " ");
        String yRoot =  String(yLoc1);
        yRoot.substring(4, sizeof(yRoot) - 1);

        Serial.println(yRoot);
        yVal = yRoot.toFloat();
      }
      else if (i2.charAt(0) == 'y' || i2.charAt(1) == 'y') {
        char *yLoc = strtok(in2, ": ");
        char *yLoc1 = strtok(NULL, " ");
        String yRoot =  String(yLoc1);
        yRoot.substring(4, sizeof(yRoot) - 1);

        Serial.println(yRoot);
        yVal = yRoot.toFloat();
      }
      else if (i3.charAt(0) == 'y' || i3.charAt(1) == 'y') {
        char *yLoc = strtok(in3, ": ");
        char *yLoc1 = strtok(NULL, " ");
        String yRoot =  String(yLoc1);
        yRoot.substring(4, sizeof(yRoot) - 1);

        Serial.println(yRoot);
        yVal = yRoot.toFloat();
      }

      return yVal;

    case 'z':
      if (i1.charAt(0) == 'z') {
        char *zLoc = strtok(in1, ": ");
        char *zLoc1 = strtok(NULL, " ");
        String zRoot =  String(zLoc1);
        zRoot.substring(4, sizeof(zRoot) - 1);

        Serial.println(zRoot);
        zVal = zRoot.toFloat();
      }
      else if (i2.charAt(0) == 'z' || i2.charAt(1) == 'z') {
        char *zLoc = strtok(in2, ": ");
        char *zLoc1 = strtok(NULL, " ");
        String zRoot =  String(zLoc1);
        zRoot.substring(4, sizeof(zRoot) - 1);

        Serial.println(zRoot);
        zVal = zRoot.toFloat();
      }
      else if (i3.charAt(0) == 'x' || i3.charAt(1) == 'z') {
        char *zLoc = strtok(in3, ": ");
        char *zLoc1 = strtok(NULL, " ");
        String zRoot =  String(zLoc1);
        zRoot.substring(4, sizeof(zRoot) - 1);

        Serial.println(zRoot);
        zVal = zRoot.toFloat();
      }

      return zVal;

    default:
      return "fail, 1";

  }
}

float getCSS(){
  float value = analogRead(CSSPin);
  Serial.println(value); // this is a testing placeholder for us atm - DJTR
  float V_css = value/204.6;
  return V_css;
}

float getSmag(char axis) {
    float xVal, yVal, zVal;

    switch (axis) {
        case 'x':
            xVal = smag.getX();
            return xVal;
        case 'y':
            yVal = smag.getY();
            return yVal;
        case 'z':
            zVal = smag.getZ();
            return zVal;
        default:
            return "fail, 1";
    }
}
