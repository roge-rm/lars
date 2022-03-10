# lars
##### a small but powerful controller for the XVA1 synthesizer

<img src=https://raw.githubusercontent.com/hunked/lars/main/images/lars_01.jpg width=800>

I came across the <a href=https://www.futur3soundz.com/>XVA1 FPGA Synthesizer</a> recently and decided to have a go at creating a control interface with parts I had sitting around. This monstrosity is the result of that proces and I felt like sharing it even though it is clearly a work in progress.

My goal is to make a controller that allows me to edit all of the parameters on the XVA1 without having to hook it up to a computer. Ideally the control surface would be larger, there would be more screens and buttons and knobs and maybe sliders? But that's somewhere down the road. In the meantime I have used only parts that were already in my parts bins (check out how I joined two perfboards together and judge me as you will) to create something functional (if not optimal).

The brains of the operation is a Teensy 2.0++. I have a few sitting around, they have lots of IO pins, and maybe it's not the fastest board out there but it was already here. I added four button encoders, fourteen lil buttons, and one tiny OLED screen and called it a day. Communication with the XVA1 is done via UART and they even share a power bus so I don't have to plug more things in.

The software functionality is coming along, most values are editable using a number of submenus (I hope you are good at diving) accessed via the six lower buttons below the Teensy. Most screens allow for editing of four variables at a time (laid out somewhat thoughtfully but due for revision at some point) and I've spent a fair bit of time working on a graphical editor for the 7 segment ADSR envelope generator. I'd say that the UI is at a point where the XVA1 is usable as a synthesizer, further development on that front is on hold while I work on a nicer looking enclosure.

I am posting this to github in case anyone else out there is trying to make an XVA1 controller - hopefully my code and ideas can be helpful to you.

Cheers, check out my other projects if you like what you see here.
