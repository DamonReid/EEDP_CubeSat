#include <QMC5883LCompass.h>

const char *delimiter = "xyz:\n";

QMC5883LCompass smag;
boolean test;
char buffer[15]
char serialIn[100];
float pmag[3] = { NULL };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  test = true;
  float systemVersion = 1.2;
  int CSSPin = A0; // change as required
  int tempPin = A1; // change as required
  smag.init(); // initialises magnetometer chip
}

static void loop() {
  // put your main code here, to run repeatedly:
  char *read_from_pmag_serial 
  getPmag(*read_from_pmag_serial);
  if(test){
    Serial.print("Please type in your command (Make sure you put /n at the end of your command): ");
    while(!Serial.available()){}
    Serial.println(testSwitch(Serial.readString()));
  }
}

String testSwitch(String command){
  int setVal;
  char axis;
  if(command.indexOf("get pmag") == 0){
    axis = command.charAt(9);
    switch (axis){
    case 'x':
      return ("ok, " + pmag[0]);
    case 'y':
      py = getPmag('y');
      return("ok, " + pmag[1]);
    case 'z':
      return("ok, " + pmag[2]);
    default:
        return "fail, 1";
    }
  }
  else if(command.indexOf("get smag") == 0){
    axis = command.charAt(9);
    switch(axis){
    case 'x':
      sx = getSmag('x');
      return("ok, " + sx);
    case 'y':
      sy = getSmag('y');
      return("ok, " + sy);
    case 'z':
      sz = getSmag('z');
      return("ok, " + sz);
    default:
        return "fail, 1";
    }
  }
  else if(command.indexOf("get css") == 0){
    V_css = getCSS();
    return("ok, " + V_css);
  }
  else if(command.indexOf("get temp") == 0){
    Temp_S = getTemp();
    return("ok, " + Temp_S);
  }
  else if(command.indexOf("get version") == 0){
    return("ok, " + systemVersion);
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
        return("ok, " + mx);
      case 'y':
        float my = setVal;
        return("ok, " + my);
      case 'z':
        float mz = setVal;
        return("ok, " + mz);
      default:
        return "fail, 1";
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

float setPmag(char *serialIn){
  if(serialIn[0] == 'x'){
    float newMag[3];
    char *in1 = strtok(serialIn, delimiter);
    newMag[0] = atof(in1);
    char *in2 = strtok(NULL, delimiter);
    newMag[1] = atof(in2);
    char *in3 = strtok(NULL, delimiter);
    newMag[2] = atof(in3);
    if(pmag[0] == NULL){ 
      memcpy(pmag,newMag,sizeof newMag); 
    }
    else{
      for(int i = 0; i<3; i++){
        if(abs(newMag[i]-pmag[i])>(pmag[i]/2)){
          Serial.println("Incorrect input, mag value has changed by more than 0.5x");
          return;
        }  
      }
      memcpy(pmag,newMag,sizeof newMag);
    }
  }
  else{
    Serial.println("Incorrect input");
    return;
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

float getTemp(){
    float sensorIn, value, value1, tempVal;

    sensorIn = analogRead(tempPin);
    value = (sensorIn/1023)*5;
    value1 = (5-value)/value*4700;
    tempVal = 1/(log(value1/10000)/3950 + 1/(25+273.15)) - 273.15;

    return tempVal;
}
