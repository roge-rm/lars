/* Change preset, param, values */

int changeMIDI() { // change what MIDI port the XVA1 responds to
  bool cont = false;
  display.clearDisplay();
  display.setCursor(15, 28);
  display.print("MIDI PORT: ");
  displayStatus(6);
  while (!cont) {
    encUpdate();

    if (enc1.isLeft() || enc2.isLeft() || enc3.isLeft() || enc4.isLeft()) {
      midiPort--;
      if (midiPort < 0) midiPort = 16;
      displayStatus(6);
    }
    else if (enc1.isRight() || enc2.isRight() || enc3.isRight() || enc4.isRight()) {
      midiPort++;
      if (midiPort > 16) midiPort = 0;
      displayStatus(6);
    }
    else if (tbtn4.isClick() || enc1.isClick() || enc2.isClick() || enc3.isClick() || enc4.isClick()) {
      setMIDI(midiPort);
      cont = true;
      return 1;
    }
    else if (tbtn1.isClick() || tbtn2.isClick() || tbtn3.isClick() || bbtn1.isClick() || bbtn2.isClick() || bbtn3.isClick() || bbtn4.isClick() || bbtn5.isClick() || bbtn6.isClick()) {
      cont = true;
      return 0;
    }
  }
}

int changeSave() { // prompt for patch number to save to
  bool cont = false;
  display.clearDisplay();
  display.setCursor(20, 30);
  display.print("SAVE TO: ");
  displayStatus(5);
  while (!cont) {
    encUpdate();

    if (enc1.isLeft() || enc2.isLeft() || enc3.isLeft() || enc4.isLeft()) {
      patchNum--;
      if (patchNum < 0) patchNum = 127;
      displayStatus(5);
    }
    else if (enc1.isRight() || enc2.isRight() || enc3.isRight() || enc4.isRight()) {
      patchNum++;
      if (patchNum > 127) patchNum = 0;
      displayStatus(5);
    }
    else if (tbtn4.isClick() || enc1.isClick() || enc2.isClick() || enc3.isClick() || enc4.isClick()) {
      savePatch();
      cont = true;
      patchModify = false;
      return 1;
    }
    else if (tbtn1.isClick() || tbtn2.isClick() || tbtn3.isClick() || bbtn1.isClick() || bbtn2.isClick() || bbtn3.isClick() || bbtn4.isClick() || bbtn5.isClick() || bbtn6.isClick()) {
      cont = true;
      return 0;
    }
  }

}

void changePreset() {
  stateChange = true;
  if ((presetType == 0) && (presetNum[0] == 4 || presetNum[0] == 6)) bitEdit = 1;
  else bitEdit = 0;
  
  switch (presetType) {
    case 0: // oscillators
      switch (presetNum[0]) {
        case 0: // on/off
          strcpy(menuName, "OSC ON/OFF");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 1;
          paramNum[1] = 2;
          paramNum[2] = 3;
          paramNum[3] = 4;
          break;
        case 1: // waveform
          strcpy(menuName, "WAVEFORM");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 11;
          paramNum[1] = 12;
          paramNum[2] = 13;
          paramNum[3] = 14;
          break;
        case 2: // pulse width
          strcpy(menuName, "PULSE WIDTH");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 15;
          paramNum[1] = 16;
          paramNum[2] = 17;
          paramNum[3] = 18;
          break;
        case 3: // sawstack detune
          strcpy(menuName, "SAWSTACK DETUNE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 285;
          paramNum[1] = 286;
          paramNum[2] = 287;
          paramNum[3] = 288;
          break;
        case 4: // sync
          strcpy(menuName, "SYNC");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          bitNum = 0;
          readBits();
          paramNum[0] = 0;
          paramNum[1] = 0;
          paramNum[2] = 0;
          paramNum[3] = 0;
          bitLocation[0] = 0;
          bitLocation[1] = 1;
          bitLocation[2] = 2;
          bitLocation[3] = 3;
          break;
        case 5: // phase
          strcpy(menuName, "PHASE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 7;
          paramNum[1] = 8;
          paramNum[2] = 9;
          paramNum[3] = 10;
          break;
        case 6: // mode
          strcpy(menuName, "MODE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          bitNum = 1;
          readBits();
          paramNum[0] = 0;
          paramNum[1] = 0;
          paramNum[2] = 0;
          paramNum[3] = 0;
          bitLocation[0] = 0;
          bitLocation[1] = 1;
          bitLocation[2] = 2;
          bitLocation[3] = 3;
          break;
        case 7: // transpose
          strcpy(menuName, "TRANSPOSE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 19;
          paramNum[1] = 20;
          paramNum[2] = 21;
          paramNum[3] = 22;
          break;
        case 8: // tune
          strcpy(menuName, "DETUNE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 23;
          paramNum[1] = 24;
          paramNum[2] = 25;
          paramNum[3] = 26;
          break;
        case 9: // drift
          strcpy(menuName, "DRIFT");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 260;
          paramNum[1] = 261;
          paramNum[2] = 262;
          paramNum[3] = 263;
          break;
        case 10: // level
          strcpy(menuName, "LEVEL");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 27;
          paramNum[1] = 28;
          paramNum[2] = 29;
          paramNum[3] = 30;
          break;
        case 11: // level l
          strcpy(menuName, "LEVEL L");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 31;
          paramNum[1] = 33;
          paramNum[2] = 35;
          paramNum[3] = 37;
          break;
        case 12: // level r
          strcpy(menuName, "LEVEL R");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 32;
          paramNum[1] = 34;
          paramNum[2] = 36;
          paramNum[3] = 38;
          break;
        case 13: // velo sens
          strcpy(menuName, "VELOCITY SENS");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 39;
          paramNum[1] = 40;
          paramNum[2] = 41;
          paramNum[3] = 42;
          break;
        case 14: // key bp
          strcpy(menuName, "KEY BP");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 43;
          paramNum[1] = 44;
          paramNum[2] = 45;
          paramNum[3] = 46;
          break;
        case 15: // key ldepth
          strcpy(menuName, "KEY LDEPTH");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 47;
          paramNum[1] = 48;
          paramNum[2] = 49;
          paramNum[3] = 50;
          break;
        case 16: // key rdepth
          strcpy(menuName, "KEY RDEPTH");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 51;
          paramNum[1] = 52;
          paramNum[2] = 53;
          paramNum[3] = 54;
          break;
        case 17: // key lcurve
          strcpy(menuName, "KEY LCURVE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 55;
          paramNum[1] = 56;
          paramNum[2] = 57;
          paramNum[3] = 58;
          break;
        case 18: // key rcurve
          strcpy(menuName, "KEY RCURVE");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 59;
          paramNum[1] = 60;
          paramNum[2] = 61;
          paramNum[3] = 62;
          break;
        case 19: // pitch mod sens
          strcpy(menuName, "PITCH MOD SENS");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 63;
          paramNum[1] = 64;
          paramNum[2] = 65;
          paramNum[3] = 66;
          break;
        case 20: // amp mod sens
          strcpy(menuName, "AMP MOD SENS");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = 67;
          paramNum[1] = 68;
          paramNum[2] = 69;
          paramNum[3] = 70;
          break;
        case 21: // ring mod
          strcpy(menuName, "RING MOD");
          strcpy(paramNames[0], "OSC1");
          strcpy(paramNames[1], "OSC2");
          strcpy(paramNames[2], "OSC3");
          strcpy(paramNames[3], "OSC4");
          paramNum[0] = -1;
          paramNum[1] = -1;
          paramNum[2] = 271;
          paramNum[3] = -1;
          break;
      }
      break;
    case 1: // filters
      switch (presetNum[1]) {
        case 0: // filter/drive/routing
          strcpy(menuName, "FILTER");
          strcpy(paramNames[0], "TYPE");
          strcpy(paramNames[1], "");
          strcpy(paramNames[2], "DRV");
          strcpy(paramNames[3], "ROUT");
          paramNum[0] = 71;
          paramNum[1] = -1;
          paramNum[2] = 275;
          paramNum[3] = 278;
          break;
        case 1: // cutoff/reso 1/2
          strcpy(menuName, "CUTOFF/RESONANCE");
          strcpy(paramNames[0], "CUT1");
          strcpy(paramNames[1], "CUT2");
          strcpy(paramNames[2], "RES1");
          strcpy(paramNames[3], "RES2");
          paramNum[0] = 72;
          paramNum[1] = 78;
          paramNum[2] = 77;
          paramNum[3] = 79;
          break;
        case 2: // vel/kb track/reso 1/2
          strcpy(menuName, "KBD TRACK/RESONANCE");
          strcpy(paramNames[0], "VELT");
          strcpy(paramNames[1], "KEYT");
          strcpy(paramNames[2], "VELR");
          strcpy(paramNames[3], "KEYR");
          paramNum[0] = 77;
          paramNum[1] = 79;
          paramNum[2] = 276;
          paramNum[3] = 277;
          break;
        case 3: // eg depth/velocity
          strcpy(menuName, " ENVELOPE GEN");
          strcpy(paramNames[0], "DPTH");
          strcpy(paramNames[1], "VELO");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          paramNum[0] = 75;
          paramNum[1] = 79;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 2: // modulation
      switch (presetNum[2]) {
        case 0: // LFO1 wave/range/speed/sync
          strcpy(menuName, "LFO1 MOD1");
          strcpy(paramNames[0], "WAVE");
          strcpy(paramNames[1], "RNG");
          strcpy(paramNames[2], "SPD");
          strcpy(paramNames[3], "SYNC");
          paramNum[0] = 160;
          paramNum[1] = 166;
          paramNum[2] = 161;
          paramNum[3] = 162;
          break;
        case 1: // LFO1 fade/depth pitch/depth amp
          strcpy(menuName, "LFO1 MOD2");
          strcpy(paramNames[0], "FADE");
          strcpy(paramNames[1], "DPIT");
          strcpy(paramNames[2], "DAMP");
          strcpy(paramNames[3], "");
          paramNum[0] = 163;
          paramNum[1] = 164;
          paramNum[2] = 165;
          paramNum[3] = -1;
          break;
        case 2: // LFO2 wave/range/speed/sync
          strcpy(menuName, "LFO2 MOD1");
          strcpy(paramNames[0], "WAVE");
          strcpy(paramNames[1], "RNG");
          strcpy(paramNames[2], "SPD");
          strcpy(paramNames[3], "SYNC");
          paramNum[0] = 170;
          paramNum[1] = 176;
          paramNum[2] = 171;
          paramNum[3] = 172;
          break;
        case 3: // LFO2 fade/depth pulse width/depth cutoff
          strcpy(menuName, "LFO2 MOD2");
          strcpy(paramNames[0], "FADE");
          strcpy(paramNames[1], "DPW");
          strcpy(paramNames[2], "DCUT");
          strcpy(paramNames[3], "");
          paramNum[0] = 173;
          paramNum[1] = 174;
          paramNum[2] = 175;
          paramNum[3] = -1;
          break;
        case 4: // LFO after pitch/pw/filter/amp
          strcpy(menuName, "LFO AFTER");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "FILT");
          strcpy(paramNames[3], "AMP");
          paramNum[0] = 180;
          paramNum[1] = 184;
          paramNum[2] = 188;
          paramNum[3] = 192;
          break;
        case 5: // LFO wheel pitch/pw/filter/amp
          strcpy(menuName, "LFO WHEEL");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "FILT");
          strcpy(paramNames[3], "AMP");
          paramNum[0] = 181;
          paramNum[1] = 185;
          paramNum[2] = 189;
          paramNum[3] = 193;
          break;
        case 6: // LFO breath pitch/pw/filter/amp
          strcpy(menuName, "LFO BREATH");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "FILT");
          strcpy(paramNames[3], "AMP");
          paramNum[0] = 182;
          paramNum[1] = 186;
          paramNum[2] = 190;
          paramNum[3] = 194;
          break;
        case 7: // LFO foot pitch/pw/filter/amp
          strcpy(menuName, "LFO FOOT");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "FILT");
          strcpy(paramNames[3], "AMP");
          paramNum[0] = 183;
          paramNum[1] = 187;
          paramNum[2] = 191;
          paramNum[3] = 195;
          break;
        case 8: // MIDI after pitch/pw/cutoff/volume
          strcpy(menuName, "MIDI AFTER");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "CUT");
          strcpy(paramNames[3], "VOL");
          paramNum[0] = 200;
          paramNum[1] = 204;
          paramNum[2] = 208;
          paramNum[3] = 212;
          break;
        case 9: // MIDI breath pitch/pw/cutoff/volume
          strcpy(menuName, "MIDI BREATH");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "CUT");
          strcpy(paramNames[3], "VOL");
          paramNum[0] = 201;
          paramNum[1] = 206;
          paramNum[2] = 210;
          paramNum[3] = 214;
          break;
        case 10: // MIDI rnd/wheel pitch/pw/cutoff/volume
          strcpy(menuName, "MIDI RND/WHL");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "CUT");
          strcpy(paramNames[3], "VOL");
          paramNum[0] = 203;
          paramNum[1] = 205;
          paramNum[2] = 209;
          paramNum[3] = 213;
          break;
        case 11: // MIDI foot pitch/pw/cutoff/volume
          strcpy(menuName, "MIDI FOOT");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "CUT");
          strcpy(paramNames[3], "VOL");
          paramNum[0] = 202;
          paramNum[1] = 207;
          paramNum[2] = 211;
          paramNum[3] = 215;
          break;
        case 12: // MIDI temp pitch/pw/cutoff/volume
          strcpy(menuName, "MIDI TEMP");
          strcpy(paramNames[0], "PIT");
          strcpy(paramNames[1], "PW");
          strcpy(paramNames[2], "CUT");
          strcpy(paramNames[3], "VOL");
          paramNum[0] = 220;
          paramNum[1] = 223;
          paramNum[2] = 226;
          paramNum[3] = 229;
          break;
      }
      break;
    case 3: // envelope generators

      if (presetNum[3] > 2 && presetNum[3] < 6) bitEdit = 1;
      else bitEdit = 0;

      switch (presetNum[3]) {
        case 0: // amp adsr
          strcpy(menuName, "");
          strcpy(paramNames[0], "");
          strcpy(paramNames[1], "");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          if (levelEG) {
            if (!editEG[0]) paramNum[0] = 87; // default for encoder 1 is L1 (attack)
            else paramNum[0] = 82; // alternative is L0 (start)
            if (!editEG[1]) paramNum[1] = 92; // default for encoder 2 is L2 (decay 1)
            else paramNum[1] = 87; // alternative is L1 (attack) in case enc1 is reassigned
            if (!editEG[2]) paramNum[2] = 97; // default for encoder 3 is L3 (sustain)
            else paramNum[2] = 102; // alternative is L4 (release 1)
            if (!editEG[3]) paramNum[3] = 102; // default for encoder 4 is L4 (release 1)
            else paramNum[3] = 107; // alternative is L5 (release 2)
            doEG = true;
          }
          else {
            if (!editEG[0]) paramNum[0] = 117; // default is R1
            else paramNum[0] = 112; // alt is DLY
            if (!editEG[1]) paramNum[1] = 122; // default is R2
            else paramNum[1] = 117; // alt is R1
            if (!editEG[2]) paramNum[2] = 127; // default is R3
            else paramNum[2] = 132; // alt is R4
            if (!editEG[3]) paramNum[3] = 132; // default is R4
            else paramNum[3] = 137; // alt is R5
            doEG = true;
          }
          break;
        case 1: // cutoff adsr
          strcpy(menuName, "");
          strcpy(paramNames[0], "");
          strcpy(paramNames[1], "");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          if (levelEG) {
            if (!editEG[0]) paramNum[0] = 86; // default for encoder 1 is L1 (attack)
            else paramNum[0] = 81; // alternative is L0 (start)
            if (!editEG[1]) paramNum[1] = 91; // default for encoder 2 is L2 (decay 1)
            else paramNum[1] = 86; // alternative is L1 (attack) in case enc1 is reassigned
            if (!editEG[2]) paramNum[2] = 96; // default for encoder 3 is L3 (sustain)
            else paramNum[2] = 101; // alternative is L4 (release 1)
            if (!editEG[3]) paramNum[3] = 101; // default for encoder 4 is L4 (release 1)
            else paramNum[3] = 106; // alternative is L5 (release 2)
            doEG = true;
          }
          else {
            if (!editEG[0]) paramNum[0] = 116; // default is R1
            else paramNum[0] = 111; // alt is DLY
            if (!editEG[1]) paramNum[1] = 121; // default is R2
            else paramNum[1] = 116; // alt is R1
            if (!editEG[2]) paramNum[2] = 126; // default is R3
            else paramNum[2] = 131; // alt is R4
            if (!editEG[3]) paramNum[3] = 131; // default is R4
            else paramNum[3] = 136; // alt is R5
            doEG = true;
          }
          break;
        case 2: // pitch adsr
          strcpy(menuName, "");
          strcpy(paramNames[0], "");
          strcpy(paramNames[1], "");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          if (levelEG) {
            if (!editEG[0]) paramNum[0] = 85; // default for encoder 1 is L1 (attack)
            else paramNum[0] = 80; // alternative is L0 (start)
            if (!editEG[1]) paramNum[1] = 90; // default for encoder 2 is L2 (decay 1)
            else paramNum[1] = 85; // alternative is L1 (attack) in case enc1 is reassigned
            if (!editEG[2]) paramNum[2] = 95; // default for encoder 3 is L3 (sustain)
            else paramNum[2] = 100; // alternative is L4 (release 1)
            if (!editEG[3]) paramNum[3] = 100; // default for encoder 4 is L4 (release 1)
            else paramNum[3] = 105; // alternative is L5 (release 2)
            doEG = true;
          }
          else {
            if (!editEG[0]) paramNum[0] = 115; // default is R1
            else paramNum[0] = 110; // alt is DLY
            if (!editEG[1]) paramNum[1] = 120; // default is R2
            else paramNum[1] = 115; // alt is R1
            if (!editEG[2]) paramNum[2] = 125; // default is R3
            else paramNum[2] = 130; // alt is R4
            if (!editEG[3]) paramNum[3] = 130; // default is R4
            else paramNum[3] = 135; // alt is R5
            doEG = true;
          }
          break;
        case 3:
          strcpy(menuName, "EG LOOP");
          strcpy(paramNames[0], "AMP");
          strcpy(paramNames[1], "FLT");
          strcpy(paramNames[2], "PIT");
          strcpy(paramNames[3], "");
          bitNum = 2;
          bitLocation[0] = 0;
          bitLocation[1] = 1;
          bitLocation[2] = 6;
          bitLocation[3] = -1;
          paramNum[0] = 0;
          paramNum[1] = 0;
          paramNum[2] = 0;
          paramNum[3] = -1;
          readBits();
          doClear();
          displayText(103);
          break;
        case 4:
          strcpy(menuName, "EG LOOP SEG");
          strcpy(paramNames[0], "AMP");
          strcpy(paramNames[1], "FLT");
          strcpy(paramNames[2], "PIT");
          strcpy(paramNames[3], "");
          bitNum = 3;
          bitLocation[0] = 0;
          bitLocation[1] = 1;
          bitLocation[2] = 6;
          bitLocation[3] = -1;
          paramNum[0] = 0;
          paramNum[1] = 0;
          paramNum[2] = 0;
          paramNum[3] = -1;
          readBits();
          doClear();
          break;
        case 5:
          strcpy(menuName, "EG RESTART");
          strcpy(paramNames[0], "AMP");
          strcpy(paramNames[1], "FLT");
          strcpy(paramNames[2], "PIT");
          strcpy(paramNames[3], "");
          bitNum = 4;
          bitLocation[0] = 0;
          bitLocation[1] = 1;
          bitLocation[2] = 6;
          bitLocation[3] = -1;
          paramNum[0] = 0;
          paramNum[1] = 0;
          paramNum[2] = 0;
          paramNum[3] = -1;
          readBits();
          doClear();
          break;
        case 6:
          strcpy(menuName, "PITCH");
          strcpy(paramNames[0], "RANG");
          strcpy(paramNames[1], "VELO");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          paramNum[0] = 148;
          paramNum[1] = 149;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }

      for (int i = 0; i < 4; i++) { // this is normally called in the displayStatus function..which is not used for graphics
        paramValue[i] = getParam(paramNum[i]);
        previousValue[i] =  paramValue[i];
      }
      break;
    case 4: // effects
      switch (presetNum[4]) {
        case 0: // chorus/flanger dry/wet/mode
          strcpy(menuName, "CHORUS/FLANGER 1");
          strcpy(paramNames[0], "DRY");
          strcpy(paramNames[1], "WET");
          strcpy(paramNames[2], "MODE");
          strcpy(paramNames[3], "");
          paramNum[0] = 360;
          paramNum[1] = 361;
          paramNum[2] = 362;
          paramNum[3] = -1;
          break;
        case 1: // chorus/flanger speed/depth/feedback/phase
          strcpy(menuName, "CHORUS/FLANGER 2");
          strcpy(paramNames[0], "SPD");
          strcpy(paramNames[1], "DPTH");
          strcpy(paramNames[2], "FEED");
          strcpy(paramNames[3], "PHAS");
          paramNum[0] = 363;
          paramNum[1] = 364;
          paramNum[2] = 365;
          paramNum[3] = 366;
          break;
        case 2: // delay dry/wet/mode/time
          strcpy(menuName, "DELAY 1");
          strcpy(paramNames[0], "DRY");
          strcpy(paramNames[1], "WET");
          strcpy(paramNames[2], "MODE");
          strcpy(paramNames[3], "TIME");
          paramNum[0] = 300;
          paramNum[1] = 301;
          paramNum[2] = 302;
          paramNum[3] = 303;
          break;
        case 3: // delay mul/div/mod speed/mod depth
          strcpy(menuName, "DELAY 2");
          strcpy(paramNames[0], "MUL");
          strcpy(paramNames[1], "DIV");
          strcpy(paramNames[2], "SPD");
          strcpy(paramNames[3], "DPTH");
          paramNum[0] = 308;
          paramNum[1] = 309;
          paramNum[2] = 298;
          paramNum[3] = 299;
          break;
        case 4: // delay feedback/tempo/low/high
          strcpy(menuName, "DELAY 3");
          strcpy(paramNames[0], "FEED");
          strcpy(paramNames[1], "TMPO");
          strcpy(paramNames[2], "LOW");
          strcpy(paramNames[3], "HIGH");
          paramNum[0] = 304;
          paramNum[1] = 307;
          paramNum[2] = 305;
          paramNum[3] = 306;
          break;
        case 5: // delay smear/2x
          strcpy(menuName, "DELAY 4");
          strcpy(paramNames[0], "SMEA");
          strcpy(paramNames[1], "2X");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          paramNum[0] = 291;
          paramNum[1] = 292;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 6: // reverb dry/wet/mode/decay
          strcpy(menuName, "REVERB 1");
          strcpy(paramNames[0], "DRY");
          strcpy(paramNames[1], "WET");
          strcpy(paramNames[2], "MODE");
          strcpy(paramNames[3], "DCAY");
          paramNum[0] = 390;
          paramNum[1] = 391;
          paramNum[2] = 392;
          paramNum[3] = 393;
          break;
        case 7: // reverb damp/hpf/mod speed/mod depth
          strcpy(menuName, "REVERB 2");
          strcpy(paramNames[0], "DAMP");
          strcpy(paramNames[1], "HPF");
          strcpy(paramNames[2], "SPD");
          strcpy(paramNames[3], "DPTH");
          paramNum[0] = 394;
          paramNum[1] = 397;
          paramNum[2] = 395;
          paramNum[3] = 396;
          break;
        case 8: // er dry/wet/room
          strcpy(menuName, "EAREFLECT 1");
          strcpy(paramNames[0], "DRY");
          strcpy(paramNames[1], "WET");
          strcpy(paramNames[2], "ROOM");
          strcpy(paramNames[3], "");
          paramNum[0] = 294;
          paramNum[1] = 295;
          paramNum[2] = 296;
          paramNum[3] = -1;
          break;
        case 9: // er taps/feedback
          strcpy(menuName, "EAREFLECT 2");
          strcpy(paramNames[0], "TAPS");
          strcpy(paramNames[1], "FEED");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "");
          paramNum[0] = 293;
          paramNum[1] = 297;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 10: // phaser dry/wet/mode/stages
          strcpy(menuName, "PHASER 1");
          strcpy(paramNames[0], "DRY");
          strcpy(paramNames[1], "WET");
          strcpy(paramNames[2], "MODE");
          strcpy(paramNames[3], "STAG");
          paramNum[0] = 310;
          paramNum[1] = 311;
          paramNum[2] = 312;
          paramNum[3] = 317;
          break;
        case 11: // phaser speed/depth/feedback/phase
          strcpy(menuName, "PHASER 2");
          strcpy(paramNames[0], "SPD");
          strcpy(paramNames[1], "DPTH");
          strcpy(paramNames[2], "FEED");
          strcpy(paramNames[3], "PHAS");
          paramNum[0] = 314;
          paramNum[1] = 315;
          paramNum[2] = 316;
          paramNum[3] = 318;
          break;
        case 12: // bitcrusher/decimator/filter lo/hi cutoff
          strcpy(menuName, "BIT/DEC/FILT");
          strcpy(paramNames[0], "BIT");
          strcpy(paramNames[1], "DEC");
          strcpy(paramNames[2], "LOW");
          strcpy(paramNames[3], "HIGH");
          paramNum[0] = 380;
          paramNum[1] = 370;
          paramNum[2] = 320;
          paramNum[3] = 321;
          break;
        case 13: // gate onoff/curve/attack/release
          strcpy(menuName, "GATE");
          strcpy(paramNames[0], "GATE");
          strcpy(paramNames[1], "CURV");
          strcpy(paramNames[2], "ATK");
          strcpy(paramNames[3], "RLS");
          paramNum[0] = 385;
          paramNum[1] = 386;
          paramNum[2] = 387;
          paramNum[3] = 388;
          break;
        case 14: // amp mod speed/depth/range/phase
          strcpy(menuName, "AMP MOD");
          strcpy(paramNames[0], "SPD");
          strcpy(paramNames[1], "DPTH");
          strcpy(paramNames[2], "RANG");
          strcpy(paramNames[3], "PHAS");
          paramNum[0] = 331;
          paramNum[1] = 330;
          paramNum[2] = 332;
          paramNum[3] = 333;
          break;
        case 15: // bw/routing/distort on/type
          strcpy(menuName, "BW/ROUTE/DISTORT");
          strcpy(paramNames[0], "BW");
          strcpy(paramNames[1], "ROUT");
          strcpy(paramNames[2], "DIST");
          strcpy(paramNames[3], "TYPE");
          paramNum[0] = 340;
          paramNum[1] = 508;
          paramNum[2] = 350;
          paramNum[3] = 354;
          break;
        case 16: // distort gain pre/post/filter post
          strcpy(menuName, "DISTORT GAIN");
          strcpy(paramNames[0], "PRE");
          strcpy(paramNames[1], "POST");
          strcpy(paramNames[2], "FILT");
          strcpy(paramNames[3], "");
          paramNum[0] = 351;
          paramNum[1] = 352;
          paramNum[2] = 353;
          paramNum[3] = -1;
          break;


      }
      break;
    case 5: // global params
      switch (presetNum[5]) {
        case 0: // arp mode/tempo/mul/octaves
          strcpy(menuName, "ARP");
          strcpy(paramNames[0], "MODE");
          strcpy(paramNames[1], "TEMP");
          strcpy(paramNames[2], "MUL");
          strcpy(paramNames[3], "OCT");
          paramNum[0] = 450;
          paramNum[1] = 451;
          paramNum[2] = 453;
          paramNum[3] = 454;
          break;
        case 1: // transpose/legato/bend up/bend down
          strcpy(menuName, "GLOBAL");
          strcpy(paramNames[0], "TPOS");
          strcpy(paramNames[1], "LEGT");
          strcpy(paramNames[2], "B UP");
          strcpy(paramNames[3], "B DN");
          paramNum[0] = 241;
          paramNum[1] = 244;
          paramNum[2] = 242;
          paramNum[3] = 243;
          break;
        case 2: // porta mode/time, pan/volume
          strcpy(menuName, "PORT/PAN/VOL");
          strcpy(paramNames[0], "MODE");
          strcpy(paramNames[1], "TIME");
          strcpy(paramNames[2], "PAN");
          strcpy(paramNames[3], "VOL");
          paramNum[0] = 245;
          paramNum[1] = 246;
          paramNum[2] = 247;
          paramNum[3] = 248;
          break;
        case 3: // velo offset/tuning/temp offset
          strcpy(menuName, "OFFSET TUNE");
          strcpy(paramNames[0], "VOFF");
          strcpy(paramNames[1], "TUNE");
          strcpy(paramNames[2], "TOFF");
          strcpy(paramNames[3], "");
          paramNum[0] = 249;
          paramNum[1] = 251;
          paramNum[2] = 239;
          paramNum[3] = -1;
          break;
        case 4: // output volume/gain pre/gain post
          strcpy(menuName, "OUTPUT");
          strcpy(paramNames[0], "VOL");
          strcpy(paramNames[1], "PRE");
          strcpy(paramNames[2], "");
          strcpy(paramNames[3], "POST");
          paramNum[0] = 509;
          paramNum[1] = 510;
          paramNum[2] = -1;
          paramNum[3] = 511;
          break;
      }
      break;
    case 11: // osc 1 submenu
      switch (presetNum[11]) {
        case 0: // onoff/phase/waveform/pulse width
          strcpy(menuName, "OSC1 1");
          strcpy(paramNames[0], "OSC");
          strcpy(paramNames[1], "PHAS");
          strcpy(paramNames[2], "WAVE");
          strcpy(paramNames[3], "PW");
          paramNum[0] = 1;
          paramNum[1] = 7;
          paramNum[2] = 11;
          paramNum[3] = 15;
          break;
        case 1: // transpose/drift/detune/saw detune
          strcpy(menuName, "OSC1 2");
          strcpy(paramNames[0], "TPOS");
          strcpy(paramNames[1], "DRFT");
          strcpy(paramNames[2], "TUNE");
          strcpy(paramNames[3], "SAWD");
          paramNum[0] = 19;
          paramNum[1] = 260;
          paramNum[2] = 23;
          paramNum[3] = 285;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          strcpy(menuName, "OSC1 3");
          strcpy(paramNames[0], "LVL");
          strcpy(paramNames[1], "VSEN");
          strcpy(paramNames[2], "LVLL");
          strcpy(paramNames[3], "LVLR");
          paramNum[0] = 27;
          paramNum[1] = 39;
          paramNum[2] = 31;
          paramNum[3] = 32;
          break;
        case 3: // pms, ams
          strcpy(menuName, "OSC1 4");
          strcpy(paramNames[0], "PMS");
          strcpy(paramNames[1], "AMS");
          strcpy(paramNames[2], "RING");
          strcpy(paramNames[3], "");
          paramNum[0] = 63;
          paramNum[1] = 67;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 12: // osc 2 submenu

      switch (presetNum[12]) {
        case 0: // onoff/phase/waveform/pulse width
          strcpy(menuName, "OSC2 1");
          strcpy(paramNames[0], "OSC");
          strcpy(paramNames[1], "PHAS");
          strcpy(paramNames[2], "WAVE");
          strcpy(paramNames[3], "PW");
          paramNum[0] = 2;
          paramNum[1] = 8;
          paramNum[2] = 12;
          paramNum[3] = 16;
          break;
        case 1: // transpose/drift/detune/saw detune
          strcpy(menuName, "OSC2 2");
          strcpy(paramNames[0], "TPOS");
          strcpy(paramNames[1], "DRFT");
          strcpy(paramNames[2], "TUNE");
          strcpy(paramNames[3], "SAWD");
          paramNum[0] = 20;
          paramNum[1] = 261;
          paramNum[2] = 24;
          paramNum[3] = 286;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          strcpy(menuName, "OSC2 3");
          strcpy(paramNames[0], "LVL");
          strcpy(paramNames[1], "VSEN");
          strcpy(paramNames[2], "LVLL");
          strcpy(paramNames[3], "LVLR");
          paramNum[0] = 28;
          paramNum[1] = 40;
          paramNum[2] = 33;
          paramNum[3] = 34;
          break;
        case 3: // pms, ams
          strcpy(menuName, "OSC2 4");
          strcpy(paramNames[0], "PMS");
          strcpy(paramNames[1], "AMS");
          strcpy(paramNames[2], "RING");
          strcpy(paramNames[3], "");
          paramNum[0] = 64;
          paramNum[1] = 68;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 13: // osc 3 submenu

      switch (presetNum[13]) {
        case 0: // onoff/phase/waveform/pulse width
          strcpy(menuName, "OSC3 1");
          strcpy(paramNames[0], "OSC");
          strcpy(paramNames[1], "PHAS");
          strcpy(paramNames[2], "WAVE");
          strcpy(paramNames[3], "PW");
          paramNum[0] = 3;
          paramNum[1] = 9;
          paramNum[2] = 13;
          paramNum[3] = 17;
          break;
        case 1: // transpose/drift/detune/saw detune
          strcpy(menuName, "OSC3 2");
          strcpy(paramNames[0], "TPOS");
          strcpy(paramNames[1], "DRFT");
          strcpy(paramNames[2], "TUNE");
          strcpy(paramNames[3], "SAWD");
          paramNum[0] = 21;
          paramNum[1] = 262;
          paramNum[2] = 25;
          paramNum[3] = 287;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          strcpy(menuName, "OSC3 3");
          strcpy(paramNames[0], "LVL");
          strcpy(paramNames[1], "VSEN");
          strcpy(paramNames[2], "LVLL");
          strcpy(paramNames[3], "LVLR");
          paramNum[0] = 29;
          paramNum[1] = 41;
          paramNum[2] = 35;
          paramNum[3] = 36;
          break;
        case 3: // pms, ams, ring mod
          strcpy(menuName, "OSC3 4");
          strcpy(paramNames[0], "PMS");
          strcpy(paramNames[1], "AMS");
          strcpy(paramNames[2], "RING");
          strcpy(paramNames[3], "");
          paramNum[0] = 65;
          paramNum[1] = 69;
          paramNum[2] = 271;
          paramNum[3] = -1;
          break;
      }
      break;
    case 14: // osc 4 submenu

      switch (presetNum[14]) {
        case 0: // onoff/phase/waveform/pulse width
          strcpy(menuName, "OSC4 1");
          strcpy(paramNames[0], "OSC");
          strcpy(paramNames[1], "PHAS");
          strcpy(paramNames[2], "WAVE");
          strcpy(paramNames[3], "PW");
          paramNum[0] = 4;
          paramNum[1] = 10;
          paramNum[2] = 14;
          paramNum[3] = 18;
          break;
        case 1: // transpose/drift/detune/saw detune
          strcpy(menuName, "OSC4 2");
          strcpy(paramNames[0], "TPOS");
          strcpy(paramNames[1], "DRFT");
          strcpy(paramNames[2], "TUNE");
          strcpy(paramNames[3], "SAWD");
          paramNum[0] = 22;
          paramNum[1] = 263;
          paramNum[2] = 26;
          paramNum[3] = 288;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          strcpy(menuName, "OSC4 3");
          strcpy(paramNames[0], "LVL");
          strcpy(paramNames[1], "VSEN");
          strcpy(paramNames[2], "LVLL");
          strcpy(paramNames[3], "LVLR");
          paramNum[0] = 30;
          paramNum[1] = 42;
          paramNum[2] = 37;
          paramNum[3] = 38;
          break;
        case 3: // pms, ams, ring mod
          strcpy(menuName, "OSC4 4");
          strcpy(paramNames[0], "PMS");
          strcpy(paramNames[1], "AMS");
          strcpy(paramNames[2], "RING");
          strcpy(paramNames[3], "");
          paramNum[0] = 66;
          paramNum[1] = 70;
          paramNum[2] = 271;
          paramNum[3] = -1;
          break;
      }
      break;
  }

  if (!doEG) {
    displayText(100);
    displayStatus(4);
  }

  doPreset = false;
}

void changeValue(int pNum, int pDir) { // inputs are parameter number and direction of change
  if (!bitEdit) { // when editing normal, non-bitwise values
    switch (pDir) {
      case 0:
        paramValue[pNum]--;
        break;
      case 1:
        paramValue[pNum]++;
        break;
      case 10:
        paramValue[pNum] -= 25;
        break;
      case 11:
        paramValue[pNum] += 25;
        break;
      case 12:
        paramValue[pNum] = previousValue[pNum];
        break;
    }

    paramValue[pNum] = checkValue(paramNum[pNum], paramValue[pNum]); // verify parameter value is valid
    setParam(paramNum[pNum], paramValue[pNum]);
    displayText(((pNum + 1) * 2) + 1); // update displayed value

  }
  else if (bitEdit) { // when editing bitwise values
    if (bitLocation[pNum] >= 0) {
      bitValues[bitNum][bitLocation[pNum]] = !bitValues[bitNum][bitLocation[pNum]];
    }

    storeBits();

    displayText(((pNum + 1) * 2) + 19);
  }

  patchModify = true;
  stateChange = true;
}

void changePatch() {
  int oldPatch = patchNum;
  if (checkModify()) {
    bool cont = false;
    display.clearDisplay();
    display.setCursor(30, 20);
    display.print("PATCH NUMBER: ");
    displayStatus(5);
    while (!cont) {
      encUpdate();

      if (enc1.isLeft() || enc2.isLeft() || enc3.isLeft() || enc4.isLeft()) { // turn any encoder to select patch to change to
        patchNum--;
        if (patchNum < 0) patchNum = 127;
        displayStatus(5);
      }
      else if (enc1.isLeftH() || enc2.isLeftH() || enc3.isLeftH() || enc4.isLeftH()) { // if encoder is held, will load patch as it changes
        patchNum--;
        if (patchNum < 0) patchNum = 127;
        displayStatus(5);
        loadPatch();
      }
      else if (enc1.isRight() || enc2.isRight() || enc3.isRight() || enc4.isRight()) {
        patchNum++;
        if (patchNum > 127) patchNum = 0;
        displayStatus(5);
      }
      else if (enc1.isRightH() || enc2.isRightH() || enc3.isRightH() || enc4.isRightH()) {
        patchNum++;
        if (patchNum < 0) patchNum = 127;
        displayStatus(5);
        loadPatch();
      }

      else if (tbtn2.isClick() || enc1.isClick() || enc2.isClick() || enc3.isClick() || enc4.isClick()) { // otherwise button two or one of the encoders must be clicked to select patch
        loadPatch();
        display.clearDisplay();
        clearText(0);
        displayText(10);
        cont = true;
        patchModify = false;
      }

      else if (tbtn1.isClick() || tbtn2.isClick() || tbtn3.isClick() || bbtn1.isClick() || bbtn2.isClick() || bbtn3.isClick() || bbtn4.isClick() || bbtn5.isClick() || bbtn6.isClick()) { // any other top button or all bottom buttons will cancel selection
        cont = true;
        patchNum = oldPatch;
      }
    }
  }

  display.clearDisplay();
}
