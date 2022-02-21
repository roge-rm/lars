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
int midiPort = 0; // what MIDI channel the XVA1 will respond to (default is 0/omni)

int presetType = 0; // 0-Oscillators,1-Filters,2-Modulation,3-Effects,4-Global Param,5-MIDI Modulation
int presetNum[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // see spreadsheet for breakdown

bool doPreset = 0; // indicate preset change needed
bool doEG = 0; // enable graphic mode

bool bitEdit = 0; // editing bitwise values is handled differently
int bitNum = 0; // track which bitwiser number is being edited - see spreadsheet
int bitLocation[4] = {0, 1, 2, 3};
bool bitValues[5][8];

bool editEG[4] = {0, 0, 0, 0}; // used to toggle encoders between ADSR edit modes
bool levelEG = false; // edit EG level or time
bool stateChange = 1; // used to confirm display clear to prevent flickering/excess time on redrawing display
float egDLY, egL0, egL1, egL2, egL3, egL4, egL5, egR1, egR2, egR3, egR4, egR5;
int eg0x, eg0y, eg1x, eg1y, eg2x, eg2y, eg3x, eg3y, eg4x, eg4y, eg5x, eg5y, eg6x, eg6y;

// store menu headings in char arrays
char menu0Names[22][13] = {"OSC ON/OFF", " WAVEFORM", "PULSE WIDTH", "SAWSTACK DET", "   SYNC", "   PHASE", "   MODE", " TRANSPOSE", "  DETUNE", "  DRIFT", "  LEVEL", " LEVEL L", " LEVEL R", " VELO SENS", "  KEY BP", "KEY LDEPTH", "KEY RDEPTH", "KEY LCURVE", "KEY RCURVE", " PM SENS", " AM SENS", " RING MOD"};
char menu1Names[4][13] = {"  FILTER", "CUTOFF/RESO", "TRACK/RESO", " ENV GEN"};
char menu2Names[13][13] = {"LFO1 MOD1", "LFO1 MOD2", "LFO2 MOD1", "LFO2 MOD2", "LFO AFTER", "LFO WHEEL", "LFO BREATH", "LFO FOOT", "MIDI AFTER", "MIDI BREATH", "MIDI RND/WHL", "MIDI FOOT", "MIDI TEMP"};
char menu3Names[7][13] = {"", "", "", " EG LOOP", "EG LOOP SEG", "EG RESTART", "  PITCH"};
char menu4Names[19][15] = {"BW & ROUTING", "  DISTORT", "DISTORT GAIN", "CRUSH/DECIM", "FILTER CUTOFF", "CHORUS/FLANGER", "CHORUS/FLANGER", " PHASER 1", " PHASER 2", "  AMP MOD", "  DELAY 1", "  DELAY 2", "  DELAY 3", "  DELAY 4", " EAREFLECT", " EAREFLECT", " REVERB 1", " REVERB 2", "   GATE"};
char menu5Names[6][13] = {"  GLOBAL", "PORTMENTO", "PAN & VOLUME", " OFFSET TUNE", "    ARP", "  OUTPUT"};
char menu11Names[4][8] = {"OSC1 1", "OSC1 2", "OSC1 3", "OSC1 4"};
char menu12Names[4][8] = {"OSC2 1", "OSC2 2", "OSC2 3", "OSC2 4"};
char menu13Names[4][8] = {"OSC3 1", "OSC3 2", "OSC3 3", "OSC3 4"};
char menu14Names[4][8] = {"OSC4 1", "OSC4 2", "OSC4 3", "OSC4 4"};

// store parameter names in char arrays
char paramName0[4][5] = {"OSC1", "OSC2", "OSC3", "OSC4"};
char paramName1_1[4][5] = {"TYPE",  "CUT1", "VELT", "DPTH"};
char paramName1_2[4][5] = {"",      "CUT2", "KEYT",   "VELO"};
char paramName1_3[4][5] = {"DRV",   "RES1", "VELR", ""};
char paramName1_4[4][5] = {"ROUT",  "RES2", "KEYR", ""};
char paramName2_1[13][5] = {"WAVE", "FADE", "WAVE", "FADE", "PIT",  "PIT",  "PIT",  "PIT",  "PIT",  "PIT",  "PIT",  "PIT",  "PIT"};
char paramName2_2[13][5] = {"RNG",  "DPIT", "RNG",  "DPW",  "PW",   "PW",   "PW",   "PW",   "PW",   "PW",   "PW",   "PW",   "PW"};
char paramName2_3[13][5] = {"SPD",  "DAMP", "SPD",  "DCUT", "FILT", "FILT", "FILT", "FILT", "CUT",  "CUT",  "CUT",  "CUT",  "CUT"};
char paramName2_4[13][5] = {"SYNC", "",     "SYNC", "",     "AMP",  "AMP",  "AMP",  "AMP",  "VOL",  "VOL",  "VOL",  "VOL",  "VOL"};
char paramName3_1[7][5] = {"", "", "", "AMP", "AMP", "AMP", "RANG"};
char paramName3_2[7][5] = {"", "", "", "FLT", "FLT", "FLT", "VELO"};
char paramName3_3[7][5] = {"", "", "", "PIT", "PIT", "PIT", ""};
char paramName3_4[7][5] = {"", "", "", "", "", "", ""};
char paramName4_1[19][5] = {"BW",   "ON", "PRE",  "BIT",  "LO", "DRY",  "SPD",  "DRY",  "SPD",  "SPD",  "DRY",  "FEED", "MUL",  "SMEA", "DRY",  "TAPS", "DRY",  "DAMP", "GATE"};
char paramName4_2[19][5] = {"ROUT", "TYPE",   "POST", "DEC",  "HI", "WET",  "DPTH", "WET",  "DPTH", "DPTH", "WET",  "LO",   "DIV",  "2X",   "WET",  "FEED", "WET",  "HPF",  "CURV"};
char paramName4_3[19][5] = {"",     "",       "FILT", "",     "",   "MODE", "FEED", "MODE", "FEED", "RANG", "MODE", "HI",   "SPD",  "",     "ROOM", "",     "MODE", "SPD",  "ATK"};
char paramName4_4[19][5] = {"",     "",       "",     "",     "",   "",     "PHAS", "STAG", "PHAS", "PHAS", "TIME", "TMPO", "DPTH", "",     "",     "",     "DCAY", "DPTH", "REL"};
char paramName5_1[6][5] = {"TRAN",  "MODE", "PAN",  "VOFF",  "MODE", "VOL"};
char paramName5_2[6][5] = {"LEGT",  "TIME", "VOL",  "TUNE", "TEMP", "PRE"};
char paramName5_3[6][5] = {"B UP",  "",     "",     "TOFF", "MUL",  ""};
char paramName5_4[6][5] = {"B DN",  "",     "",     "",     "OCT",  "POST"};
char paramName6_1[4][5] = {"OSC",   "TRAN", "LVL",  "PMS"};
char paramName6_2[4][5] = {"PHAS", "DRFT", "VSEN", "AMS"};
char paramName6_3[4][5] = {"WAVE", "TUNE", "LVLL", "RING"};
char paramName6_4[4][5] = {"PW",   "SAW",  "LVLR", ""};

// store parameter value names in char arrays
char valueName0[2][5] = {"OFF", "ON"};
char valueName1[10][5] = {"SAWD", "SAWU", "PULS", "TRI", "SINE", "NOIS", "SW3M", "SW3S", "SW7M", "SW7S"}; // osc waveforms
char valueName2[4][4] = {"0", "90", "180", "270"}; // osc phase
char valueName3[22][5] = {"NONE", "1P L", "2P L", "3P L", "4P L", "1P H", "2P H", "3P H", "4P H", "2P B", "4P B", "2PBR", "4PBR", "2PLL", "2PLB", "2PLH", "P2xL", "P LB", "P LH", "P BB", "P BH", "P HH"}; // filter types
char valueName4[10][5] = {"TRI", "SQR", "SAWU", "SAWD", "SINE", "S+2S", "S+3S", "SIN3", "GUIT", "RAND"}; // lfo wave
char valueName5[4][5] = {"SINF", "SINK", "MULF", "MINK"}; // lfo  sync behavior
char valueName6[2][5] = {"POLY", "MONO"}; // legato
char valueName7[3][5] = {"OFF", "YES", "FING"}; // porta mode
char valueName8[6][5] = {"OFF", "UP", "DOWN", "UPDN", "PLAY", "RAND"}; // arp mode
char valueName9[8][5] = {"FULL", "20 k", "18 k", "16 k", "14 k", "12 k", "10 k", "8 k"}; // bandwidth/filter post
char valueName10[2][5] = {"PAR", "IND"}; // routing
char valueName11[4][5] = {"HARD", "SOFT", "12AX", "DSL"}; // distortion type
char valueName12[4][5] = {"CLON", "CSHO", "FLON", "FSHO"}; // chorus/flanger mode
char valueName13[3][5] = {"MONO", "STR", "CROS"}; // phaser mode
char valueName14[3][5] = {"MONO", "CROS", "BOUN"}; // delay mode
char valueName15[8][5] = {"NONE", "16 b", "15 b", "14 b", "13 b", "12 b", "11 b", "10 b"}; // smear
char valueName16[2][5] = {"PLAT", "HALL"}; // reverb mode
char valueName17[2][5] = {"SS 1", "SS 2"}; // gate volume ramp curve
char valueName18[3][5] = {"CHOR", "GATE", "NONE"}; // effects routing
char valueName19[4][5] = {"0 dB", "6 dB", "12dB", "18dB"}; // gain pre/post


void setup() {
  // screen initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Address 0x3C for 128x64
    for (;;); //Don't proceed, loop forever
  }
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();

  //  Serial.begin(9600); // for monitoring purposes
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

  doEncButtons(); // encoder/button press handling
  doTopButtons(); // top row button handling
  doBotButtons(); // bottom row button handling
  doScrButtons(); // handle buttons around screen (not encoders)

  if (doPreset) changePreset();
  if (doEG) displayADSR();

  usbMIDI.read(midiChan);
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

// defaults

void loadDefaults() {
  levelEG = true;

  for (int i = 0; i < 4; i++) {
    editEG[i] = 0;
  }
}
