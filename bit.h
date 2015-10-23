/*
 * bit.h -- Simple manipulation of bits for microcontrollers
 *
 * By Colin ML Burnett (Copyright 2015)
 *
 * Licensed under Creative Commons Attributeion-ShareAlike 3.0 (CC BY-SA 3.0)
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#ifndef BIT_H_
#define BIT_H_

// Shifts the value @v over by @b bits
#define BITV(v,b)		(v << b)

// Same as BITV but ones complement
#define NBITV(v,b)		(~BITV(v,b))

// Shortcuts to BITV for values 0-7
#define BIT0(b)			BITV(0,b)
#define BIT1(b)			BITV(1,b)
#define BIT2(b)			BITV(2,b)
#define BIT3(b)			BITV(3,b)
#define BIT4(b)			BITV(4,b)
#define BIT5(b)			BITV(5,b)
#define BIT6(b)			BITV(6,b)
#define BIT7(b)			BITV(7,b)

#define NBIT0(b)		NBITV(0,b)
#define NBIT1(b)		NBITV(1,b)
#define NBIT2(b)		NBITV(2,b)
#define NBIT3(b)		NBITV(3,b)
#define NBIT4(b)		NBITV(4,b)
#define NBIT5(b)		NBITV(5,b)
#define NBIT6(b)		NBITV(6,b)
#define NBIT7(b)		NBITV(7,b)

/* Get a mask of @width bits wide
 * For example:
 *   GETMASK(0) = 0x00000000
 *   GETMASK(1) = 0x00000001
 *   GETMASK(2) = 0x00000003
 *   GETMASK(4) = 0x0000000F
 *   GETMASK(8) = 0x000000FF
 *
 * I have not thought about what GETMASK(32) will return but I suspect it would return correctly.
*/
#define GETMASK(width)				((1 << (width)) - 1)
/* Get the inverted GETMASK */
#define GETMASKI(width)				(~((1 << (width)) - 1))

/* Get the mask from GETMASK(@width) and then shift it over by @shift bits.
 * For example:
 *   GETSHIFTMASK(2,0)  = 0x00000003
 *   GETSHIFTMASK(2,1)  = 0x00000006
 *   GETSHIFTMASK(2,2)  = 0x0000000C
 *   GETSHIFTMASK(15,0) = 0x0000000F
 *   GETSHIFTMASK(15,8) = 0x00000F00
 */
#define GETSHIFTMASK(width,shift)	BITV(GETMASK(width), shift)
/* Get the inverted GETSHIFTMASK */
#define GETSHIFTMASKI(width,shift)	NBITV(GETMASK(width), shift)

/* Mask the value @val to be @width bits wide and shift it over @shift bits.
 * This is to take a "random" value and put it in the appropriate place
 * to be OR'ed with another value which requires ensuring @value is
 * of the correct bit width and be located at the appropriate bits.
 *
 * For example:
 *   MASKVALUE(2, 4, 8) = ((2 & 0xF) << 8) = 0x200
 *   MASKVALUE(15, 2, 4) = ((15 & 0x3) << 4) = (3 << 4) = 0x30
 */
#define MASKVALUE(val, width, shift) (((val) & GETMASK(width)) << (shift))

/* Unmasks the value from @val that is @width bits wide and @shift bits over
 * For example:
 *   UNMASKVALUE(0xFFFFACFF, 8, 8) = 0xAC
 *   UNMASKVALUE(0xFFFFACFF, 3, 11) = 0x05
 */
#define UNMASKVALUE(val, width, shift) (((val) & GETSHIFTMASK(width,shift)) >> (shift))

/* Apply bit value @val to the existing value @init
 * by assuming @val has bit width of @width and should
 * be located @shift bits over.
 *
 * This is intended to be used with setting values to registers
 * where @init is a defined constant for the register location,
 * @val is whatever the bits should be (the user manual indicates
 * what these various values are) and the value should only be
 * @width bits wide and located in @init at @shift bits over.
 */
#define BITSET(init,val,width,shift) ((init & GETSHIFTMASKI(width,shift)) | MASKVALUE(val,width,shift))

/* Takes the register value @loc, masks in @val, and stores it back into @loc */
#define REGSET(loc,val,width,shift) do{loc = BITSET(loc,val,width,shift);}while(0)

/* Gets the value from @loc that is @width bits wide and at @shift bits over.
 * (Basically just copying the UNMASKVALUE macro to keep naming consistency.)
*/
#define REGGET(loc,width,shift) UNMASKVALUE(loc,width,shift)

/* Pin definitions regardless of which port it is on */
#define PIN_0			BIT1(0)
#define PIN_1			BIT1(1)
#define PIN_2			BIT1(2)
#define PIN_3			BIT1(3)
#define PIN_4			BIT1(4)
#define PIN_5			BIT1(5)
#define PIN_6			BIT1(6)
#define PIN_7			BIT1(7)
#define PIN_8			BIT1(8)
#define PIN_9			BIT1(9)
#define PIN_10			BIT1(10)
#define PIN_11			BIT1(11)
#define PIN_12			BIT1(12)
#define PIN_13			BIT1(13)
#define PIN_14			BIT1(14)
#define PIN_15			BIT1(15)
#define PIN_16			BIT1(16)
#define PIN_17			BIT1(17)
#define PIN_18			BIT1(18)
#define PIN_19			BIT1(19)
#define PIN_20			BIT1(20)
#define PIN_21			BIT1(21)
#define PIN_22			BIT1(22)
#define PIN_23			BIT1(23)
#define PIN_24			BIT1(24)
#define PIN_25			BIT1(25)
#define PIN_26			BIT1(26)
#define PIN_27			BIT1(27)
#define PIN_28			BIT1(28)
#define PIN_29			BIT1(29)
#define PIN_30			BIT1(30)
#define PIN_31			BIT1(31)

// Combine multiple bytes into one
#define COMBINE_8TO16(buf, offset) ( ((uint16_t)buf[offset] << 8) | (uint16_t)buf[offset+1] )
#define COMBINE_8TO32(buf, offset) ( ((uint32_t)buf[offset] << 24) | ((uint32_t)buf[offset+1] << 16) | ((uint32_t)buf[offset+2] << 8) | (uint32_t)buf[offset+3] )

#endif /* BIT_H_ */
