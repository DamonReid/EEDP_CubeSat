char serialIn[100];
float xVal;
float yVal;
float zVal;

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

  char *in1 = strtok(serialIn, ",");
  String i1 = String(in1);
  Serial.println(in1);

  char *in2 = strtok(NULL,  ",");
  String i2 = String(in2);
  Serial.println(in2);

  char *in3 = strtok(NULL,  ",");
  String i3 = String(in3);
  Serial.println(in3);

  switch (pmagAxis) {
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
