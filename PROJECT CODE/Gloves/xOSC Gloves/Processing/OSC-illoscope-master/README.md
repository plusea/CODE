OSC-illoscope
=============

OSC-illoscope is a simple example to show how to interface to [x-OSC](http://www.x-io.co.uk/x-osc/) using [Processing](http://www.processing.org/).  The sketch plots received analogue input values on up to 16 graphs in real-time.  This application is a handy development tool for viewing the data provided by analogue sensors and peripherals.  The [demo video](http://www.youtube.com/watch?v=yi7a4-hhDFQ) shows OSC-illoscope being used to plot data from a [membrane potentiometer](https://www.sparkfun.com/products/8680), light sensor, [triple-axis accelerometer]( https://www.sparkfun.com/products/9269), [piezo transducer](https://www.sparkfun.com/products/10293), [IR distance sensor]( https://www.sparkfun.com/products/242), and a data glove incorporating 8 [flex sensors](https://www.sparkfun.com/products/10264).

The Processing sketch requires the [oscP5 library](http://www.sojamo.de/libraries/oscP5/) to send and receive OSC messages.  To use this library, copy the entire *oscP5* directory (.zip available in the repository) into a directory named *"libraries"* in Processing Sketchbook location (see: *File* > *Preferences* > *Sketchbook location*).  A tutorial for sending and receiving OSC messages in Processing is available on the [codasign](http://learning.codasign.com/index.php?title=Sending_and_Receiving_OSC_Data_Using_Processing) website.

<div align="center">
<img src="https://raw.github.com/xioTechnologies/OSC-illoscope/master/OSC-illoscope%20With%20Triple-Axis%20Accelerometer.png"/>
</div>

For more information see the [original post](http://www.x-io.co.uk/osc-illoscope/).

**Windows 7 Firewall:**  When running the processing application for the first time you will be prompted to grant network access to Java by Windows Firewall.  Java must be given access "Public" access else network communication will not be possible.  These permission can be modified any time through *Control Panel* > *Windows Firewall* > *"Change settings"*.
