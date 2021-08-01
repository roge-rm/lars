/* Bitwise value operators */

void readBits(int bNum) { // read bit values for bitwise-stored variables
  int bit0 = getParam(bNum);
  switch (bNum) {
    case 5:
      Serial.print("Sync: ");
      break;
    case 6:
      Serial.print("Mode: ");
      break;
  }
  for (int i = 0; i < 4; i++) {
    bitValues[0][i] = bitRead(bit0, i); // oscillator sync
    Serial.print(bitValues[0][i]);
  }
  Serial.println();
}

void storeBits(int bNum) { // store bit values for bitwise-stored variables
  int bit0 = 0;
  int bParam = 0;
  switch (bNum) {
    case 0:
      bParam = 5;
      break;
    case 1:
      bParam = 6;
      break;
    case 2:
      bParam = 145;
      break;
    case 3:
      bParam = 146;
      break;
    case 4:
      bParam = 147;
      break;
}
  Serial.print("ParamNum ");
  Serial.print(bParam);
  Serial.print(": ");
  for (int i = 0; i < 4; i++) {
    bitWrite(bit0, i, bitValues[bNum][i]);
  }
  Serial.print(bit0);
  setParam(bParam, bit0);
  Serial.println();
}
