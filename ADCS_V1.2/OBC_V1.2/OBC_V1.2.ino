#include <SoftwareSerial.h>
#include <QMC5883LCompass.h>

const String systemVersion = "1.3";
const char *delimiter = "xyz:\n";
const float kw = 2.3809*1/100000;
const float N = 2000;
const float A = 0.0001;

QMC5883LCompass smag;
boolean test;
char serialIn[100];
float pmag[3] = { NULL };
float maghist[3] = { NULL };
float curr[3] = { NULL };

//pins
int mtrX;
int mtrY;
int mtrZ;
int CSSPin;
int tempPin;
int OBCtransmit;
SoftwareSerial Mag(18, 19); //RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Mag.begin(9600);
  test = true;
  CSSPin = A0; // change as required
  tempPin = A1; // change as required
  OBCtransmit = 14;
  smag.init(); // initialises magnetometer chip
}

static void loop() {
  // put your main code here, to run repeatedly:
  if(Mag.available()){
   setPmag(Mag.readBytesUntil('\n', serialIn, sizeof(serialIn) - 1));
  }
  if(test){
    OBCtransmit = LOW;
    //Serial.println("Please type in your command (Make sure you put \n at the end of your command): ");
    if(Serial.available()){
    String serialReturn = testSwitch(Serial.readString());
    OBCtransmit = HIGH;
    Serial.println(serialReturn);
    delay(5);
    OBCtransmit = LOW;
    }
  }
  else{
    OBCtransmit = LOW;
    if(Serial.available()){
      if(Serial.readString().equals("set mode test\n")){
        test = true;
        OBCtransmit = HIGH;
        Serial.println("ok, test");
        delay(5);
        OBCtransmit = LOW;
      }
      else{
        OBCtransmit = HIGH;
        Serial.println("fail, 1");
        delay(5);
        OBCtransmit = LOW;
      }
    }
    if(pmag[0] != NULL){
      bDot();
      if(curr[0] != NULL){
        hackySetMTRX();
      }
    } 
  }  
}

String testSwitch(String command){
  float setVal;
  char axis;
  if(command.indexOf("get pmag") == 0){
    axis = command.charAt(9);
    switch (axis){
    case 'x':
      return ("ok, " + String(pmag[0]));
    case 'y':
      return("ok, " + String(pmag[1]));
    case 'z':
      return("ok, " + String(pmag[2]));
    default:
        return "fail, 1";
    }
  }
  else if(command.indexOf("get smag") == 0){
    axis = command.charAt(9);
    switch(axis){
    case 'x':
      float sx = getSmag('x');
      return("ok, " + String(sx));
    case 'y':
      float sy = getSmag('y');
      return("ok, " + String(sy));
    case 'z':
      float sz = getSmag('z');
      return("ok, " + String(sz));
    default:
        return "fail, 1";
    }
  }
  else if(command.indexOf("get css") == 0){
    float V_css = getCSS();
    return("ok, " + String(V_css));
  }
  else if(command.indexOf("get temp") == 0){
    float Temp_S = getTemp();
    return("ok, " + String(Temp_S));
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
        curr[0] = setVal/10;
        return("ok, " + String(setVal));
      case 'y':
        curr[1] = setVal/10;
        return("ok, " + String(setVal));
      case 'z':
        curr[2] = setVal/10;
        return("ok, " + String(setVal));
      default:
        return "fail, 1";
    }
  }
  else if(command.indexOf("set mode") == 0){
    if(command.indexOf("test") == 9){
      test = true;
      return("ok, test");
    }
    else if(command.indexOf("run") == 9){
      test = false;
      return("ok, run");
    }
  }
  else{
    return "fail, 1";
  }
}

void bDot(){
  if(maghist[0] != NULL){
    float k = -kw/(sq(pmag[1])+sq(pmag[2])+sq(pmag[3]));
    for(int axis = 0; axis<3; axis++){
      float m = ((pmag[axis]-maghist[axis])*k);
      float curr = m/(N*A);
      curr = constrain((curr),-10,10);
      
    } 
  }
  memcpy(maghist,pmag,sizeof pmag);
}
void setMTR(){
  int mtr[3];
  for(int axis = 0; axis<3; axis++){
    mtr[axis] = map(curr[axis]*100,-1000,1000,0,255);
  }
  mtrX.analogWrite(mtr[0]);
  mtrY.analogWrite(mtr[1]);
  mtrZ.analogWrite(mtr[2]);
}

void hackySetMTRX(){
  if(curr[0]>=0){
    int forward = map(curr[0]*100,0,1000,0,255);
    mtrX.analogWrite(forward);
  }
  else{
    int backwards = map(curr[0]*100,-1000,0,0,255);
    mtrY.analogWrite(backwards);
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
            return 0;
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
