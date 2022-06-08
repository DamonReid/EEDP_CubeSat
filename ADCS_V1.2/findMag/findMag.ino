const char *delimiter = "xyz:\n";
char serialIn[100];
float pmag[3] = { NULL };

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Delimit Test");
}

void loop() {
  while (!Serial.available()) {}
  int input = Serial.readBytesUntil('\n', serialIn, sizeof(serialIn) - 1);
  Serial.println();
  Serial.print("Captured String is ");
  Serial.println(serialIn); //prints string to serial port out
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
  for(int i = 0; i<3; i++){
    Serial.println(pmag[i]);
  }
}

void setMagValues(char *serialIn){
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
