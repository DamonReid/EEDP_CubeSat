#include <SoftwareSerial.h>
#include <QMC5883LCompass.h>

//pins
#define mtrX 9 //hacky X+
#define mtrY 10 //hacky X-
#define mtrZ 11
#define CSSPin A0
#define tempPin A1
#define OBCtransmit 14
#define magRX 18
#define magTX 19

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

SoftwareSerial Mag = SoftwareSerial(magRX, magTX); //RX, TX

void setup() {
  // put your setup code here, to run once:
  test = true;
  pinMode(CSSPin,INPUT);
  pinMode(tempPin,INPUT);
  pinMode(OBCtransmit,OUTPUT);
  pinMode(mtrX,OUTPUT);
  pinMode(mtrY,OUTPUT);
  pinMode(mtrZ,OUTPUT);
  pinMode(magRX,INPUT);
  pinMode(magTX,OUTPUT);
  Serial.begin(9600);
  Mag.begin(9600);
  smag.init(); // initialises magnetometer chip
}

static void loop() {
  // put your main code here, to run repeatedly:
  if(Mag.available()){
   char *readIn = Mag.readBytesUntil('\n', serialIn, sizeof(serialIn) - 1); 
   if(readIn[0] == 'x'){
      Serial.println(String(readIn));
      setPmag(readIn);
   }
  }
  if(test){
    Serial.println("test");
    digitalWrite(OBCtransmit,LOW);
    //Serial.println("Please type in your command (Make sure you put \n at the end of your command): ");
    if(Serial.available()){
    String serialReturn = testSwitch(Serial.readString());
    digitalWrite(OBCtransmit,HIGH);
    Serial.println(serialReturn);
    delay(5);
    digitalWrite(OBCtransmit,LOW);
    }
  }
  else{
    digitalWrite(OBCtransmit,LOW);
    if(Serial.available()){
      if(Serial.readString().equals("set mode test\n")){
        test = true;
        digitalWrite(OBCtransmit,HIGH);
        Serial.println("ok, test");
        delay(5);
        digitalWrite(OBCtransmit,LOW);
      }
      else{
        digitalWrite(OBCtransmit,HIGH);
        Serial.println("fail, 1");
        delay(5);
        digitalWrite(OBCtransmit,LOW);
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
    char axis2;
    axis2 = command.charAt(9);
    Serial.println(axis2);
    switch(axis2){
    case 'x':
      Serial.println("getSmag x");
      return("ok, " + String(smag.getX()));
    case 'y':
      Serial.println("getSmag y");
      return("ok, " + String(smag.getY()));
    case 'z':
      Serial.println("getSmag z");
      return("ok, " + String(smag.getZ()));
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
    String valString = command.substring(9,command.length()-1);
    setVal = valString.toFloat();
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
  analogWrite(mtrX,mtr[0]);
  analogWrite(mtrY,mtr[1]);
  analogWrite(mtrZ,mtr[2]);
}

void hackySetMTRX(){
  if(curr[0]>=0){
    int forward = map(curr[0]*100,0,1000,0,255);
    analogWrite(mtrX,forward);
  }
  else{
    int backwards = map(curr[0]*100,-1000,0,0,255);
    analogWrite(mtrY,backwards);
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
    //Serial.println("Incorrect input");
    return;
  }
}

float getCSS(){
  float value = analogRead(CSSPin);
  //Serial.println(value); // this is a testing placeholder for us atm - DJTR
  float V_css = value/10.6;
  return V_css;
}

float getSmag1(char axis) {
    Serial.print("smag for ");
    Serial.println(axis);
    float xVal, yVal, zVal;
    switch (axis) {
        case 'x':
            xVal = 2; //smag.getX();
            Serial.println("xVal: " + String(xVal));
            return xVal;
        case 'y':
            yVal = 3; //smag.getY();
            Serial.println("yVal: " + String(yVal));
            return yVal;
        case 'z':
            zVal = 4; //smag.getZ();
            Serial.println("zVal: " + String(zVal));
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
