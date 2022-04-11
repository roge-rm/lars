# lars
##### a small but powerful controller for the XVA1 synthesizer

<img src=https://raw.githubusercontent.com/hunked/lars/main/images/07.jpg width=800>

I came across the <a href=https://www.futur3soundz.com/>XVA1 FPGA Synthesizer</a> recently and decided to have a go at creating a control interface with parts I had sitting around. 
This is the result of that process, though it is still a work in progress.

<img src=https://raw.githubusercontent.com/hunked/lars/main/images/01.jpg width=300> <img src=https://raw.githubusercontent.com/hunked/lars/main/images/02.jpg width=300>

My goal is to make a controller that allows me to edit all of the parameters on the XVA1 without having to hook it up to a computer. So far most parameters on the XVA1 are editable from the controller itself, except the sequencer and MIDI performance controls, in a menu system accessible through the fourteen buttons. 
Figuring out how to make a menu system to go with the board layout I've chosen has been ..interesting.. and is progressing now that a 3D printed housing has been added.

The brains of the operation is a Teensy 2.0++ connected to four clickable encoders and fourteen buttons. The encoders and four buttons are arranged around a 0.96" OLED screen and used for editing up to four values at once. The rest of the buttons are arranged to the right - the bottom six switch between six different submenus (oscillators, filters, modulation, envelope generators, effects, and arp/general settings) while the top four perform functions such as changing, loading, and saving patches and accessing additional settings. Communication with the XVA1 is done over a serial connection and MIDI data goes straight into the XVA1 itself through the port on the back.

<img src=https://raw.githubusercontent.com/hunked/lars/main/images/04.jpg width=300> <img src=https://raw.githubusercontent.com/hunked/lars/main/images/05.jpg width=300>

One of the more interesting challenges has been the 7 segment envelope generator. Thanks to some helpful tips from a user on the r/Synthesizers discord I have developed a graphical interface to display and edit the three EGs. I could not wrap my head around the values individually but seeing them laid out graphically makes it much easier to tweak in a way I can understand.

<img src=https://raw.githubusercontent.com/hunked/lars/main/images/06.jpg width=300> <img src=https://raw.githubusercontent.com/hunked/lars/main/images/08.jpg width=300>

I am not posting any of this in expectation that anyone will copy me - the code is a work in progress as I hack together ideas and clean things up. But if you are trying to make a controller for your XVA1 perhaps some of this could be of use to you!

Take care!
rm
