
 // Atmega table-based digital oscillator
// using "DDS" with 32-bit phase register to illustrate efficient
// accurate frequency.
// 20-bits is on the edge of people pitch perception
// 24-bits has been the usual resolution employed.
// so we use 32-bits in C, i.e. long.
//
// smoothly interpolates frequency and amplitudes illustrating
// lock-free approach to synchronizing foreground process  control and background (interrupt)
// sound synthesis
// copyright 2009. Adrian Freed. All Rights Reserved.
// Use this as you will but include attribution in derivative works.
// tested on the Arduino Mega
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
const unsigned int LUTsize = 1<<8; // Look Up Table size: has to be power of 2 so that the modulo LUTsize
                                   // can be done by picking bits from the phase avoiding arithmetic
int8_t sintable[LUTsize] PROGMEM = { // already biased with +127
  127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,
  176,179,182,184,187,190,193,195,198,200,203,205,208,210,213,215,
  217,219,221,224,226,228,229,231,233,235,236,238,239,241,242,244,
  245,246,247,248,249,250,251,251,252,253,253,254,254,254,254,254,
  255,254,254,254,254,254,253,253,252,251,251,250,249,248,247,246,
  245,244,242,241,239,238,236,235,233,231,229,228,226,224,221,219,
  217,215,213,210,208,205,203,200,198,195,193,190,187,184,182,179,
  176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,
  127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,
  78,75,72,70,67,64,61,59,56,54,51,49,46,44,41,39,
  37,35,33,30,28,26,25,23,21,19,18,16,15,13,12,10,
  9,8,7,6,5,4,3,3,2,1,1,0,0,0,0,0,
  0,0,0,0,0,0,1,1,2,3,3,4,5,6,7,8,
  9,10,12,13,15,16,18,19,21,23,25,26,28,30,33,35,
  37,39,41,44,46,49,51,54,56,59,61,64,67,70,72,75,
  78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124};

int8_t triangletable[LUTsize] PROGMEM = {
  0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,
  0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,
  0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,
  0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,
  0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,
  0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,
  0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,
  0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,
  0xff,0xfd,0xfb,0xf9,0xf7,0xf5,0xf3,0xf1,0xef,0xed,0xeb,0xe9,0xe7,0xe5,0xe3,0xe1,
  0xdf,0xdd,0xdb,0xd9,0xd7,0xd5,0xd3,0xd1,0xcf,0xcd,0xcb,0xc9,0xc7,0xc5,0xc3,0xc1,
  0xbf,0xbd,0xbb,0xb9,0xb7,0xb5,0xb3,0xb1,0xaf,0xad,0xab,0xa9,0xa7,0xa5,0xa3,0xa1,
  0x9f,0x9d,0x9b,0x99,0x97,0x95,0x93,0x91,0x8f,0x8d,0x8b,0x89,0x87,0x85,0x83,0x81,
  0x7f,0x7d,0x7b,0x79,0x77,0x75,0x73,0x71,0x6f,0x6d,0x6b,0x69,0x67,0x65,0x63,0x61,
  0x5f,0x5d,0x5b,0x59,0x57,0x55,0x53,0x51,0x4f,0x4d,0x4b,0x49,0x47,0x45,0x43,0x41,
  0x3f,0x3d,0x3b,0x39,0x37,0x35,0x33,0x31,0x2f,0x2d,0x2b,0x29,0x27,0x25,0x23,0x21,
  0x1f,0x1d,0x1b,0x19,0x17,0x15,0x13,0x11,0x0f,0x0d,0x0b,0x09,0x07,0x05,0x03,0x01,
};

const int timerPrescale=1<<9;
struct oscillator
{
    uint32_t phase;
    int32_t phase_increment;
    int32_t frequency_increment;
    int16_t amplitude;
    int16_t amplitude_increment;
    uint32_t framecounter;
} o1;
const int fractionalbits = 16; // 16 bits fractional phase
// compute a phase increment from a frequency
unsigned long phaseinc(float frequency_in_Hz)
{
   return LUTsize *(1l<<fractionalbits)* frequency_in_Hz/(F_CPU/timerPrescale);
}
// The above requires floating point and is robust for a wide range of parameters
// If we constrain the parameters and take care we can go much
// faster with integer arithmetic
// We control the calculation order to avoid overflow or resolution loss
 //
 // we chose "predivide" so that (pow(2,predivide) divides F_CPU,so 4MHz (1.7v), 8Mhz, 12Mhz (3.3v) and 16Mhz 20Mhz all work
 // AND note that "frequency_in_Hz" is not too large. We only have about 16Khz bandwidth to play with on
 // Arduino timers anyway
const int predivide = 8;
unsigned long phaseinc_from_fractional_frequency(unsigned long frequency_in_Hz_times_256)
{
    return (1l<<(fractionalbits-predivide))* ((LUTsize*(timerPrescale/(1<<predivide))*frequency_in_Hz_times_256)/(F_CPU/(1<<predivide)));
}
// tabulate phaseincrements correspondending to equaltemperament and midi note numbers (semitones)
#define MIDITOPH
#ifdef MIDITOPH
#define mtoph(x) ( phaseinc(8.1757989156* pow(2.0, x /12.0) ))
unsigned long midinotetophaseinc[128]=
{
  mtoph(0), mtoph(1), mtoph(2),mtoph(3), mtoph(4), mtoph(5), mtoph(6), mtoph(7),
  mtoph(8),mtoph(9), mtoph(10), mtoph(11), mtoph(12), mtoph(13), mtoph(14), mtoph(15),
   mtoph(16), mtoph(17), mtoph(18), mtoph(19), mtoph(20), mtoph(21), mtoph(22), mtoph(23),
  mtoph(24), mtoph(25), mtoph(26), mtoph(27), mtoph(28), mtoph(29), mtoph(30), mtoph(31),
   mtoph(32), mtoph(33), mtoph(34), mtoph(35), mtoph(36), mtoph(37), mtoph(38), mtoph(39),
  mtoph(40), mtoph(41), mtoph(42), mtoph(43), mtoph(44), mtoph(45), mtoph(46), mtoph(47),
   mtoph(48), mtoph(49), mtoph(50), mtoph(51), mtoph(52), mtoph(53), mtoph(54), mtoph(55),
  mtoph(56), mtoph(57), mtoph(58), mtoph(59), mtoph(60), mtoph(61), mtoph(62), mtoph(63),
  mtoph(64), mtoph(65), mtoph(66), mtoph(67), mtoph(68), mtoph(69), mtoph(70), mtoph(71),
  mtoph(72), mtoph(73), mtoph(74), mtoph(75), mtoph(76), mtoph(77), mtoph(78), mtoph(79),
   mtoph(80), mtoph(81), mtoph(82), mtoph(83), mtoph(84), mtoph(85), mtoph(86), mtoph(87),
  mtoph(88), mtoph(89), mtoph(90), mtoph(91), mtoph(92), mtoph(93), mtoph(94), mtoph(95),
   mtoph(96),mtoph(97), mtoph(98), mtoph(99), mtoph(100), mtoph(101), mtoph(102), mtoph(103),
  mtoph(104),mtoph(105), mtoph(106), mtoph(107), mtoph(108), mtoph(109), mtoph(110), mtoph(111),
   mtoph(112),mtoph(113), mtoph(114), mtoph(115), mtoph(116), mtoph(117), mtoph(118), mtoph(119),
  mtoph(120), mtoph(121), mtoph(122), mtoph(123), mtoph(124), mtoph(125), mtoph(126), mtoph(127)
 };
#undef mtoph
#endif
// Timer setup constants
#if defined(__AVR_ATmega8__)
// On old ATmega8 boards, output is on pin 11
#define PWM_PIN       11
#define PWM_VALUE_DESTINATION     OCR2
#define PWM_INTERRUPT TIMER2_OVF_vect

#elif defined(__AVR_ATmega1280__)
#define PWM_PIN       3
#define PWM_VALUE_DESTINATION     OCR3C
#define PWM_INTERRUPT TIMER3_OVF_vect
#else
// For modern ATmega168 boards, output is on pin 3
#define PWM_PIN       3
#define PWM_VALUE_DESTINATION     OCR2B
#define PWM_INTERRUPT TIMER2_OVF_vect
#endif
void initializeTimer() {
 // Set up PWM  with Clock/256 (i.e.  31.25kHz on Arduino 16MHz;
 // and  phase accurate
#if defined(__AVR_ATmega8__)
  // ATmega8 has different registers
  TCCR2 = _BV(WGM20) | _BV(COM21) | _BV(CS20);
  TIMSK = _BV(TOIE2);
#elif defined(__AVR_ATmega1280__)
  TCCR3A = _BV(COM3C1) | _BV(WGM30);
  TCCR3B = _BV(CS30);
  TIMSK3 = _BV(TOIE3);
#else
  TCCR2A = _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS20);
  TIMSK2 = _BV(TOIE2);
#endif
  pinMode(PWM_PIN,OUTPUT);
}
void setup()
{
    o1.phase = 0;
   o1.phase_increment = 0 ;
   o1.amplitude_increment = 0;
   o1.frequency_increment = 0;
   o1.framecounter =0;
     o1.amplitude = 0; // full amplitude
 initializeTimer();
 }
void loop() {
// Examples
  o1.amplitude = 255*256; // full amplitude
  // All the MIDI note numbers
   for(int i=0;i<128;++i)
   {
     o1.phase_increment = midinotetophaseinc[i];
     delay(100);
   }
 delay(1000); 
   // linear frequency steps from fractional frequency
   unsigned long l;
   for(l=100;l<15000;l+=200)
   {
     o1.phase_increment = phaseinc_from_fractional_frequency(l*256);
    delay(200);
   }
 o1.phase_increment = phaseinc(440.0);
  delay(1000);
  o1.phase_increment = phaseinc(220.0);
  delay(1000);
  o1.phase_increment = phaseinc(600.0);
 delay(1000);
   //sweep up
 o1.phase_increment = phaseinc_from_fractional_frequency(100UL*256);
  o1.frequency_increment = phaseinc(0.02);
  o1.framecounter = 200000;
  delay(10000);
  //sweep down
  o1.phase_increment = phaseinc_from_fractional_frequency(10000UL*256);
  o1.frequency_increment = -phaseinc(0.02);
  o1.framecounter = 200000;
  delay(10000);
}
// this is the heart of the wavetable synthesis. A phasor looks up a sine table
int8_t outputvalue  =0;
SIGNAL(PWM_INTERRUPT)
{
   PWM_VALUE_DESTINATION = outputvalue; //output first to minimize jitter
   outputvalue = (((uint8_t)(o1.amplitude>>8)) * pgm_read_byte(sintable+((o1.phase>>16)%LUTsize)))>>8;
  o1.phase += (uint32_t)o1.phase_increment;
  // ramp amplitude and frequency
  if(o1.framecounter>0)
  {
     --o1.framecounter;
     o1.amplitude += o1.amplitude_increment;
     o1.phase_increment += o1.frequency_increment;
  }
}

