/**
General bitmasks manipulation file
**/
#ifndef bitmasks_h
#define bitmasks_h

#define SET_BIT_K(val_, BitIndex)     ((val_) |= (1 << (BitIndex)))
#define CLEAR_BIT_K(val_, BitIndex)   ((val_) &= ~(1 << (BitIndex)))
#define TOGGLE_BIT_K(val_, BitIndex)  ((val_) ^= (1 << (BitIndex)))
#define CHECK_BIT_K(val_, BitIndex)   (((val_) & (1 << (BitIndex))) >> (BitIndex))

#endif
