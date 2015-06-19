Pixelgroup
==========

Pixelgroup is a library to group pixels in a LED-strip. It is intended to be used in the Arduino framework together with a pixel-strip library like Adafruit_NeoPixel or Adafruit_WS2801 but can be used for any kind of backend. The PixelWriter class can be used to write into a uint8_t array. The PixelWriterInterface can be used to subclass existing pixelstrip writers or to build your own writer.

Pixelgroups are limited to 255 pixels.


4 Pixelgroup classes:
--

PixelgroupBase:
- basic pixelgroup
- can set color
- If you just need to set a color in groups, use this

PixelgroupEaser:
- based on PixelgroupBase
- can do colorfades

PixelgroupStrobe:
- based on PixelgroupBase
- can strobe

Pixelgroup:
- based on PixelgroupBase
- can do colorfades
- can strobe
- can flicker
