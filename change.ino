/* Change preset, param, values */

int changeMIDI() { // change what MIDI port the XVA1 responds to
  bool cont = false;
  display.clearDisplay();
  display.setCursor(15, 30);
  display.print("MIDI PORT: ");
  displayStatus(6);
  while (!cont) {
    encUpdate();

    if (enc1.isLeft()) {
      midiPort--;
      if (midiPort < 0) midiPort = 16;
      displayStatus(6);
    }
    else if (enc1.isRight()) {
      midiPort++;
      if (midiPort > 16) midiPort = 0;
      displayStatus(6);
    }

    else if (tbtn4.isPress()) {
      setMIDI(midiPort);
      cont = true;
      return 1;
    }
    else if (tbtn1.isPress() || tbtn2.isPress() || tbtn3.isPress()) {
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

    if (enc1.isLeft()) {
      patchNum--;
      if (patchNum < 0) patchNum = 127;
      displayStatus(5);
    }
    else if (enc1.isRight()) {
      patchNum++;
      if (patchNum > 127) patchNum = 0;
      displayStatus(5);
    }

    else if (tbtn4.isPress()) {
      savePatch();
      cont = true;
      return 1;
    }
    else if (tbtn1.isPress() || tbtn2.isPress() || tbtn3.isPress()) {
      cont = true;
      return 0;
    }
  }

}

void changePreset() {
  stateChange = true;
  switch (presetType) {
    case 0: // oscillators

      if (presetNum[0] == 4 || presetNum[0] == 6) bitEdit = 1;
      else bitEdit = 0;

      switch (presetNum[0]) {
        case 0: // on/off
          paramNum[0] = 1;
          paramNum[1] = 2;
          paramNum[2] = 3;
          paramNum[3] = 4;
          break;
        case 1: // waveform
          paramNum[0] = 11;
          paramNum[1] = 12;
          paramNum[2] = 13;
          paramNum[3] = 14;
          break;
        case 2: // pulse width
          paramNum[0] = 15;
          paramNum[1] = 16;
          paramNum[2] = 17;
          paramNum[3] = 18;
          break;
        case 3: // sawstack detune
          paramNum[0] = 285;
          paramNum[1] = 286;
          paramNum[2] = 287;
          paramNum[3] = 288;
          break;
        case 4: // sync
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
          paramNum[0] = 7;
          paramNum[1] = 8;
          paramNum[2] = 9;
          paramNum[3] = 10;
          break;
        case 6: // mode
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
          paramNum[0] = 19;
          paramNum[1] = 20;
          paramNum[2] = 21;
          paramNum[3] = 22;
          break;
        case 8: // tune
          paramNum[0] = 23;
          paramNum[1] = 24;
          paramNum[2] = 25;
          paramNum[3] = 26;
          break;
        case 9: // drift
          paramNum[0] = 260;
          paramNum[1] = 261;
          paramNum[2] = 262;
          paramNum[3] = 263;
          break;
        case 10: // level
          paramNum[0] = 27;
          paramNum[1] = 28;
          paramNum[2] = 29;
          paramNum[3] = 30;
          break;
        case 11: // level l
          paramNum[0] = 31;
          paramNum[1] = 33;
          paramNum[2] = 35;
          paramNum[3] = 37;
          break;
        case 12: // level r
          paramNum[0] = 32;
          paramNum[1] = 34;
          paramNum[2] = 36;
          paramNum[3] = 38;
          break;
        case 13: // velo sens
          paramNum[0] = 39;
          paramNum[1] = 40;
          paramNum[2] = 41;
          paramNum[3] = 42;
          break;
        case 14: // key bp
          paramNum[0] = 43;
          paramNum[1] = 44;
          paramNum[2] = 45;
          paramNum[3] = 46;
          break;
        case 15: // key ldepth
          paramNum[0] = 47;
          paramNum[1] = 48;
          paramNum[2] = 49;
          paramNum[3] = 50;
          break;
        case 16: // key rdepth
          paramNum[0] = 51;
          paramNum[1] = 52;
          paramNum[2] = 53;
          paramNum[3] = 54;
          break;
        case 17: // key lcurve
          paramNum[0] = 55;
          paramNum[1] = 56;
          paramNum[2] = 57;
          paramNum[3] = 58;
          break;
        case 18: // key rcurve
          paramNum[0] = 59;
          paramNum[1] = 60;
          paramNum[2] = 61;
          paramNum[3] = 62;
          break;
        case 19: // pitch mod sens
          paramNum[0] = 63;
          paramNum[1] = 64;
          paramNum[2] = 65;
          paramNum[3] = 66;
          break;
        case 20: // amp mod sens
          paramNum[0] = 67;
          paramNum[1] = 68;
          paramNum[2] = 69;
          paramNum[3] = 70;
          break;
        case 21: // ring mod
          paramNum[0] = -1;
          paramNum[1] = -1;
          paramNum[2] = 271;
          paramNum[3] = -1;
          break;
      }

      displayText(100);

      break;
    case 1: // filters
      displayText(101);
      switch (presetNum[1]) {
        case 0: // filter type
          paramNum[0] = 71;
          paramNum[1] = -1;
          paramNum[2] = 275;
          paramNum[3] = 278;
          break;
        case 1: // cutoff/reso 1/2
          paramNum[0] = 72;
          paramNum[1] = 78;
          paramNum[2] = 77;
          paramNum[3] = 79;
          break;
        case 2: // vel/kb track/reso 1/2
          paramNum[0] = 77;
          paramNum[1] = 79;
          paramNum[2] = 276;
          paramNum[3] = 277;
          break;
        case 3: // eg depth/velocity
          paramNum[0] = 75;
          paramNum[1] = 79;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 2: // modulation
      displayText(102);
      switch (presetNum[2]) {
        case 0: // LFO1 wave/range/speed/sync
          paramNum[0] = 160;
          paramNum[1] = 166;
          paramNum[2] = 161;
          paramNum[3] = 162;
          break;
        case 1: // LFO1 fade/depth pitch/depth amp
          paramNum[0] = 163;
          paramNum[1] = 164;
          paramNum[2] = 165;
          paramNum[3] = -1;
          break;
        case 2: // LFO2 wave/range/speed/sync
          paramNum[0] = 170;
          paramNum[1] = 176;
          paramNum[2] = 171;
          paramNum[3] = 172;
          break;
        case 3: // LFO2 fade/depth pulse width/depth cutoff
          paramNum[0] = 173;
          paramNum[1] = 174;
          paramNum[2] = 175;
          paramNum[3] = -1;
          break;
        case 4: // LFO after pitch/pw/filter/amp
          paramNum[0] = 180;
          paramNum[1] = 184;
          paramNum[2] = 188;
          paramNum[3] = 192;
          break;
        case 5: // LFO wheel pitch/pw/filter/amp
          paramNum[0] = 181;
          paramNum[1] = 185;
          paramNum[2] = 189;
          paramNum[3] = 193;
          break;
        case 6: // LFO breath pitch/pw/filter/amp
          paramNum[0] = 182;
          paramNum[1] = 186;
          paramNum[2] = 190;
          paramNum[3] = 194;
          break;
        case 7: // LFO foot pitch/pw/filter/amp
          paramNum[0] = 183;
          paramNum[1] = 187;
          paramNum[2] = 191;
          paramNum[3] = 195;
          break;
        case 8: // MIDI after pitch/pw/cutoff/volume
          paramNum[0] = 200;
          paramNum[1] = 204;
          paramNum[2] = 208;
          paramNum[3] = 212;
          break;
        case 9: // MIDI breath pitch/pw/cutoff/volume
          paramNum[0] = 201;
          paramNum[1] = 206;
          paramNum[2] = 210;
          paramNum[3] = 214;
          break;
        case 10: // MIDI rnd/wheel pitch/pw/cutoff/volume
          paramNum[0] = 203;
          paramNum[1] = 205;
          paramNum[2] = 209;
          paramNum[3] = 213;
          break;
        case 11: // MIDI foot pitch/pw/cutoff/volume
          paramNum[0] = 202;
          paramNum[1] = 207;
          paramNum[2] = 211;
          paramNum[3] = 215;
          break;
        case 12: // MIDI temp pitch/pw/cutoff/volume
          paramNum[0] = 220;
          paramNum[1] = 223;
          paramNum[2] = 226;
          paramNum[3] = 229;
          break;
      }
      break;
    case 3: // envelope generators
      if (!doEG) displayText(103);
      if (presetNum[3] > 2 && presetNum[3] < 6) bitEdit = 1;
      else bitEdit = 0;

      switch (presetNum[3]) {
        case 0: // amp adsr
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
      displayText(104);
      switch (presetNum[4]) {
        case 0: // bw/routing
          paramNum[0] = 340;
          paramNum[1] = 508;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 1: // distort on/type
          paramNum[0] = 350;
          paramNum[1] = 354;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 2: // distort gain pre/post/filter post
          paramNum[0] = 351;
          paramNum[1] = 352;
          paramNum[2] = 353;
          paramNum[3] = -1;
          break;
        case 3: // bitcrusher/decimator
          paramNum[0] = 380;
          paramNum[1] = 370;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 4: // filter lo/hi cutoff
          paramNum[0] = 320;
          paramNum[1] = 321;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 5: // chorus/flanger dry/wet/mode
          paramNum[0] = 360;
          paramNum[1] = 361;
          paramNum[2] = 362;
          paramNum[3] = -1;
          break;
        case 6: // chorus/flanger speed/depth/feedback/phase
          paramNum[0] = 363;
          paramNum[1] = 364;
          paramNum[2] = 365;
          paramNum[3] = 366;
          break;
        case 7: // phaser dry/wet/mode/stages
          paramNum[0] = 310;
          paramNum[1] = 311;
          paramNum[2] = 312;
          paramNum[3] = 317;
          break;
        case 8: // phaser speed/depth/feedback/phase
          paramNum[0] = 314;
          paramNum[1] = 315;
          paramNum[2] = 316;
          paramNum[3] = 318;
          break;
        case 9: // amp mod speed/depth/range/phase
          paramNum[0] = 331;
          paramNum[1] = 330;
          paramNum[2] = 332;
          paramNum[3] = 333;
          break;
        case 10: // delay dry/wet/mode/time
          paramNum[0] = 300;
          paramNum[1] = 301;
          paramNum[2] = 302;
          paramNum[3] = 303;
          break;
        case 11: // delay mul/div/mod speed/mod depth
          paramNum[0] = 308;
          paramNum[1] = 309;
          paramNum[2] = 298;
          paramNum[3] = 299;
          break;
        case 12: // delay feedback/lo/hi/tempo
          paramNum[0] = 304;
          paramNum[1] = 305;
          paramNum[2] = 306;
          paramNum[3] = 307;
          break;
        case 13: // delay smear/2x
          paramNum[0] = 291;
          paramNum[1] = 292;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 14: // er dry/wet/room
          paramNum[0] = 294;
          paramNum[1] = 295;
          paramNum[2] = 296;
          paramNum[3] = -1;
          break;
        case 15: // er taps/feedback
          paramNum[0] = 293;
          paramNum[1] = 297;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 16: // reverb dry/wet/mode/decay
          paramNum[0] = 390;
          paramNum[1] = 391;
          paramNum[2] = 392;
          paramNum[3] = 393;
          break;
        case 17: // reverb damp/hpf/mod speed/mod depth
          paramNum[0] = 390;
          paramNum[1] = 391;
          paramNum[2] = 392;
          paramNum[3] = 393;
          break;
        case 18: // gate onoff/curve/attack/release
          paramNum[0] = 385;
          paramNum[1] = 386;
          paramNum[2] = 387;
          paramNum[3] = 388;
          break;
      }
      break;
    case 5: // global params
      displayText(105);
      switch (presetNum[5]) {
        case 0: // transpose/legato/bend up/bend down
          paramNum[0] = 241;
          paramNum[1] = 244;
          paramNum[2] = 242;
          paramNum[3] = 243;
          break;
        case 1: // porta mode/time
          paramNum[0] = 245;
          paramNum[1] = 246;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 2: // pan/volume
          paramNum[0] = 247;
          paramNum[1] = 248;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 3: // velo offset/tuning/temp offset
          paramNum[0] = 249;
          paramNum[1] = 251;
          paramNum[2] = 239;
          paramNum[3] = -1;
          break;
        case 4: // arp mode/tempo/mul/octaves
          paramNum[0] = 450;
          paramNum[1] = 451;
          paramNum[2] = 453;
          paramNum[3] = 454;
          break;
        case 5: // output volume/gain pre/gain post
          paramNum[0] = 509;
          paramNum[1] = 510;
          paramNum[2] = -1;
          paramNum[3] = 511;
          break;
      }
      break;
    case 11: // osc 1 submenu
      displayText(111);
      switch (presetNum[11]) {
        case 0: // onoff/phase/waveform/pulse width
          paramNum[0] = 1;
          paramNum[1] = 7;
          paramNum[2] = 11;
          paramNum[3] = 15;
          break;
        case 1: // transpose/drift/detune/saw detune
          paramNum[0] = 19;
          paramNum[1] = 260;
          paramNum[2] = 23;
          paramNum[3] = 285;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          paramNum[0] = 27;
          paramNum[1] = 39;
          paramNum[2] = 31;
          paramNum[3] = 32;
          break;
        case 3: // pms, ams
          paramNum[0] = 63;
          paramNum[1] = 67;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 12: // osc 2 submenu
      displayText(112);
      switch (presetNum[12]) {
        case 0: // onoff/phase/waveform/pulse width
          paramNum[0] = 2;
          paramNum[1] = 8;
          paramNum[2] = 12;
          paramNum[3] = 16;
          break;
        case 1: // transpose/drift/detune/saw detune
          paramNum[0] = 20;
          paramNum[1] = 261;
          paramNum[2] = 24;
          paramNum[3] = 286;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          paramNum[0] = 28;
          paramNum[1] = 40;
          paramNum[2] = 33;
          paramNum[3] = 34;
          break;
        case 3: // pms, ams
          paramNum[0] = 64;
          paramNum[1] = 68;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 13: // osc 3 submenu
      displayText(113);
      switch (presetNum[13]) {
        case 0: // onoff/phase/waveform/pulse width
          paramNum[0] = 3;
          paramNum[1] = 9;
          paramNum[2] = 13;
          paramNum[3] = 17;
          break;
        case 1: // transpose/drift/detune/saw detune
          paramNum[0] = 21;
          paramNum[1] = 262;
          paramNum[2] = 25;
          paramNum[3] = 287;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          paramNum[0] = 29;
          paramNum[1] = 41;
          paramNum[2] = 35;
          paramNum[3] = 36;
          break;
        case 3: // pms, ams, ring mod
          paramNum[0] = 65;
          paramNum[1] = 69;
          paramNum[2] = 271;
          paramNum[3] = -1;
          break;
      }
      break;
    case 14: // osc 4 submenu
      displayText(114);
      switch (presetNum[14]) {
        case 0: // onoff/phase/waveform/pulse width
          paramNum[0] = 4;
          paramNum[1] = 10;
          paramNum[2] = 14;
          paramNum[3] = 18;
          break;
        case 1: // transpose/drift/detune/saw detune
          paramNum[0] = 22;
          paramNum[1] = 263;
          paramNum[2] = 26;
          paramNum[3] = 288;
          break;
        case 2: // level/velocity sensitivity,level l, level r
          paramNum[0] = 30;
          paramNum[1] = 42;
          paramNum[2] = 37;
          paramNum[3] = 38;
          break;
        case 3: // pms, ams, ring mod
          paramNum[0] = 66;
          paramNum[1] = 70;
          paramNum[2] = 271;
          paramNum[3] = -1;
          break;
      }
      break;
  }

  if (!doEG) {
    displayStatus(4);
  }


  doPreset = false;
}

void changeParam(int pNum, int pDir) { // inputs are parameter number and direction of change (0/down, 1/up)
  stateChange = true;
  switch (pDir) {
    case 0:
      paramNum[pNum]--; // reduce param num by one
      break;
    case 1:
      paramNum[pNum]++; // increment param num by oneo
      break;
  }

  paramNum[pNum] = checkParam(paramNum[pNum]); // verify param number is valid
  paramValue[pNum] = getParam(paramNum[pNum]); // pull value for new param number from XVA1
  displayText((pNum + 1) * 2); // update heading for encoder
  displayText(((pNum + 1) * 2) + 1); // update value to go along with new paramnum

}

void changeValue(int pNum, int pDir) { // inputs are parameter number and direction of change
  stateChange = true;
  if (!bitEdit) { // when editing normal, non-bitwise values
    switch (pDir) {
      case 0:
        paramValue[pNum]--;
        break;
      case 1:
        paramValue[pNum]++;
        break;
      case 10:
        paramValue[pNum] -= 10;
        break;
      case 11:
        paramValue[pNum] += 10;
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


}
