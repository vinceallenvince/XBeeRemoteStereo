# XBeeRemoteStereo

This repo contains code to send audio data from a wireless microphone to a web browser. There are three components involved.

* [Arduino code](https://github.com/vinceallenvince/XBeeRemoteStereo/tree/master/Arduino)
* [a NodeJS app](https://github.com/vinceallenvince/XBeeRemoteStereo)
* [JS and HTML for the browser](https://github.com/vinceallenvince/XBeeRemoteStereo/tree/master/public)

The Arduino code analyzes the microphone signal and looks for a specific frequency. It writes the magnitude of the frequency to the serial port which is sent wireless via XBee radios. The NodeJS app uses the [node-serialport](https://github.com/voodootikigod/node-serialport) node module to read the base XBee radio and forwards the data to the browser via [web sockets](http://socket.io).

You can also find [cutting plans](https://github.com/vinceallenvince/XBeeRemoteStereo/tree/master/enclosure) to laser cut the enclosure.

![XBeeRemoteStereo](https://raw.githubusercontent.com/vinceallenvince/XBeeRemoteStereo/master/images/xbeemic.jpg)

#### Hardware

4 X Threaded F-F Nylon Standoff M3 x 10mm; item #: 30357-02 Inventables.com; $2.50
https://www.inventables.com/technologies/standoff-threaded-nylon

8 X Threaded F-F Nylon Standoff M3 x 6mm; item #: 30357-01 Inventables.com; $2.50
https://www.inventables.com/technologies/standoff-threaded-nylon

4 X Socket Head Cap Screw Thread Size: M5, Length: 40mm, Pitch: 0.8mm; item #: 25285-06 Inventables; $2.91
https://www.inventables.com/technologies/socket-head-cap-screw

1 X Transparent Dark Bronze Acrylic Sheet; item #: 24137-03; Inventables.com $5.10
https://www.inventables.com/technologies/transparent-dark-bronze-acrylic-sheet--2

1 X Transparent Grey Acrylic Sheet; item #: 24136-03; Inventables.com $5.10
https://www.inventables.com/technologies/transparent-dark-bronze-acrylic-sheet--2

4 X Machine screw S/S RPH MS 4-40 X 5/8; item #: 72487 Fastenal.com; $0.28
http://www.fastenal.com/web/products/details/72487

2 X Machine screw 2-56 X 1/4"; item #: 72456 Fastenal.com; $0.28
http://www.fastenal.com/web/products/details/72456

2 X Small Pattern Hex Nut 2-56; item #: 0173911 Fastenal.com; $0.07
https://www.fastenal.com/web/products/details/0173911

8 X Machine Screw: #4-40, 1/2" Length, Phillips (25-pack); item #: 1962 Pololu.com; $0.99
http://www.pololu.com/product/1962

8 X Machine Hex Nut: #4-40 (25-pack); item #: 1962 Pololu.com; $0.99
http://www.pololu.com/product/1068

1 X Perma-Proto Small Mint Tin Size Breadboard PCB; item #: 1214; Adafruit.com; $7.95
http://www.adafruit.com/products/1214

1 X Electret Microphone Amplifier - MAX4466 with Adjustable Gain; item #: 1063; Adafruit.com; $6.95
http://www.adafruit.com/product/1063

1 X XBee Shield; item #: WRL-10854; Sparkfun.com; $24.95
https://www.sparkfun.com/products/10854

1 X XBee Pro 60mW Wire Antenna - Series 1 (802.15.4); item #: WRL-08742; Sparkfun.com; $37.95
https://www.sparkfun.com/products/8742

1 X Arduino Uno - R3; item #: DEV-11021; Sparkfun.com; $29.95
https://www.sparkfun.com/products/11021

4 X 3D Printed 29mm spacers

