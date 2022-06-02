boolean test;
char buffer[15]

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
  if(command.indexOf("get pmag") == 0){
    axis = command.charAt(9);
    switch (axis){
    case 'x':
      return ("ok, " + px + "\n");
    case 'y':
      return("ok, " + py + "\n");
    case 'z':
      return("ok, " + pz + "\n");
    }
  }
  else if(command.indexOf("get smag") == 0){
    axis = command.charAt(9);
    switch(axis){
    case 'x':
      return("ok, " + sx + "\n");
    case 'y':
      return("ok, " + sy + "\n");
    case 'z':
      return("ok, " + sz + "\n");
    }
  }
  else if(command.indexOf("get css") == 0){
    return("ok, " + V_css + "\n");
  }
  else if(command.indexOf("get temp") == 0){
    return("ok, " + Temp_S + "\n");
  }
  else if(command.indexOf("set version") == 0){
    return("ok, " + version + "\n");
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
      default:
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
