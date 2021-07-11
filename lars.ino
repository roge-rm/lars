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
int patchNum = 0;
int paramNum[4] = {1, 2, 3, 4};
bool paramFlag[4] = {0, 0, 0, 0}; // enabling flag allows for changing active param
int paramValue[4] = {1, 2, 3, 4};
int midiChan = 6; // what MIDI channel USB MIDI will respond to

void setup() {
  // screen initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); //Don't proceed, loop forever
  }
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();

  Serial.begin(9600); // for monitoring purposes
  Serial1.begin(500000); // connection to XVA1 requires 500kbps

  usbMIDI.setHandleProgramChange(midiProgramChange);

  delay(500); // wait for XVA1 to initialize before blasting it with commands

  displayStatus(0);
}

void loop() {
  encUpdate(); // update encoders and buttons

  if (enc1.isLeft()) {
    if (paramFlag[0]) changeParam(0, 0);
    else changeValue(0, 0);
  }
  else if (enc1.isRight()) {
    if (paramFlag[0]) changeParam(0, 1);
    else changeValue(0, 1);
  }
  else if (enc1.isClick()) {
    if (paramFlag[0]) changeParam(0, 2);
  }

  if (enc2.isLeft()) {
    if (paramFlag[1]) changeParam(1, 0);
    else changeValue(1, 0);
  }
  else if (enc2.isRight()) {
    if (paramFlag[1]) changeParam(1, 1);
    else changeValue(1, 1);
  }
  else if (enc2.isClick()) {
    if (paramFlag[1]) changeParam(1, 2);
  }

  if (enc3.isLeft()) {
    if (paramFlag[2]) changeParam(2, 0);
    else changeValue(2, 0);
  }
  else if (enc3.isRight()) {
    if (paramFlag[2]) changeParam(2, 1);
    else changeValue(2, 1);
  }
  else if (enc3.isClick()) {
    if (paramFlag[2]) changeParam(2, 2);
  }

  if (enc4.isLeft()) {
    if (paramFlag[3]) changeParam(3, 0);
    else changeValue(3, 0);
  }
  else if (enc4.isRight()) {
    if (paramFlag[3]) changeParam(3, 1);
    else changeValue(3, 1);
  }
  else if (enc4.isClick()) {
    if (paramFlag[3]) changeParam(3, 2);
  }

  if (sbtn1.isClick()) {
    paramFlag[0] = !paramFlag[0];
    displayText(2);
  }
  else if (sbtn2.isClick()) {
    paramFlag[1] = !paramFlag[1];
    displayText(4);
  }
  else if (sbtn3.isClick()) {
    paramFlag[2] = !paramFlag[2];
    displayText(6);
  }
  else if (sbtn4.isClick()) {
    paramFlag[3] = !paramFlag[3];
    displayText(8);
  }

  if (tbtn1.isPress()) {
    patchNum--;
    if (patchNum < 0) patchNum = 127;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn1.isHold()) {
    patchNum -= 1;
    if (patchNum < 0) patchNum = 127;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn2.isPress()) {
    patchNum++;
    if (patchNum > 127) patchNum = 0;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn2.isHold()) {
    patchNum += 1;
    if (patchNum > 127) patchNum = 0;
    loadPatch();
    displayStatus(2);
  }
  else if (tbtn3.isClick()) { // load patch from EEPROM
    loadPatch();
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
  else if (tbtn4.isPress()) { // save patch to EEPROM
    savePatch();
    displayText(11);
    delay(1000);
    displayStatus(1);
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

void changeParam(int pNum, int pDir) { // inputs are parameter number and direction of change (0/down, 1/up)
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
  switch (pDir) {
    case 0:
      paramValue[pNum]--;
      break;
    case 1:
      paramValue[pNum]++;
      break;
  }

  paramValue[pNum] = checkValue(paramNum[pNum], paramValue[pNum]); // verify parameter value is valid
  setParam(paramNum[pNum], paramValue[pNum]);
  displayText(((pNum + 1) * 2) + 1); // update displayed value
}

/* Display Text */

void displayStatus(int i) {
  switch (i) {
    case 0:
      display.clearDisplay();
    case 1:
      for (int i = 0; i < 4; i++) {
        paramValue[i] = getParam(paramNum[i]);
      }
      for (int i = 0; i < 10; i++) {
        displayText(i);
      }
      break;
    case 2:
      for (int i = 0; i < 4; i++) {
        paramValue[i] = getParam(paramNum[i]);
      }
      for (int i = 1; i < 10; i += 2) {
        displayText(i);
      }
      break;
  }
}

void displayText(int textnum) { // display text in individual pieces to allow for quickly rewriting a section
  switch (textnum) {
    case 0: // patch heading, centre of screen
      display.setCursor(20, 30);
      display.print("               ");
      display.setCursor(35, 30);
      display.println(F("Patch"));
      break;
    case 1: // patch number
      display.setCursor(70, 30);
      display.println("   ");
      display.setCursor(70, 30);
      display.println(patchNum);
      break;
    case 2: // encoder 1 title, top left
      display.setCursor(2, 0);
      display.println("    ");
      display.setCursor(2, 0);
      if (paramFlag[0]) display.print(".");
      display.print(paramNum[0]);
      break;
    case 3: // encoder 1 value
      display.setCursor(2, 12);
      display.println("    ");
      display.setCursor(2, 12);
      display.println(paramValue[0]);
      break;
    case 4: // encoder 2 title, top right
      display.setCursor(100, 0);
      display.println("    ");
      display.setCursor(100, 0);
      if (paramFlag[1]) display.print(".");
      display.print(paramNum[1]);
      break;
    case 5: // encoder 2 value
      display.setCursor(100, 12);
      display.println("    ");
      display.setCursor(100, 12);
      display.println(paramValue[1]);
      break;
    case 6: // encoder 3 title, bottom left
      display.setCursor(2, 43);
      display.println("    ");
      display.setCursor(2, 43);
      if (paramFlag[2]) display.print(".");
      display.print(paramNum[2]);
      break;
    case 7: // encoder 3 value
      display.setCursor(2, 55);
      display.println("    ");
      display.setCursor(2, 55);
      display.println(paramValue[2]);
      break;
    case 8: // encoder 4 title, bottom right
      display.setCursor(100, 43);
      display.println("    ");
      display.setCursor(100, 43);
      if (paramFlag[3]) display.print(".");
      display.print(paramNum[3]);
      break;
    case 9: // encoder 4 value
      display.setCursor(100, 55);
      display.println("    ");
      display.setCursor(100, 55);
      display.println(paramValue[3]);
      break;
    case 10: // patch loaded
      display.setCursor(35, 30);
      display.print("               ");
      display.setCursor(20, 30);
      display.println("Patch Loaded");
      break;
    case 11: // patch saved
      display.setCursor(35, 30);
      display.print("               ");
      display.setCursor(20, 30);
      display.println("Patch Saved");
      break;
    case 12: // init patch
      display.setCursor(35, 30);
      display.print("               ");
      display.setCursor(25, 30);
      display.println("Patch Init");
  }
  display.display();
}

/* XVA1 Interaction */

int getParam(int pNum) { // input parameter number
  Serial1.write('g'); // send g + param number to request value
  if (pNum < 254) Serial1.write(pNum);
  else {
    Serial1.write(255);
    Serial1.write(pNum - 256);
  }
  while (!Serial1.available()); // wait for return
  return Serial1.read(); // return value provided by XVA1
}

void setParam(int pNum, int pVal) { // input parameter number and value to set
  Serial1.write('s'); // send g + param number to request value
  if (pNum < 254) Serial1.write(pNum);
  else {
    Serial1.write(255);
    Serial1.write(pNum - 256);
  }
  Serial1.write(pVal);
  delay(10);
}

void loadPatch() { // load patch from EEPROM
  Serial1.write('r');
  Serial1.write(patchNum);
  while (!Serial1.available()); //wait for it
  if (Serial1.read() == 0) Serial.println("Patch loaded");
}

void savePatch() { // save current patch to EEPROM
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

/* Parameter Checking */

int checkParam(int pNum) { // take parameter number as input, return valid parameter number as output
  if (pNum < 1) pNum = 511;
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
    case 27 ... 38: // level, level l, level r
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

/* USB MIDI response */

void midiProgramChange (byte channel, byte program) { // respond to PC messages over USB MIDI
  patchNum = program;
  if (patchNum < 0) patchNum = 127;
  if (patchNum > 127) patchNum = 0;
  loadPatch();
  displayStatus(2);
}
