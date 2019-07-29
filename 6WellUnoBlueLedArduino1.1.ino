String id = "6W-001"; //Enter LED plate's unique ID inside the quotations
int a1 = 11;
int a2 = 6;
int a3 = 3;
int b1 = 10;
int b2 = 9;
int b3 = 5;

int leds[] = {0, 0, 0, 0, 0, 0};

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
          Serial.println("06" + id);
        } else {
          for (int i = 0; i < 6; i++) {
            leds[i] = floor((((int)receivedChars[i]) - 1)*2.55);
          }
          analogWrite(a1, leds[0]);
          analogWrite(a2, leds[1]);
          analogWrite(a3, leds[2]);
          analogWrite(b1, leds[3]);
          analogWrite(b2, leds[4]);
          analogWrite(b3, leds[5]);
        }
        newData = false;
    }
}
