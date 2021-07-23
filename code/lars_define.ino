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
