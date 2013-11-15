;---------------------------------------------------------------------------;
; Touch sensor test module                                                  ;
; (C)ChaN, 2007 (http://elm-chan.org/)                                      ;
; modified jvm                                                              ;
;---------------------------------------------------------------------------;
; This module uses a 8 bit timer Timer1.
.nolist
#include <avr/io.h>
.list

#define TIMER_CTRL	_SFR_IO_ADDR(TCCR1)
//#define TIMER_CNTH	_SFR_IO_ADDR(TCNT1H)
#define TIMER_CNTL	_SFR_IO_ADDR(TCNT1)

#define	CH0_OUT _SFR_IO_ADDR(DDRB),3
#define	CH0_IN	_SFR_IO_ADDR(PINB),3
#define	CH1_OUT _SFR_IO_ADDR(DDRB),4
#define	CH1_IN	_SFR_IO_ADDR(PINB),4
/*#define	CH2_OUT _SFR_IO_ADDR(DDRA),1
#define	CH2_IN	_SFR_IO_ADDR(PINA),1
#define	CH3_OUT _SFR_IO_ADDR(DDRA),0
#define	CH3_IN	_SFR_IO_ADDR(PINA),0
#define	CH4_OUT _SFR_IO_ADDR(DDRD),2
#define	CH4_IN	_SFR_IO_ADDR(PIND),2
#define	CH5_OUT _SFR_IO_ADDR(DDRD),3
#define	CH5_IN	_SFR_IO_ADDR(PIND),3
#define	CH6_OUT _SFR_IO_ADDR(DDRD),4
#define	CH6_IN	_SFR_IO_ADDR(PIND),4
#define	CH7_OUT _SFR_IO_ADDR(DDRD),5
#define	CH7_IN	_SFR_IO_ADDR(PIND),5 
*/

;---------------------------------------------------------------------------;
; Get sensor capacitance
;
;Prototype: void xmit (uint8_t data);
;
; channel number is in R24 ( first parameter passed to the assy-function )
;
.global boogieball
.func boogieball
boogieball:
	in	r18, _SFR_IO_ADDR(SREG)	;Save flags
	ldi	r25, 2
    out	TIMER_CNTL, r1 ;this zeroes the TIMER_CNTL
    out 0x38,r25; clear overflow interrupt flag
    ldi r25,1
    cli
;
00:	cpi	r24, 0
	brne	10f
	out	TIMER_CTRL, r25
	cbi	CH0_OUT
01:	sbis	CH0_IN
	rjmp	01b
	sbi	CH0_OUT
	rjmp	99f
;
10:	cpi	r24, 1
	brne    14f
	out	TIMER_CTRL, r25
	cbi	CH1_OUT
11:	sbis	CH1_IN
	rjmp	11b
	sbi	CH1_OUT
14:	rjmp	99f
/*
20:	cpi	r24, 2
	brne	30f
	out	TIMER_CTRL, r25
	cbi	CH2_OUT
21:	sbis	CH2_IN
	rjmp	21b
	sbi	CH2_OUT
	rjmp	99f

30:	cpi	r24, 3
	brne	40f
	out	TIMER_CTRL, r25
	cbi	CH3_OUT
31:	sbis	CH3_IN
	rjmp	31b
	sbi	CH3_OUT
	rjmp	99f

40:	cpi	r24, 4
	brne	50f
	out	TIMER_CTRL, r25
	cbi	CH4_OUT
41:	sbis	CH4_IN
	rjmp	41b
	sbi	CH4_OUT
	rjmp	99f

50:	cpi	r24, 5
	brne	60f
	out	TIMER_CTRL, r25
	cbi	CH5_OUT
51:	sbis	CH5_IN
	rjmp	51b
	sbi	CH5_OUT
	rjmp	99f

60:	cpi	r24, 6
	brne	70f
	out	TIMER_CTRL, r25
	cbi	CH6_OUT
61:	sbis	CH6_IN
	rjmp	61b
	sbi	CH6_OUT
	rjmp	99f

70:	cpi	r24, 7
	brne	99f
	out	TIMER_CTRL, r25
	cbi	CH7_OUT
71:	sbis	CH7_IN
	rjmp	71b
	sbi	CH7_OUT
	rjmp	99f
*/

99:
	out	TIMER_CTRL, r1		;Stop Timer -> put zero to it.
    in	r24, TIMER_CNTL     ;  timer counter value to R24
    in r25, 0x38      ;to return only a single value
    sbrc r25, 2; if timer overflow is set
    ldi r24, 255    ;if not, max out the timer
    ldi r25,2;
    out 0x38 ,r25;
    ldi r25,0

    ;sei
	out	_SFR_IO_ADDR(SREG), r18
	ret
.endfunc



