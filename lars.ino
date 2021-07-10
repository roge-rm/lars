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
int paramNum = 1;
int paramValue = 0;

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

  enc1.counter = 100; // change counter
  enc2.counter = 100;
  enc3.counter = 100;
  enc4.counter = 100;

  getParam();
  displayStatus();
}

void loop() {
  encUpdate(); // update encoders and buttons

  if (enc1.isLeft()) {
    patchNum--;
    if (patchNum < 0) patchNum = 127;
    loadPatch();
    updateText(0);
  }
  else if (enc1.isRight()) {
    patchNum++;
    if (patchNum > 127) patchNum = 0;
    loadPatch();
    updateText(0);
  }

  if (enc3.isLeft()) {
    paramNum--;
    checkParam();
    getParam();
    updateText(1);
  }
  else if (enc3.isRight()) {
    paramNum++;
    checkParam();
    getParam();
    updateText(1);
  }
  else if (enc3.isClick()) {
    paramNum = 1;
    getParam();
    updateText(1);
  }

  if (enc4.isLeft()) {
    paramValue--;
    checkValue();
    setParam();
    updateText(1);
  }
  else if (enc4.isRight()) {
    paramValue++;
    checkValue();
    setParam();
    updateText(1);
  }
}

void displayStatus() {
  display.clearDisplay();
  display.setCursor(5, 10);
  display.println(F("Patch"));
  display.setCursor(70, 10);
  display.println(patchNum);

  display.setCursor(5, 30);
  display.println(F("Param num"));
  display.setCursor(70, 30);
  display.println(paramNum);
  display.setCursor(70, 40);
  display.println(paramValue);
  display.display();
}

void updateText(int textnum) {
  switch (textnum) {
    case 0:
      display.setCursor(70, 10);
      display.println("   ");
      display.setCursor(70, 10);
      display.println(patchNum);
      break;
    case 1:
      display.setCursor(70, 30);
      display.println("   ");
      display.setCursor(70, 30);
      display.println(paramNum);
      display.setCursor(70, 40);
      display.println("   ");
      display.setCursor(70, 40);
      display.println(paramValue);
      break;
  }
  display.display();
}

void encUpdate() {
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

void getParam() {
  Serial1.write('g'); // send g + param number to request value
  if (paramNum < 254) Serial1.write(paramNum);
  else {
    Serial1.write(255);
    Serial1.write(paramNum - 256);
  }
  while (!Serial1.available()); // wait for return
  paramValue =  Serial1.read();
}

void setParam() {
  Serial1.write('s'); // send g + param number to request value
  if (paramNum < 254) Serial1.write(paramNum);
  else {
    Serial1.write(255);
    Serial1.write(paramNum - 256);
  }
  Serial1.write(paramValue);
  delay(10);
}

void loadPatch() {
  Serial1.write('r');
  Serial1.write(patchNum);
  while (!Serial1.available()); //wait for it
  Serial.println(Serial1.read());
}

void savePatch() {
  Serial1.write('w');
  Serial1.write(patchNum);
  while (!Serial1.available()); //wait for it
  Serial.println(Serial1.read());
}

void checkParam() { // constrain param choice to known possible params
  if (paramNum < 1) paramNum = 511;
  else if ((paramNum > 251) && (paramNum < 258)) paramNum = 260;
  else if ((paramNum < 260) && (paramNum > 253)) paramNum = 251;
  else if ((paramNum > 397) && (paramNum < 399)) paramNum = 400;
  else if ((paramNum < 400) && (paramNum > 398)) paramNum = 397;
  else if ((paramNum > 415) && (paramNum < 426)) paramNum = 428;
  else if ((paramNum < 428) && (paramNum > 417)) paramNum = 415;
  else if ((paramNum > 454) && (paramNum < 506)) paramNum = 508;
  else if ((paramNum < 508) && (paramNum > 456)) paramNum = 454;
    else if (paramNum > 511) paramNum = 1;
}

void checkValue() { // constrain all params to known possible values
  switch (paramNum) {
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
      if (paramValue < 0) paramValue = 1;
      else if (paramValue > 1) paramValue = 0;
      break;

    // 0-2
    case 245: // porta mode
    case 302: //fx delay mode
    case 312: // fx phaser mode
    case 508: // fx routing mode
      if (paramValue < 0) paramValue = 2;
      else if (paramValue > 2) paramValue = 0;
      break;

    // 0-3
    case 7 ... 10: // phase
    case 162: // LFO1 sync
    case 172: // LFO2 sync
    case 354: // fx distortion type
    case 362: // fx chorus/flanger mode
    case 510 ... 511: // gain pre/post fx
      if (paramValue < 0) paramValue = 3;
      else if (paramValue > 3) paramValue = 0;
      break;

    // 0-5
    case 450: // arp mode
      if (paramValue < 0) paramValue = 5;
      else if (paramValue > 5) paramValue = 0;
      break;

    // 0-7
    case 13 ... 14: // waveforms osc 3 & 4
    case 275: // drive
    case 291: // fx delay smear
    case 340: // fx bandwidth
    case 353: // fx distortion filter post
      if (paramValue < 0) paramValue = 7;
      else if (paramValue > 7) paramValue = 0;
      break;

    // 0-9
    case 11 ... 12: // waveforms osc 1 & 2
    case 160: // LFO1 waveform
    case 170: // LFO2 waveform
      if (paramValue < 0) paramValue = 9;
      else if (paramValue > 9) paramValue = 0;
      break;

    // 1-10
    case 308 ... 309: // fx delay tempo multiplier/divider
    case 432: // seq tempo multiplier
    case 453 ... 454: // arp tempo multiplier & number of octaves
      if (paramValue < 1) paramValue = 10;
      else if (paramValue > 10) paramValue = 1;
      break;

    // 4-12
    case 317: // fx phaser stages
      if (paramValue < 4) paramValue = 12;
      else if (paramValue > 12) paramValue = 4;
      break;

    // 0-15
    case 5 ... 6: // sync & mode
      if (paramValue < 0) paramValue = 15;
      else if (paramValue > 15) paramValue = 0;
      break;

    // 1-16
    case 430: // sync & mode
      if (paramValue < 1) paramValue = 16;
      else if (paramValue > 16) paramValue = 1;
      break;

    // 0-21
    case 71: // filter type
      if (paramValue < 0) paramValue = 21;
      else if (paramValue > 21) paramValue = 0;
      break;

    // 0-24
    case 370: // fx decimator depth
    case 380: // fx bitcrusher depth
      if (paramValue < 0) paramValue = 24;
      else if (paramValue > 24) paramValue = 0;
      break;

    // 0-31
    case 296: // fx early reflections room
      if (paramValue < 0) paramValue = 31;
      else if (paramValue > 31) paramValue = 0;
      break;

    // 0-32
    case 293: // fx early reflections taps
      if (paramValue < 0) paramValue = 32;
      else if (paramValue > 32) paramValue = 0;
      break;

    // 0-3, 65-67
    case 145 ... 147: // eg loop, eg loop seg, eg restart
      if (paramValue < 0) paramValue = 67;
      else if ((paramValue > 3) && (paramValue < 63)) paramValue = 65;
      else if ((paramValue < 65) && (paramValue > 5)) paramValue = 3;
      else if (paramValue > 67) paramValue = 0;
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
      if (paramValue < 0) paramValue = 100;
      else if (paramValue > 100) paramValue = 0;
      break;

    // 0-127
    case 43 ... 46: // keyboard breakpoint
      if (paramValue < 0) paramValue = 127;
      else if (paramValue > 127) paramValue = 0;
      break;

    // 0,50-255
    case 307: // fx delay tempo
    case 431: // seq tempo
    case 451: // arp tempo
      if (paramValue < 0) paramValue = 255;
      else if ((paramValue > 0) && (paramValue < 48)) paramValue = 50;
      else if ((paramValue < 50) && (paramValue > 1)) paramValue = 0;
      else if (paramValue > 255) paramValue = 0;
      break;

    // 0-127,200-201,255
    case 434 ... 449: // seq step1 through step16
      if (paramValue < 0) paramValue = 255;
      else if ((paramValue > 127) && (paramValue < 198)) paramValue = 200;
      else if ((paramValue < 200) && (paramValue > 128)) paramValue = 127;
      else if ((paramValue > 201) && (paramValue < 254)) paramValue = 255;
      else if ((paramValue < 255) && (paramValue > 202)) paramValue = 201;
      else if (paramValue > 255) paramValue = 0;
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
      if (paramValue < 0) paramValue = 255;
      else if (paramValue > 255) paramValue = 0;
      break;
  }
}
