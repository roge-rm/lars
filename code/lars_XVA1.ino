/* XVA1 interaction */

int getParam(int pNum) { // input parameter number
  if (pNum > -1) {
    Serial1.write('g'); // send g + param number to request value
    if (pNum < 254) Serial1.write(pNum);
    else {
      Serial1.write(255);
      Serial1.write(pNum - 256);
    }
    while (!Serial1.available()); // wait for return
    return Serial1.read(); // return value provided by XVA1
  }
}

void setParam(int pNum, int pVal) { // input parameter number and value to set
  if (pNum > -1) {
    Serial1.write('s'); // send g + param number to request value
    if (pNum < 254) Serial1.write(pNum);
    else {
      Serial1.write(255);
      Serial1.write(pNum - 256);
    }
    Serial1.write(pVal);
    delay(10);
  }
}

void loadPatch() { // load patch from EEPROM
  Serial1.write('r');
  Serial1.write(patchNum);
  while (!Serial1.available()); //wait for it
  if (Serial1.read() == 0) Serial.println("Patch loaded");
}

void savePatch() { // save current patch to EEPROM after prompting for patch number
  Serial1.write('w');
  Serial1.write(patchNum);
  while (!Serial1.available()); //wait for it
  Serial.println(Serial1.read());

}

void initPatch() { // initialize current patch
  Serial1.write('i');
  Serial1.write(patchNum);
  while (!Serial1.available()); //wait for it
  Serial.println(Serial1.read());
}

void setMIDI(int chan) { // set MIDI channel
  Serial1.write('*');
  Serial1.write(10);
  Serial1.write(chan); // 0 for omni or 1-16
  while (!Serial1.available()); //wait for it
  Serial.println(Serial1.read());
}
