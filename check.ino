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
    case 148 ... 149: // pitch range && velocity
    case 164 ... 165: // LFO1 depth pitch && amp
    case 166: // LFO1 range
    case 174 ... 175: // LFO2 depth PW and cutoff
    case 176: // LFO2 range
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

    // 0-255 no loop
    case 80 ... 107: // eg segment SADSRR levels
    case 115 ... 137: // eg segment ADSRR levels
    case 110 ... 112: // eg delay
      if (pVal < 0) pVal = 0;
      else if (pVal > 255) pVal = 255;
      break;


    // 0-255
    case 15 ... 18: // pulse width
    case 19 ... 22: // transpose
    case 23 ... 26: // tune
    case 27 ... 38: // level, level l, level r
    case 63 ... 70: // PMS & AMS
    case 72 ... 79: // cutoff, resonance, velocity, kbd track, eg depth, eg velocity
    case 161: // LFO1 speed
    case 171: // LFO2 speed
    case 163: // LFO1 fade
    case 173: // LFO2 fade
    case 180 ... 195: // pitch, amp, cutoff, PW LFO midi modulation
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

int checkModify() { // check if current patch has been modified and prompt to continue
  if (patchModify) {
    bool cont = false;
    display.clearDisplay();
    display.setCursor(20, 30);
    display.print("PATCH MODIFIED");
    display.setCursor(35, 40);
    display.print("CONTINUE? ");
    display.display();
    while (!cont) {
      encUpdate();
      if (tbtn1.isClick() || tbtn2.isClick() || tbtn3.isClick() || tbtn4.isClick() || enc1.isClick() || enc2.isClick() || enc3.isClick() || enc4.isClick()) { // click any top button or encoder to continue
        cont = true;
        return 1;
      }
      else if (sbtn1.isClick() || sbtn2.isClick() || sbtn3.isClick() || sbtn4.isClick() || bbtn1.isClick() || bbtn2.isClick() || bbtn3.isClick() || bbtn4.isClick() || bbtn5.isClick() || bbtn6.isClick() || enc1.isLeft() || enc2.isLeft() || enc3.isLeft() || enc4.isLeft() || enc1.isRight() || enc2.isRight() || enc3.isRight() || enc4.isRight()) { // press any bottom button or turn any encoder to cancel
        cont = true;
        display.clearDisplay();
        return 0;
      }
    }
  }
  else return 1;
}
