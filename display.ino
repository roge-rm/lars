/* Display text */

void displayStatus(int i) {
  switch (i) {
    case 0:
      display.clearDisplay();
    case 1:
      for (int i = 0; i < 4; i++) {
        paramValue[i] = getParam(paramNum[i]);
        previousValue[i] =  paramValue[i];
      }
      for (int i = 0; i < 10; i++) {
        clearText(i);
        displayText(i);
      }
      delay(500);
      displayText(100);
      break;
    case 2:
      clearText(1);
      for (int i = 0; i < 4; i++) {
        paramValue[i] = getParam(paramNum[i]);
        previousValue[i] =  paramValue[i];
      }
      displayText(0);
      for (int i = 1; i < 10; i += 2) {
        clearText(i);
        displayText(i);
      }

      break;
    case 3:
      for (int i = 20; i < 28; i++) {
        displayText(i);
      }
      break;
    case 4:
      for (int i = 0; i < 4; i++) {
        paramValue[i] = getParam(paramNum[i]);
        previousValue[i] =  paramValue[i];
      }
      for (int i = 2; i < 10; i++) {
        clearText(i);
        displayText(i);
      }
      break;
    case 5:
      displayCentre("   ", 28);
      displayCentre(patchNum, 28);
      break;
    case 6:
      displayCentre("   ", 28);
      displayCentre(midiPort, 28);
      break;
  }
}

void clearText(int textNum) {
  switch (textNum) {
    case 0:
      display.setCursor(30, 18);
      display.print("           ");
      display.setCursor(0, 28);
      display.print("                    ");
      break;
    case 1:
      display.setCursor(70, 28);
      display.print("   ");
      break;
    case 2:
      display.setCursor(2, 0);
      display.print("    ");
      break;
    case 3:
      display.setCursor(2, 12);
      display.print("    ");
      break;
    case 4:
      display.setCursor(100, 0);
      display.print("    ");
      break;
    case 5:
      display.setCursor(100, 12);
      display.print("    ");
      break;
    case 6:
      display.setCursor(2, 43);
      display.print("    ");
      break;
    case 7:
      display.setCursor(2, 55);
      display.print("    ");
      break;
    case 8:
      display.setCursor(100, 43);
      display.print("    ");
      break;
    case 9:
      display.setCursor(100, 55);
      display.print("    ");
      break;
  }
}

void displayText(int textNum) { // display text in individual pieces to allow for quickly rewriting a section
  clearText(textNum);

  switch (textNum) {
    case 0: // patch heading, centre of screen
      displayCentre("PATCH", 18);
      break;
    case 1: // patch number
      displayCentre(patchNum, 28);
      break;
    case 2: // encoder 1 title, top left
    case 20:
      display.setCursor(2, 0);
      if (paramNum[0] >= 0) display.print(paramNames[0]);
      break;
    case 3: // encoder 1 value
      display.setCursor(2, 12);
      if (bitEdit) displayText(21);
      else  displayParam(paramNum[0], paramValue[0]);
      break;
    case 4: // encoder 2 title, top right
    case 22:
      display.setCursor(100, 0);
      if (paramNum[1] >= 0) display.print(paramNames[1]);
      break;
    case 5: // encoder 2 value
      display.setCursor(100, 12);
      if (bitEdit) displayText(23);
      else displayParam(paramNum[1], paramValue[1]);
      break;
    case 6: // encoder 3 title, bottom left.
    case 24:
      display.setCursor(2, 43);
      if (paramNum[2] >= 0) display.print(paramNames[2]);
      break;
    case 7: // encoder 3 value
      display.setCursor(2, 55);
      if (bitEdit) displayText(25);
      else displayParam(paramNum[2], paramValue[2]);
      break;
    case 8: // encoder 4 title, bottom right
    case 26:
      display.setCursor(100, 43);
      if (paramNum[3] >= 0) display.print(paramNames[3]);
      break;
    case 9: // encoder 4 value
      display.setCursor(100, 55);
      if (bitEdit) displayText(27);
      else displayParam(paramNum[3], paramValue[3]);
      break;
    case 10: // patch loaded
      clearText(0);
      displayCentre("PATCH LOADED", 28);
      break;
    case 11: // patch saved
      clearText(0);
      displayCentre("PATCH SAVED", 28);
      break;
    case 12: // init patch
      clearText(0);
      displayCentre("PATCH INIT", 28);
      break;
    case 13: // change MIDI channnel
      clearText(0);
      display.setCursor(10, 28);
      display.print("MIDI SET TO CH ");
      display.print(midiPort);
      break;
    case 15: // AMP EG
      display.setCursor(40, 55);
      display.print("AMP ");
      if (levelEG) display.print("LEVEL");
      else display.print("TIME");
      break;
    case 16: // Cutoff EG
      display.setCursor(40, 55);
      display.print("FLT ");
      if (levelEG) display.print("LEVEL");
      else display.print("TIME");
      break;
    case 17: // Pitch EG
      display.setCursor(40, 55);
      display.print("PIT ");
      if (levelEG) display.print("LEVEL");
      else display.print("TIME");
      break;

    /* bitwise value display */
    case 21: // osc 1 bit value
      display.setCursor(2, 12);
      display.print("    ");
      display.setCursor(2, 12);
      if (bitLocation[0] >= 0) displayBit(bitLocation[0]);
      break;
    case 23: // osc 2 bit value
      display.setCursor(100, 12);
      display.print("    ");
      display.setCursor(100, 12);
      if (bitLocation[1] >= 0) displayBit(bitLocation[1]);
      break;
    case 25: // osc 3 bit value
      display.setCursor(2, 55);
      display.print("    ");
      display.setCursor(2, 55);
      if (bitLocation[2] >= 0) displayBit(bitLocation[2]);
      break;
    case 27: // osc 4 bit value
      display.setCursor(100, 55);
      display.print("    ");
      display.setCursor(100, 55);
      if (bitLocation[3] >= 0) displayBit(bitLocation[3]);
      break;
    case 100:
      clearText(0);
      displayCentre(menuName, 28);
      break;
  }
  display.display();
}

void displayParam(int Param, int Value) {
  switch (Param) {
    case 1 ... 4:
    case 271:
    case 285 ... 288:
    case 292:
    case 350:
    case 385:
      display.print(valueName0[Value]);
      break;
    case 11 ... 14:
      display.print(valueName1[Value]);
      break;
    case 7 ... 10:
      display.print(valueName2[Value]);
      break;
    case 71:
      display.print(valueName3[Value]);
      break;
    case 160:
    case 170:
      display.print(valueName4[Value]);
      break;
    case 162:
    case 172:
      display.print(valueName5[Value]);
      break;
    case 244:
      display.print(valueName6[Value]);
      break;
    case 245:
      display.print(valueName7[Value]);
      break;
    case 450:
      display.print(valueName8[Value]);
      break;
    case 340:
    case 353:
      display.print(valueName9[Value]);
      break;
    case 278:
      display.print(valueName10[Value]);
      break;
    case 354:
      display.print(valueName11[Value]);
      break;
    case 362:
      display.print(valueName12[Value]);
      break;
    case 312:
      display.print(valueName13[Value]);
      break;
    case 302:
      display.print(valueName14[Value]);
      break;
    case 291:
      display.print(valueName15[Value]);
      break;
    case 392:
      display.print(valueName16[Value]);
      break;
    case 386:
      display.print(valueName17[Value]);
      break;
    case 508:
      display.print(valueName18[Value]);
      break;
    case 510 ... 511:
      display.print(valueName19[Value]);
      break;
    default:
      if (Value > -1) display.print(Value);
      break;
  }
}

/* Display graphics */

void displayADSR() {
  if (stateChange) {
    display.clearDisplay();

    switch (presetNum[3]) {
      case 0: // amp adsr
        egDLY = getParam(112);
        egL0 = getParam(82);
        egL1 = getParam(87);
        egL2 = getParam(92);
        egL3 = getParam(97);
        egL4 = getParam(102);
        egL5 = getParam(107);
        egR1 = getParam(117);
        egR2 = getParam(122);
        egR3 = getParam(127);
        egR4 = getParam(132);
        egR5 = getParam(137);
        displayText(15);
        break;
      case 1: // cutoff adsr
        egDLY = getParam(111);
        egL0 = getParam(81);
        egL1 = getParam(86);
        egL2 = getParam(91);
        egL3 = getParam(96);
        egL4 = getParam(101);
        egL5 = getParam(106);
        egR1 = getParam(116);
        egR2 = getParam(121);
        egR3 = getParam(126);
        egR4 = getParam(131);
        egR5 = getParam(136);
        displayText(16);
        break;
      case 2: // pitch adsr
        egDLY = getParam(110);
        egL0 = getParam(80);
        egL1 = getParam(85);
        egL2 = getParam(90);
        egL3 = getParam(95);
        egL4 = getParam(100);
        egL5 = getParam(105);
        egR1 = getParam(115);
        egR2 = getParam(120);
        egR3 = getParam(125);
        egR4 = getParam(130);
        egR5 = getParam(135);
        displayText(17);
        break;
    }

    int egTotalTime = egDLY + egR1 + egR2 + egR3 + egR4 + egR5;
    eg0x = 0;
    eg0y = 63 - ((egL0 / 255) * 62); // divide egL0 by the total possible value to get percentage of display height to use
    eg1x = (((egDLY / egTotalTime)) * 122) + 1; // do something similar with an x value for display length
    eg1y = 63 - ((egL0 / 255) * 62);
    eg2x = (((egR1 / egTotalTime)) * 122) + eg1x + 1;
    eg2y = 63 - ((egL1 / 255) * 62);
    eg3x = (((egR2 / egTotalTime)) * 122) + eg2x + 1;
    eg3y = 63 - ((egL2 / 255) * 62);
    eg4x = (((egR3 / egTotalTime)) * 122) + eg3x + 1;
    eg4y = 63 - ((egL3 / 255) * 62);
    eg5x = (((egR4 / egTotalTime)) * 122) + eg4x + 1;
    eg5y = 63 - ((egL4 / 255) * 62);
    eg6x = (((egR5 / egTotalTime)) * 122) + eg5x + 1;
    eg6y = 63 - ((egL5 / 255) * 62);

    display.drawLine(eg0x, eg0y, eg1x, eg1y, WHITE);
    display.drawLine(eg1x, eg1y, eg2x, eg2y, WHITE);
    display.drawLine(eg2x, eg2y, eg3x, eg3y, WHITE);
    display.drawLine(eg3x, eg3y, eg4x, eg4y, WHITE);
    display.drawLine(eg4x, eg4y, eg5x, eg5y, WHITE);
    display.drawLine(eg5x, eg5y, eg6x, eg6y, WHITE);

    // display box around point being modified
    if (!editEG[0]) {
      display.fillRect(eg2x - 2, eg2y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg2x, 0, eg2x, 3, WHITE);
      else display.drawLine(0, eg2y, 3, eg2y, WHITE);
    }
    else {
      display.fillRect(eg1x - 2, eg1y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg1x, 0, eg1x, 3, WHITE);
      else display.drawLine(0, eg1y, 3, eg1y, WHITE);
    }
    if (!editEG[1]) {
      display.fillRect(eg3x - 2, eg3y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg3x, 0, eg3x, 3, WHITE);
      else display.drawLine(128, eg3y, 124, eg3y, WHITE);
    }
    else {
      display.fillRect(eg2x - 2, eg2y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg2x, 0, eg2x, 3, WHITE);
      else display.drawLine(128, eg2y, 124, eg2y, WHITE);
    }
    if (!editEG[2]) {
      display.fillRect(eg4x - 2, eg4y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg4x, 64, eg4x, 60, WHITE);
      else display.drawLine(0, eg4y, 3, eg4y, WHITE);
    }
    else {
      display.fillRect(eg5x - 2, eg5y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg5x, 64, eg5x, 60, WHITE);
      else display.drawLine(0, eg5y, 3, eg5y, WHITE);
    }
    if (!editEG[3]) {
      display.fillRect(eg5x - 2, eg5y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg5x, 64, eg5x, 60, WHITE);
      else display.drawLine(128, eg5y, 124, eg5y, WHITE);
    }
    else {
      display.fillRect(eg6x - 2, eg6y - 2, 5, 5, WHITE);
      if (!levelEG) display.drawLine(eg6x, 64, eg6x, 60, WHITE);
      else display.drawLine(128, eg6y, 124, eg6y, WHITE);
    }

    display.display();

    stateChange = false;

  }
}

void startA() {
  display.clearDisplay();

  for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5) {
    display.drawTriangle(
      display.width() / 2  , display.height() / 2 - i,
      display.width() / 2 - i, display.height() / 2 + i,
      display.width() / 2 + i, display.height() / 2 + i, WHITE);
    display.display();
    delay(1);
  }
  delay(500);
  display.clearDisplay();
}

void displayBit (int i) {
  if (bitValues[bitNum][bitLocation[i]]) display.print("ON ");
  else display.print("OFF");
}

void displayCentre(String text, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h); // calculate width of menu heading
  display.setCursor((128 - w) / 2, y); // centre heading
  display.print(text);
  display.display();
}
