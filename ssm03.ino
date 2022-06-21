#define sensorPin 14

uint16_t state, temp, hue;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("begin ok");
  pinMode(sensorPin, INPUT_PULLUP);

}

void loop() {
  //Serial.println("running ok");
  // put your main code here, to run repeatedly:

  if (readSesnor()) {

    if (state == 65535) {
      state = 0;
    }
    
    float actualTemp, actualHue;
    actualTemp = temp / 10.00;
    actualHue = hue / 10.00;
    Serial.print(state);
    Serial.print("    temp: ");
    Serial.print(actualTemp);
    Serial.print("  ");
    Serial.print(" hue:");
    Serial.print(actualHue);

    if (state == 0) {
      Serial.print(" air is clean:");
    }
    else if (state == 1) {
      Serial.print(" The air is not very good:");
    }
    else if (state == 2) {
      Serial.print(" The air is not clean");
    }

    Serial.println("");
  }

   delay(20);
}


bool readSesnor() {
  state = 0;
  hue = 0;
  temp = 0;
  //Serial.println("uj");
  uint32_t mil = millis();
  bool startHead = 0;
  while (digitalRead(sensorPin) == 1) { // 15ms
    //__asm__("nop\n\t");
  }
  // Serial.println(millis() - mil);
  if (millis() - mil > 15) {
    startHead = 1;
    //  Serial.println("ok");
  }
  else {
    // return 0;
  }

  while (digitalRead(sensorPin) == 0) { // 5ms
    //  __asm__("nop\n\t");
  }


  if (startHead == 1) {
    //  read f
    for (byte i = 0; i < 2; i++) {
      mil = millis();
      while (digitalRead(sensorPin) == 1) {
        //  __asm__("nop\n\t");
      }
      if (millis() - mil > 6) {
        state = state << 1;
        state = state + 1;
      }
      else {
        state = state << 1;
      }
      while (digitalRead(sensorPin) == 0) {
        //  __asm__("nop\n\t");
      }
    }
    state = state - 1;

    // ----

    uint32_t tt = 0;
    for (byte i = 0; i < 32; i++) {
      mil = millis();
      while (digitalRead(sensorPin) == 1) {
        // __asm__("nop\n\t");
      }
      if (millis() - mil > 8) {

        tt = tt << 1;
        tt = tt + 1;
      }
      else {
        tt = tt << 1;
      }
      while (digitalRead(sensorPin) == 0) {
        //  __asm__("nop\n\t");
      }
    }

    hue = tt &  0xFFFF;
    temp    = tt >> 16;
    return 1;

    // -----------------------------
    // ****************************

    /*
        for (byte i = 0; i < 16; i++) {
          mil = millis();
          while (digitalRead(sensorPin) == 1) {
            // __asm__("nop\n\t");
          }
          if (millis() - mil > 8) {

            temp = temp << 1;
            temp = temp + 1;
          }
          else {
            temp = temp << 1;
          }
          while (digitalRead(sensorPin) == 0) {
            //  __asm__("nop\n\t");
          }
        }

        for (byte i = 0; i < 16; i++) {
          mil = millis();
          while (digitalRead(sensorPin) == 1) {
            // __asm__("nop\n\t");
          }
          if (millis() - mil > 7) {

            hue = hue << 1;
            hue = hue + 1;
          }
          else {
            hue = hue << 1;
          }
          while (digitalRead(sensorPin) == 0) {
            //  __asm__("nop\n\t");
          }
          startHead = 0;
          return 1;
        }*/


  }
  return 0;

}
