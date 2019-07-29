String id = "12W-001"; //Enter LED plate's unique ID inside the quotations

int a1 = 13;
int a2 = 12;
int a3 = 11;
int a4 = 10;
int b1 = 9;
int b2 = 8;
int b3 = 7;
int b4 = 6;
int c1 = 5;
int c2 = 4;
int c3 = 3;
int c4 = 2;

int leds[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(25);
}

void loop() {

  recvWithStartEndMarkers();
  showNewData();

}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        //Serial.println(receivedChars);
        if (receivedChars[0] == 's') {
          Serial.println("12" + id);
        } else {
          for (int i = 0; i < 12; i++) {
            leds[i] = floor((((int)receivedChars[i]) - 1)*2.55);
          }
          analogWrite(a1, leds[0]);
          analogWrite(a2, leds[1]);
          analogWrite(a3, leds[2]);
          analogWrite(a4, leds[3]);
          analogWrite(b1, leds[4]);
          analogWrite(b2, leds[5]);
          analogWrite(b3, leds[6]);
          analogWrite(b4, leds[7]);
          analogWrite(c1, leds[8]);
          analogWrite(c2, leds[9]);
          analogWrite(c3, leds[10]);
          analogWrite(c4, leds[11]);
        }
        newData = false;
    }
}
