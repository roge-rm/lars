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
int paramValue[4] = {1, 2, 3, 4};
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
      if (presetNum[1] > 10) presetNum[1] = 0;
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
