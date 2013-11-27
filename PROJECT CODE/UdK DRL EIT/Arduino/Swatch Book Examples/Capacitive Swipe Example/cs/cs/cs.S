;---------------------------------------------------------------------------;
; Touch sensor test module                                                  ;
; (C)ChaN, 2007 (http://elm-chan.org/)                                      ;
; modified by jvm                                                           ;
;---------------------------------------------------------------------------;
; This module uses a 8 bit timer Timer1, instead of original using 16-bit.
.nolist
#include <avr/io.h>
.list

#define TIMER_CTRL	_SFR_IO_ADDR(TCCR1)
#define TIMER_CNTL	_SFR_IO_ADDR(TCNT1)

#define	CH0_OUT _SFR_IO_ADDR(DDRB),3
#define	CH0_IN	_SFR_IO_ADDR(PINB),3
#define	CH1_OUT _SFR_IO_ADDR(DDRB),4
#define	CH1_IN	_SFR_IO_ADDR(PINB),4
#define	CH2_OUT _SFR_IO_ADDR(DDRB),2
#define	CH2_IN	_SFR_IO_ADDR(PINB),2
#define	CH3_OUT _SFR_IO_ADDR(DDRB),0
#define	CH3_IN	_SFR_IO_ADDR(PINB),0

;---------------------------------------------------------------------------;
; Get sensor capacitance
;
; Uses the T1 for reading the rising time of a pin.
; The pin capacitance is used as the integrator, and external pull-up (470k)
; is used as a current source.
;
; Major change to original source code: this one uses T1 OVF to check if the
; pin has not risen quickly enough. This is to prevent code getting stuck.
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
01: in r25, 0x38    ; to return only a single value
    sbrc r25, 2     ; if timer overflow is set
    rjmp    100f    ;MAXED OUT TIMER
    sbis	CH0_IN
	rjmp	01b
	sbi	CH0_OUT
	rjmp	99f
;
10:	cpi	r24, 1
	brne    20f
	out	TIMER_CTRL, r25
	cbi	CH1_OUT
11:	in r25, 0x38    ; to return only a single value
    sbrc r25, 2     ; if timer overflow is set
    rjmp    100f    ;MAXED OUT TIMER
    sbis	CH1_IN
	rjmp	11b
	sbi	CH1_OUT
	rjmp	99f

20:	cpi	r24, 2
	brne	30f
	out	TIMER_CTRL, r25
	cbi	CH2_OUT
21:	in r25, 0x38    ; to return only a single value
    sbrc r25, 2     ; if timer overflow is set
    rjmp    100f    ;MAXED OUT TIMER
    sbis	CH2_IN
	rjmp	21b
	sbi	CH2_OUT
	rjmp	99f

30:	cpi	r24, 3
	brne	40f
	out	TIMER_CTRL, r25
	cbi	CH3_OUT
31:	in r25, 0x38    ; to return only a single value
    sbrc r25, 2     ; if timer overflow is set
    rjmp    100f    ;MAXED OUT TIMER
    sbis	CH3_IN
	rjmp	31b
	sbi	CH3_OUT
40:	rjmp	99f


99:
	out	TIMER_CTRL, r1		;Stop Timer -> put zero to it.
    in	r24, TIMER_CNTL     ;  timer counter value to R24
    ldi r25,0

    ;sei
	out	_SFR_IO_ADDR(SREG), r18
	ret
100:
    out	TIMER_CTRL, r1		;Stop Timer -> put zero to it.
    ldi r24, 255    ;if not, max out the timer
    ldi r25,0
;sei
    out	_SFR_IO_ADDR(SREG), r18
    ret
.endfunc



