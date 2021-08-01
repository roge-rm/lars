#include <EncButton.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 128x64 OLED SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// encoder/button setup
EncButton <EB_TICK, 38, 39, 23> enc1;
EncButton <EB_TICK, 40, 41, 22> enc2;
EncButton <EB_TICK, 42, 43, 21> enc3;
EncButton <EB_TICK, 44, 45, 20> enc4;
EncButton <EB_TICK, 31> sbtn1;
EncButton <EB_TICK, 30> sbtn2;
EncButton <EB_TICK, 29> sbtn3;
EncButton <EB_TICK, 28> sbtn4;
EncButton <EB_TICK, 8> tbtn1;
EncButton <EB_TICK, 9> tbtn2;
EncButton <EB_TICK, 10> tbtn3;
EncButton <EB_TICK, 11> tbtn4;
EncButton <EB_TICK, 17> bbtn1;
EncButton <EB_TICK, 16> bbtn2;
EncButton <EB_TICK, 15> bbtn3;
EncButton <EB_TICK, 14> bbtn4;
EncButton <EB_TICK, 13> bbtn5;
EncButton <EB_TICK, 12> bbtn6;

// initialize global variables
int patchNum = 0; // patch number
int paramNum[4] = {1, 2, 3, 4}; // parameter numbers of the 4 values shown on screen
int paramValue[4] = {1, 2, 3, 4}; // parameter values currently shown on screen
int previousValue[4] = {0, 0, 0, 0}; // allow to reset parameter to previous value
int midiChan = 6; // what MIDI channel USB MIDI will respond to

int presetType = 0; // 0-Oscillators,1-Filters,2-Modulation,3-Effects,4-Global Param,5-MIDI Modulation
int presetNum[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // see spreadsheet for breakdown

bool bitEdit = 0; // editing bitwise values is handled differently
int bitNum = 0; // track which bitwiser number is being edited - see spreadsheet
bool bitValues[5][4];

void setup() {
  // screen initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Address 0x3C for 128x64
    for (;;); //Don't proceed, loop forever
  }
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();

  //Serial.begin(9600); // for monitoring purposes
  Serial1.begin(500000); // connection to XVA1 requires 500kbps

  usbMIDI.setHandleProgramChange(midiProgramChange);
  usbMIDI.setHandleNoteOn(midiNoteOn);
  usbMIDI.setHandleNoteOff(midiNoteOff);

  delay(500); // wait for XVA1 to initialize before blasting it with commands

  displayStatus(0);
  delay(500);
  displayText(100);
}



void loop() {
  encUpdate(); // update encoders and buttons

  // encoder/button press handling
  if (enc1.isLeft()) {
    changeValue(0, 0);
  }
  else if (enc1.isLeftH()) {
    changeValue(0, 10);
  }
  else if (enc1.isRight()) {
    changeValue(0, 1);
  }
  else if (enc1.isRightH()) {
    changeValue(0, 11);
  }
  else if (enc1.isClick()) {
    changeValue(0, 12);
  }

  if (enc2.isLeft()) {
    changeValue(1, 0);
  }
  else if (enc2.isLeftH()) {
    changeValue(1, 10);
  }
  else if (enc2.isRight()) {
    changeValue(1, 1);
  }
  else if (enc2.isRightH()) {
    changeValue(1, 11);
  }
  else if (enc2.isClick()) {
    changeValue(1, 12);
  }

  if (enc3.isLeft()) {
    changeValue(2, 0);
  }
  else if (enc3.isLeftH()) {
    changeValue(2, 10);
  }
  else if (enc3.isRight()) {
    changeValue(2, 1);
  }
  else if (enc3.isRightH()) {
    changeValue(2, 11);
  }
  else if (enc3.isClick()) {
    changeValue(2, 12);
  }

  if (enc4.isLeft()) {
    changeValue(3, 0);
  }
  else if (enc4.isLeftH()) {
    changeValue(3, 10);
  }
  else if (enc4.isRight()) {
    changeValue(3, 1);
  }
  else if (enc4.isRightH()) {
    changeValue(3, 11);
  }
    else if (enc4.isClick()) {
    changeValue(3, 12);
  }

  // top row button handling
  if (tbtn1.isPress()) { // decrease patch number
    patchNum--;
    if (patchNum < 0) patchNum = 127;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn1.isHold()) { // hold button to decrease patch number
    patchNum -= 1;
    if (patchNum < 0) patchNum = 127;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn2.isPress()) { // increase patch number
    patchNum++;
    if (patchNum > 127) patchNum = 0;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn2.isHold()) { // hold button to increase patch number
    patchNum += 1;
    if (patchNum > 127) patchNum = 0;
    loadPatch();
    displayStatus(2);;
  }
  else if (tbtn3.isClick()) { // load patch from EEPROM
    loadPatch();
    clearText(0);
    displayText(10);
    delay(1000);
    displayStatus(1);
  }
  else if (tbtn3.isHold()) { // initialize patch
    initPatch();
    displayText(12);
    delay(1000);
    displayStatus(1);
  }
  else if (tbtn4.isHold()) { // save patch to EEPROM
    changeSave();
    displayText(11);
    delay(1000);
    displayStatus(0);
  }

  //bottom row button handling
  if (bbtn1.isPress()) {
    if (presetType == 0) {
      presetNum[0]++;
      if (presetNum[0] > 21) presetNum[0] = 0;
    } else presetType = 0;
    changePreset();
  }
  else if (bbtn1.isHold()) {
    presetType = 0;
    presetNum[0] = 0;
    changePreset();
  }

  else if (bbtn2.isPress()) {
    if (presetType == 1) {
      presetNum[1]++;
      if (presetNum[1] > 6) presetNum[1] = 0;
    } else presetType = 1;
    changePreset();
  }
  else if (bbtn2.isHold()) {
    presetType = 1;
    presetNum[1] = 0;
    changePreset();
  }

  else if (bbtn3.isPress()) {
    if (presetType == 2) {
      presetNum[2]++;
      if (presetNum[2] > 10) presetNum[2] = 0;
    } else presetType = 2;
    changePreset();
  }
  else if (bbtn3.isHold()) {
    presetType = 2;
    presetNum[2] = 0;
    changePreset();
  }

  else if (bbtn4.isPress()) {
    if (presetType == 3) {
      presetNum[3]++;
      if (presetNum[3] > 2) presetNum[3] = 0;
    } else presetType = 3;
    changePreset();
  }
  else if (bbtn4.isHold()) {
    presetType = 3;
    presetNum[3] = 0;
    changePreset();
  }

  else if (bbtn5.isPress()) {
    if (presetType == 4) {
      presetNum[4]++;
      if (presetNum[4] > 18) presetNum[4] = 0;
    } else presetType = 4;
    changePreset();
  }
  else if (bbtn5.isHold()) {
    presetType = 4;
    presetNum[4] = 0;
    changePreset();
  }

  else if (bbtn6.isPress()) {
    if (presetType == 5) {
      presetNum[5]++;
      if (presetNum[5] > 5) presetNum[5] = 0;
    } else presetType = 5;
    changePreset();
  }
  else if (bbtn6.isHold()) {
    presetType = 5;
    presetNum[5] = 0;
    changePreset();
  }

  // handle buttons around screen (not encoders)
  if (sbtn1.isPress()) {
    if (presetType == 11) {
      presetNum[11]++;
      if (presetNum[11] > 3) presetNum[11] = 0;
    } else presetType = 11;
    changePreset();
  }
  else if (sbtn1.isHold()) {
    presetType = 11;
    presetNum[11] = 0;
    changePreset();
  }

  else if (sbtn2.isPress()) {
    if (presetType == 12) {
      presetNum[12]++;
      if (presetNum[12] > 3) presetNum[12] = 0;
    } else presetType = 12;
    changePreset();
  }
  else if (sbtn2.isHold()) {
    presetType = 12;
    presetNum[12] = 0;
    changePreset();
  }

  else if (sbtn3.isPress()) {
    if (presetType == 13) {
      presetNum[13]++;
      if (presetNum[13] > 3) presetNum[13] = 0;
    } else presetType = 13;
    changePreset();
  }
  else if (sbtn3.isHold()) {
    presetType = 13;
    presetNum[13] = 0;
    changePreset();
  }

  else if (sbtn4.isPress()) {
    if (presetType == 14) {
      presetNum[14]++;
      if (presetNum[14] > 3) presetNum[14] = 0;
    } else presetType = 14;
    changePreset();
  }
  else if (sbtn4.isHold()) {
    presetType = 14;
    presetNum[14] = 0;
    changePreset();
  }

  usbMIDI.read(midiChan);
}

void encUpdate() { // pulls values from encoders/buttons, needs to be run as often as possible
  enc1.tick();
  enc2.tick();
  enc3.tick();
  enc4.tick();
  sbtn1.tick();
  sbtn2.tick();
  sbtn3.tick();
  sbtn4.tick();
  tbtn1.tick();
  tbtn2.tick();
  tbtn3.tick();
  tbtn4.tick();
  bbtn1.tick();
  bbtn2.tick();
  bbtn3.tick();
  bbtn4.tick();
  bbtn5.tick();
  bbtn6.tick();
}

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

/* Parameter checking */

int checkParam(int pNum) { // take parameter number as input, return valid parameter number as output
  if ((pNum < 1) && (pNum > -1)) pNum = 511;
  else if ((pNum > 251) && (pNum < 258)) pNum = 260;
  else if ((pNum < 260) && (pNum > 253)) pNum = 251;
  else if ((pNum > 397) && (pNum < 399)) pNum = 400;
  else if ((pNum < 400) && (pNum > 398)) pNum = 397;
  else if ((pNum > 415) && (pNum < 426)) pNum = 428;
  else if ((pNum < 428) && (pNum > 417)) pNum = 415;
  else if ((pNum > 454) && (pNum < 506)) pNum = 508;
  else if ((pNum < 508) && (pNum > 456)) pNum = 454;
  else if (pNum > 511) pNum = 1;

  return pNum;
}

int checkValue(int pNum, int pVal) { // take parameter number and value as input, return pvalue after checking
  switch (pNum) {
    // 0-1
    case 1 ... 4: // osc 1-4 on/off
    case 55 ... 62: // key lcurve & key rcurve
    case 244: // legato
    case 271: // ring mod 3-4
    case 278: // routing
    case 292: // fx delay 2X time
    case 350: // fx distortion on/off
    case 385 ... 386: // fx gate on/off & curve
    case 392: // fx reverb mode
    case 428: // sequencer on/off
      if (pVal < 0) pVal = 1;
      else if (pVal > 1) pVal = 0;
      break;

    // 0-2
    case 245: // porta mode
    case 302: //fx delay mode
    case 312: // fx phaser mode
    case 508: // fx routing mode
      if (pVal < 0) pVal = 2;
      else if (pVal > 2) pVal = 0;
      break;

    // 0-3
    case 7 ... 10: // phase
    case 162: // LFO1 sync
    case 172: // LFO2 sync
    case 354: // fx distortion type
    case 362: // fx chorus/flanger mode
    case 510 ... 511: // gain pre/post fx
      if (pVal < 0) pVal = 3;
      else if (pVal > 3) pVal = 0;
      break;

    // 0-5
    case 450: // arp mode
      if (pVal < 0) pVal = 5;
      else if (pVal > 5) pVal = 0;
      break;

    // 0-7
    case 13 ... 14: // waveforms osc 3 & 4
    case 275: // drive
    case 291: // fx delay smear
    case 340: // fx bandwidth
    case 353: // fx distortion filter post
      if (pVal < 0) pVal = 7;
      else if (pVal > 7) pVal = 0;
      break;

    // 0-9
    case 11 ... 12: // waveforms osc 1 & 2
    case 160: // LFO1 waveform
    case 170: // LFO2 waveform
      if (pVal < 0) pVal = 9;
      else if (pVal > 9) pVal = 0;
      break;

    // 1-10
    case 308 ... 309: // fx delay tempo multiplier/divider
    case 432: // seq tempo multiplier
    case 453 ... 454: // arp tempo multiplier & number of octaves
      if (pVal < 1) pVal = 10;
      else if (pVal > 10) pVal = 1;
      break;

    // 4-12
    case 317: // fx phaser stages
      if (pVal < 4) pVal = 12;
      else if (pVal > 12) pVal = 4;
      break;

    // 0-15
    case 5 ... 6: // sync & mode
      if (pVal < 0) pVal = 15;
      else if (pVal > 15) pVal = 0;
      break;

    // 1-16
    case 430: // sync & mode
      if (pVal < 1) pVal = 16;
      else if (pVal > 16) pVal = 1;
      break;

    // 0-21
    case 71: // filter type
      if (pVal < 0) pVal = 21;
      else if (pVal > 21) pVal = 0;
      break;

    // 0-24
    case 370: // fx decimator depth
    case 380: // fx bitcrusher depth
      if (pVal < 0) pVal = 24;
      else if (pVal > 24) pVal = 0;
      break;

    // 0-31
    case 296: // fx early reflections room
      if (pVal < 0) pVal = 31;
      else if (pVal > 31) pVal = 0;
      break;

    // 0-32
    case 293: // fx early reflections taps
      if (pVal < 0) pVal = 32;
      else if (pVal > 32) pVal = 0;
      break;

    // 0-3, 65-67
    case 145 ... 147: // eg loop, eg loop seg, eg restart
      if (pVal < 0) pVal = 67;
      else if ((pVal > 3) && (pVal < 63)) pVal = 65;
      else if ((pVal < 65) && (pVal > 5)) pVal = 3;
      else if (pVal > 67) pVal = 0;
      break;

    // 0-100
    case 39 ... 42: // velo sense
    case 47 ... 54: // key ldepth & key rdepth
    case 72: // cutoff...
    case 77 ... 79: // ... & resonance
    case 110 ... 112: // eg delay
    case 148 ... 149: // pitch range && velocity
    case 164 ... 165: // LFO1 depth pitch && amp
    case 166: // LFO1 range
    case 174 ... 175: // LFO2 depth PW and cutoff
    case 176: // LFO2 range
    case 180 ... 195: // pitch, amp, cutoff, PW LFO midi modulation
    case 203: // note pitch change randomization
    case 239: // temp offset
    case 242 ... 243: // bend up/down range
    case 246: // porta time
    case 249: // velocity offset
    case 260 ... 263: // drift
    case 285 ... 288: // sawstack detune
    case 297: // fx early reflections feedback
    case 298 ... 299: // fx delay mod speed/mod depth
    case 304: // fx delay time, feedback
    case 315: // fx phaser feedback
    case 316: // fx phaser offset
    case 332: // fx AM range
    case 351 ... 352: // fx distortion gain pre/post
    case 365: // fx chorus/flanger feedback
    case 387 ... 388: // fx gate attack/release time
    case 396: // fx reverb mod depth
    case 429: // sequencer velocity
      if (pVal < 0) pVal = 100;
      else if (pVal > 100) pVal = 0;
      break;

    // 0-127
    case 43 ... 46: // keyboard breakpoint
      if (pVal < 0) pVal = 127;
      else if (pVal > 127) pVal = 0;
      break;

    // 0,50-255
    case 307: // fx delay tempo
    case 431: // seq tempo
    case 451: // arp tempo
      if (pVal < 0) pVal = 255;
      else if ((pVal > 0) && (pVal < 48)) pVal = 50;
      else if ((pVal < 50) && (pVal > 1)) pVal = 0;
      else if (pVal > 255) pVal = 0;
      break;

    // 0-127,200-201,255
    case 434 ... 449: // seq step1 through step16
      if (pVal < 0) pVal = 255;
      else if ((pVal > 127) && (pVal < 198)) pVal = 200;
      else if ((pVal < 200) && (pVal > 128)) pVal = 127;
      else if ((pVal > 201) && (pVal < 254)) pVal = 255;
      else if ((pVal < 255) && (pVal > 202)) pVal = 201;
      else if (pVal > 255) pVal = 0;
      break;

    // 0-255
    case 15 ... 18: // pulse width
    case 19 ... 22: // transpose
    case 23 ... 26: // tune
    case 27 ... 38: // level, level l, level r
    case 63 ... 70: // PMS & AMS
    case 73 ... 76: // velocity, kbd track, eg depth, eg velocity
    case 80 ... 107: // eg segment SADSRR levels
    case 115 ... 137: // eg segment ADSRR levels
    case 161: // LFO1 speed
    case 171: // LFO2 speed
    case 163: // LFO1 fade
    case 173: // LFO2 fade
    case 200 ... 202: // pitch after/breath/foot midi mod
    case 204 ... 231: // MIDI modulation
    case 241: // transpose
    case 247 ... 248: // pan & volume
    case 251: // alternate tuning
    case 276 ... 277: // velocity resonance, kbd track resonance
    case 294 ... 295: // fx early reflections dry/wet
    case 300 ... 301: // fx delay dry/wet
    case 303: // fx delay time
    case 305 ... 306: // fx delay lo/hi cutoff
    case 310 ... 311: // fx phaser dry/wet
    case 313 ... 314: // fx phaser depth/speed
    case 318: // fx phaser lr phase
    case 320 ... 321: // fx filter lo/hi cutoff
    case 330 ... 331: // fx AM depth/speed
    case 333: // fx AM lr phase
    case 360 ... 361: // fx chorus/flanger dry/wet
    case 363 ... 364: // fx chorus/flanger speed/depth
    case 366: // fx chorus/flanger lr phase
    case 390 ... 391: // fx reverb dry/wet
    case 393 ... 395: // fx reverb decay/amp/hpf/mod speed
    case 433: // seq transpose
    case 509: // volume
      if (pVal < 0) pVal = 255;
      else if (pVal > 255) pVal = 0;
      break;
  }

  return pVal;
}

/* Define menu and parameter names */

// store menu headings in char arrays
char menu0Names[22][13] = {"OSC ON/OFF", "WAVEFORM", "PULSE WIDTH", "SAWSTACK DET", "SYNC", "PHASE", "MODE", "TRANSPOSE", "DETUNE", "DRIFT", "LEVEL", "LEVEL L", "LEVEL R", "VELO SENS", "KEY BP", "KEY LDEPTH", "KEY RDEPTH", "KEY LCURVE", "KEY RCURVE", "PM SENS", "AM SENS", "RING MOD"};
char menu1Names[7][13] = {"  FILTER", "  CUTOFF", "RESO 1/2", "VEL/KB TRACK", "ENV GEN", "VEL/KB RESO", "DRIVE/ROUTE"};
char menu2Names[11][13] = {"LFO WAVE", "LFO RANGE", "LFO SPEED", "LFO SYNC", "LFO FADE", "LFO1 DEPTH", "LFO2 DEPTH", "PITCH LFO", "PW LFO", "FILTER LFO", "AMP LFO"};
char menu3Names[7][13] = {"PITCH ADSR", "CUTOFF ADSR", "AMP ADSR"};
char menu4Names[19][15] = {"BW & ROUTING", "  DISTORT", "DISTORT GAIN", "CRUSH/DECIM", "FILTER CUTOFF", "CHORUS/FLANGER", "CHORUS/FLANGER", " PHASER 1", " PHASER 2", "  AMP MOD", "  DELAY 1", "  DELAY 2", "  DELAY 3", "  DELAY 4", " EAREFLECT", " EAREFLECT", " REVERB 1", " REVERB 2", "   GATE"};
char menu5Names[6][13] = {"  GLOBAL", "PORTMENTO", "PAN & VOLUME", " OFFSET TUNE", "    ARP", "  OUTPUT"};
char menu11Names[4][8] = {"OSC1 1", "OSC1 2", "OSC1 3", "OSC1 4"};
char menu12Names[4][8] = {"OSC2 1", "OSC2 2", "OSC2 3", "OSC2 4"};
char menu13Names[4][8] = {"OSC3 1", "OSC3 2", "OSC3 3", "OSC3 4"};
char menu14Names[4][8] = {"OSC4 1", "OSC4 2", "OSC4 3", "OSC4 4"};


// store parameter names in char arrays
char paramName0[4][5] = {"OSC1", "OSC2", "OSC3", "OSC4"};
char paramName1_1[7][5] = {"TYPE",  "CUT1", "RES1", "VELO", "DPTH", "VELO", "DRV"};
char paramName1_2[7][5] = {"",      "CUT2", "RES2", "KB",   "VELO", "KB",   "ROUT"};
char paramName2_1[11][5] = {"LFO1", "LFO1", "LFO1", "LFO1", "LFO1", "PTCH", "PW", "AFT", "AFT", "AFT", "AFT"};
char paramName2_2[11][5] = {"LFO2", "LFO2", "LFO2", "LFO2", "LFO2", "AMP", "CUT", "WHL", "WHL", "WHL", "WHL"};
char paramName2_3[11][5] = {"", "", "", "", "", "", "", "BRTH", "BRTH", "BRTH", "BRTH"};
char paramName2_4[11][5] = {"", "", "", "", "", "", "", "FOOT", "FOOT", "FOOT", "FOOT"};
char paramName3_1[4][5] = {"ATK", "ATK", "ATK", "ATK"};
char paramName3_2[4][5] = {"DEC", "DEC", "DEC", "DEC"};
char paramName3_3[4][5] = {"SUS", "SUS", "SUS", "SUS"};
char paramName3_4[4][5] = {"REL", "REL", "REL", "REL"};
char paramName4_1[19][5] = {"BW",   "ON", "PRE",  "BIT",  "LO", "DRY",  "SPD",  "DRY",  "SPD",  "SPD",  "DRY",  "FEED", "MUL",  "SMEA", "DRY",  "TAPS", "DRY",  "DAMP", "GATE"};
char paramName4_2[19][5] = {"ROUT", "TYPE",   "POST", "DEC",  "HI", "WET",  "DPTH", "WET",  "DPTH", "DPTH", "WET",  "LO",   "DIV",  "2X",   "WET",  "FEED", "WET",  "HPF",  "CURV"};
char paramName4_3[19][5] = {"",     "",       "FILT", "",     "",   "MODE", "FEED", "MODE", "FEED", "RANG", "MODE", "HI",   "SPD",  "",     "ROOM", "",     "MODE", "SPD",  "ATK"};
char paramName4_4[19][5] = {"",     "",       "",     "",     "",   "",     "PHAS", "STAG", "PHAS", "PHAS", "TIME", "TMPO", "DPTH", "",     "",     "",     "DCAY", "DPTH", "REL"};
char paramName5_1[6][5] = {"TRAN",  "MODE", "PAN",  "VOFF",  "MODE", "VOL"};
char paramName5_2[6][5] = {"LEGT",  "TIME", "VOL",  "TUNE", "TEMP", "PRE"};
char paramName5_3[6][5] = {"B UP",  "",     "",     "TOFF", "MUL",  ""};
char paramName5_4[6][5] = {"B DN",  "",     "",     "",     "OCT",  "POST"};
char paramName6_1[4][5] = {"ON",   "TRAN", "LVL",  "PMS"};
char paramName6_2[4][5] = {"PHAS", "DRFT", "VSEN", "AMS"};
char paramName6_3[4][5] = {"WAVE", "TUNE", "LVLL", "RING"};
char paramName6_4[4][5] = {"PW",   "SAW",  "LVLR", ""};

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

/* USB MIDI response */

void midiProgramChange (byte channel, byte program) { // respond to PC messages over USB MIDI
  patchNum = program;
  if (patchNum < 0) patchNum = 127;
  if (patchNum > 127) patchNum = 0;
  loadPatch();
  displayStatus(2);
}

void midiNoteOn (byte channel, byte note, byte velocity) {

}

void midiNoteOff (byte channel, byte note, byte velocity) {

}

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
