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
