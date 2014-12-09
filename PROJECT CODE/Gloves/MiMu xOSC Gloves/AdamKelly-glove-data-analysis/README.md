Gloves Data Analysis
=====================

This repository contains code for logging and analysing glove posture data.


Logging Data With Processing
----------------------------

The Processing sketch 'GloveLogging' receives glove data by OSC and logs sensor data of the right glove to a text file when the space bar is pressed. You will need to update the text file name and be sure to press 's' at the end of logging to save the data to the text file.

Exploring Datasets
------------------

Currently, datasets are stored in text files (with one posture per line stored as comma separated values) and as Python pickles (binary collections of Python dictionaries which hold arrays containing the data).

Existing datasets are...

* 18th April 2013 - Adam Stark - Right Hand - 7 Postures - 25 of each
* 18th April 2013 - Kelly Snook - Right Hand - 7 Postures - 25 of each