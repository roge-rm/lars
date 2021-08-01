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
      displayText(presetType + 100);
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
      display.setCursor(70, 30);
      display.print("   ");
      display.setCursor(70, 30);
      display.print(patchNum);
      display.display();
      break;
  }
}

void clearText(int textNum) {
  switch (textNum) {
    case 0:
      display.setCursor(0, 30);
      display.print("                    ");
      break;
    case 1:
      display.setCursor(70, 30);
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
      display.setCursor(35, 30);
      display.print(F("Patch"));
      break;
    case 1: // patch number
      display.setCursor(70, 30);
      display.print(patchNum);
      break;
    case 2: // encoder 1 title, top left
      display.setCursor(2, 0);
      switch (presetType) {
        case 0:
          if (paramNum[0] > 0) display.print(paramName0[0]);
          break;
        case 1:
          if (paramNum[0] > 0) display.print(paramName1_1[presetNum[1]]);
          break;
        case 2:
          if (paramNum[0] > 0) display.print(paramName2_1[presetNum[2]]);
          break;
        case 3:
          if (paramNum[0] > 0) display.print(paramName3_1[presetNum[3]]);
          break;
        case 4:
          if (paramNum[0] > 0) display.print(paramName4_1[presetNum[4]]);
          break;
        case 5:
          if (paramNum[0] > 0) display.print(paramName5_1[presetNum[5]]);
          break;
        case 11:
          if (paramNum[0] > 0) display.print(paramName6_1[presetNum[11]]);
          break;
        case 12:
          if (paramNum[0] > 0) display.print(paramName6_1[presetNum[12]]);
          break;
        case 13:
          if (paramNum[0] > 0) display.print(paramName6_1[presetNum[13]]);
          break;
        case 14:
          if (paramNum[0] > 0) display.print(paramName6_1[presetNum[14]]);
          break;
      }
      break;
    case 3: // encoder 1 value
      display.setCursor(2, 12);
      if (paramNum[0] > 0) display.print(paramValue[0]);
      break;
    case 4: // encoder 2 title, top right
      display.setCursor(100, 0);
      switch (presetType) {
        case 0:
          if (paramNum[1] > 0) display.print(paramName0[1]);
          break;
        case 1:
          if (paramNum[1] > 0) display.print(paramName1_2[presetNum[1]]);
          break;
        case 2:
          if (paramNum[1] > 0) display.print(paramName2_2[presetNum[2]]);
          break;
        case 3:
          if (paramNum[1] > 0) display.print(paramName3_2[presetNum[3]]);
          break;
        case 4:
          if (paramNum[1] > 0) display.print(paramName4_2[presetNum[4]]);
          break;
        case 5:
          if (paramNum[1] > 0) display.print(paramName5_2[presetNum[5]]);
          break;
        case 11:
          if (paramNum[1] > 0) display.print(paramName6_2[presetNum[11]]);
          break;
        case 12:
          if (paramNum[1] > 0) display.print(paramName6_2[presetNum[12]]);
          break;
        case 13:
          if (paramNum[1] > 0) display.print(paramName6_2[presetNum[13]]);
          break;
        case 14:
          if (paramNum[1] > 0) display.print(paramName6_2[presetNum[14]]);
          break;
      }
      break;
    case 5: // encoder 2 value
      display.setCursor(100, 12);
      if (paramNum[1] > 0) display.print(paramValue[1]);
      break;
    case 6: // encoder 3 title, bottom left.
      display.setCursor(2, 43);
      switch (presetType) {
        case 0:
          if (paramNum[2] > 0) display.print(paramName0[2]);
          break;
        case 2:
          if (paramNum[2] > 0) display.print(paramName2_3[presetNum[2]]);
          break;
        case 3:
          if (paramNum[2] > 0) display.print(paramName3_3[presetNum[3]]);
          break;
        case 4:
          if (paramNum[2] > 0) display.print(paramName4_3[presetNum[4]]);
          break;
        case 5:
          if (paramNum[2] > 0) display.print(paramName5_3[presetNum[5]]);
          break;
        case 11:
          if (paramNum[2] > 0) display.print(paramName6_3[presetNum[11]]);
          break;
        case 12:
          if (paramNum[2] > 0) display.print(paramName6_3[presetNum[12]]);
          break;
        case 13:
          if (paramNum[2] > 0) display.print(paramName6_3[presetNum[13]]);
          break;
        case 14:
          if (paramNum[2] > 0) display.print(paramName6_3[presetNum[14]]);
          break;
      }
      break;
    case 7: // encoder 3 value
      display.setCursor(2, 55);
      if (paramNum[2] > 0) display.print(paramValue[2]);
      break;
    case 8: // encoder 4 title, bottom right
      display.setCursor(100, 43);
      switch (presetType) {
        case 0:
          if (paramNum[3] > 0) display.print(paramName0[3]);
          break;
        case 2:
          if (paramNum[3] > 0) display.print(paramName2_4[presetNum[2]]);
          break;
        case 3:
          if (paramNum[3] > 0) display.print(paramName3_4[presetNum[3]]);
          break;
        case 4:
          if (paramNum[3] > 0) display.print(paramName4_4[presetNum[4]]);
          break;
        case 5:
          if (paramNum[3] > 0) display.print(paramName5_4[presetNum[5]]);
          break;
        case 11:
          if (paramNum[3] > 0) display.print(paramName6_4[presetNum[11]]);
          break;
        case 12:
          if (paramNum[3] > 0) display.print(paramName6_4[presetNum[12]]);
          break;
        case 13:
          if (paramNum[3] > 0) display.print(paramName6_4[presetNum[13]]);
          break;
        case 14:
          if (paramNum[3] > 0) display.print(paramName6_4[presetNum[14]]);
          break;
      }
      break;
    case 9: // encoder 4 value
      display.setCursor(100, 55);
      if (paramNum[3] > 0) display.print(paramValue[3]);
      break;
    case 10: // patch loaded
      clearText(0);
      display.setCursor(20, 30);
      display.print("Patch Loaded");
      break;
    case 11: // patch saved
      clearText(0);
      display.setCursor(20, 30);
      display.print("Patch Saved");
      break;
    case 12: // init patch
      clearText(0);
      display.setCursor(25, 30);
      display.print("Patch Init");

    /* bitwise value display */
    case 20: // osc 1 name
      display.setCursor(2, 0);
      display.print("    ");
      display.setCursor(2, 0);
      display.print("OSC1");
      break;
    case 21: // osc 1 bit value
      display.setCursor(2, 12);
      display.print("    ");
      display.setCursor(2, 12);
      display.print(bitValues[bitNum][0]);
      break;
    case 22: // osc 2 name
      display.setCursor(100, 0);
      display.print("    ");
      display.setCursor(100, 0);
      display.print("OSC2");
      break;
    case 23: // osc 2 bit value
      display.setCursor(100, 12);
      display.print("    ");
      display.setCursor(100, 12);
      display.print(bitValues[bitNum][1]);
      break;
    case 24: // osc 3 name
      display.setCursor(2, 43);
      display.print("    ");
      display.setCursor(2, 43);
      display.print("OSC3");
      break;
    case 25: // osc 3 bit value
      display.setCursor(2, 55);
      display.print("    ");
      display.setCursor(2, 55);
      display.print(bitValues[bitNum][2]);
      break;
    case 26: // osc 4 name
      display.setCursor(100, 43);
      display.print("    ");
      display.setCursor(100, 43);
      display.print("OSC4");
      break;
    case 27: // osc 4 bit value
      display.setCursor(100, 55);
      display.print("    ");
      display.setCursor(100, 55);
      display.print(bitValues[bitNum][3]);
      break;

    case 100:
      clearText(0);
      display.setCursor(30, 30);
      display.print(menu0Names[presetNum[0]]);
      break;
    case 101:
      clearText(0);
      display.setCursor(30, 30);
      display.print(menu1Names[presetNum[1]]);
      break;
    case 102:
      clearText(0);
      display.setCursor(30, 30);
      display.print(menu2Names[presetNum[2]]);
      break;
    case 103:
      clearText(0);
      display.setCursor(30, 30);
      display.print(menu3Names[presetNum[3]]);
      break;
    case 104:
      clearText(0);
      display.setCursor(25, 30);
      display.print(menu4Names[presetNum[4]]);
      break;
    case 105:
      clearText(0);
      display.setCursor(25, 30);
      display.print(menu5Names[presetNum[5]]);
      break;
    case 111:
      clearText(0);
      display.setCursor(35, 30);
      display.print(menu11Names[presetNum[11]]);
      break;
    case 112:
      clearText(0);
      display.setCursor(35, 30);
      display.print(menu12Names[presetNum[12]]);
      break;
    case 113:
      clearText(0);
      display.setCursor(35, 30);
      display.print(menu13Names[presetNum[13]]);
      break;
    case 114:
      clearText(0);
      display.setCursor(35, 30);
      display.print(menu14Names[presetNum[14]]);
      break;
  }
  display.display();
}
