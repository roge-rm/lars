/* Change preset, param, values */

void changeSave() { // prompt for patch number to save to
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

    else if (tbtn4.isPress()) cont = true;
  }
  savePatch();
}

void changePreset() {
  switch (presetType) {
    case 0: // oscillators
      displayText(100);

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
          readBits(5);
          break;
        case 5: // phase
          paramNum[0] = 7;
          paramNum[1] = 8;
          paramNum[2] = 9;
          paramNum[3] = 10;
          break;
        case 6: // mode
          bitNum = 1;
          readBits(6);
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
          paramNum[3] = 39;
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
      break;
    case 1: // filters
      displayText(101);
      switch (presetNum[1]) {
        case 0: // filter type
          paramNum[0] = 71;
          paramNum[1] = -1;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 1: // cutoff 1/2
          paramNum[0] = 72;
          paramNum[1] = 78;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 2: // reso 1/2
          paramNum[0] = 77;
          paramNum[1] = 79;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 3: // velocity/kb track
          paramNum[0] = 73;
          paramNum[1] = 74;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 4: // eg depth/velocity
          paramNum[0] = 75;
          paramNum[1] = 79;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 5: // velocity/kb track reso
          paramNum[0] = 279;
          paramNum[1] = 277;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 6: // drive/routing
          paramNum[0] = 275;
          paramNum[1] = 278;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
      }
      break;
    case 2: // modulation
      displayText(102);
      switch (presetNum[2]) {
        case 0: // waveform
          paramNum[0] = 160;
          paramNum[1] = 170;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 1: // range
          paramNum[0] = 166;
          paramNum[1] = 176;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 2: // speed
          paramNum[0] = 161;
          paramNum[1] = 171;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 3: // sync
          paramNum[0] = 162;
          paramNum[1] = 172;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 4: // fade
          paramNum[0] = 163;
          paramNum[1] = 173;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 5: // lfo1 depth pitch/amp
          paramNum[0] = 164;
          paramNum[1] = 165;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 6: // lfo2 depth pw/cutoff
          paramNum[0] = 174;
          paramNum[1] = 175;
          paramNum[2] = -1;
          paramNum[3] = -1;
          break;
        case 7: // pitch lfo after/wheel/breath/foot
          paramNum[0] = 180;
          paramNum[1] = 181;
          paramNum[2] = 182;
          paramNum[3] = 183;
          break;
        case 8: // pw  lfo after/wheel/breath/foot
          paramNum[0] = 184;
          paramNum[1] = 185;
          paramNum[2] = 186;
          paramNum[3] = 187;
          break;
        case 9: // filter lfo after/wheel/breath/foot
          paramNum[0] = 188;
          paramNum[1] = 189;
          paramNum[2] = 190;
          paramNum[3] = 191;
          break;
        case 10: // amp lfo after/wheel/breath/foot
          paramNum[0] = 192;
          paramNum[1] = 193;
          paramNum[2] = 194;
          paramNum[3] = 195;
          break;
      }
      break;
    case 3: // envelope generators
      displayText(103);
      switch (presetNum[3]) {
        case 0: // pitch adsr
          paramNum[0] = 85;
          paramNum[1] = 90;
          paramNum[2] = 95;
          paramNum[3] = 100;
          break;
        case 1: // cutoff adsr
          paramNum[0] = 86;
          paramNum[1] = 91;
          paramNum[2] = 96;
          paramNum[3] = 101;
          break;
        case 2: // amp adsr
          paramNum[0] = 87;
          paramNum[1] = 92;
          paramNum[2] = 97;
          paramNum[3] = 102;
          break;
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

  if (!bitEdit) displayStatus(4);
  else if (bitEdit) displayStatus(3);
}

void changeParam(int pNum, int pDir) { // inputs are parameter number and direction of change (0/down, 1/up)
  if (!bitEdit) { // when editing normal, non-bitwise values
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
  else { // when editing bitwise values

  }
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
    switch (pDir) {
      case 0:
      case 1:
        bitValues[bitNum][pNum] = !bitValues[bitNum][pNum];
        break;
    }

    storeBits(bitNum);
    displayText(((pNum + 1) * 2) + 19);
  }
}
