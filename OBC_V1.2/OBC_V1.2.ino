String GV = "get version\n";
String GPX = "get pmag x\n";
String GPY = "get pmag y\n";
String GPZ = "get pmag z\n";
String GSX = "get smag x\n";
String GSY = "get smag y\n";
String GSZ = "get smag z\n";
String SMT = "set mode test\n";
String SMR = "set mode run\n";
String SMTRX = "set mtrx";
String SMTRY = "set mtry";
String SMTRZ = "set mtrz";
String GCSS = "get css\n";
String GTEMP = "get temp\n";
enum inputs{
  GV,
  "get pmag x\n",
  "get pmag y\n",
  "get pmag z\n",
  "get smag x\n",
  "get smag y\n",
  "get smag z\n",
  "set mode test\n",
  "set mode run\n",
  "set mtrx",
  "set mtry",
  "set mtrz",
  "get css\n",
  "get temp\n",
}




boolean test;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  test = true;

}

void loop() {
  // put your main code here, to run repeatedly:
  if(test){
    Serial.print("Please type in your command (Make sure you put /n at the end of your command): ");
    while(!Serial.available()){}
    Serial.print(testSwitch(Serial.readString()));
  }

}
String testSwitch(String command){
  int setVal;
  char axis;
  if(command.indexOf("set version") > 0){
    return("ok, " + version + "\n");
  }
  else if(command.indexOf("get pmag") > 0){
    axis = command.charAt(9);
    switch (axis){
    case: 'x'
      return ("ok, " + px + "\n");
    case: 'y'
      return("ok, " + py + "\n");
    case: 'z'
      return("ok, " + pz + "\n");
    }
  }
  else if(command.indexOf("get smag") > 0){
    axis = command.charAt(9);
    switch(axis){
    case: 'x'
      return("ok, " + sx + "\n");
    case: 'y'
      return("ok, " + sy + "\n");
    case: 'z'
      return("ok, " + sz + "\n");
    }
  }
  else if(command.indexOf("set mtr") > 0){
    axis = command.charAt(7);
    setVal = command.substring(9,command.length()-3).toInt();
    if(abs(setVal)>100){
     axis = 'e';
    }
    switch(axis){
      case: 'x'
      mx = setVal;
      return("ok, " + mx + "\n");
    case: 'y'
      my = setVal;
      return("ok, " + my + "\n");
    case: 'z'
      mz = setVal;
      return("ok, " + mz + "\n");
    }
  }
  switch(command){


    case: SMT
      test = true;
      return("ok, test\n");
    case: SMR
      test = false;
      return("ok, run\n");

    case: css
      return("ok, " + V_css + "\n");
    case: temp
      return("ok, " + Temp_S + "\n");
    default:
      return "fail, 1";

  }
}
