
#ifndef __EMU86__
#define __EMU86__

#include "common.h"

union reg16 {
	struct {
		u8	l;
		u8	h;
	} b;
	u16 a;
};

struct emu86_state
{
	union reg16 ax;
	union reg16 bx;
	union reg16 cx;
	union reg16 dx;

	u16 si;
	u16 di;
	u16 sp;
	u16 bp;
	u16 ip;

	u16	cs;
	u16	ds;
	u16	ss;
	u16	es;
	/*
	u16	fs;
	u16	gs;
	*/
};

void emu86_int(struct emu86_state * state, u8 int_no);
// execute until execution end signature (0xFF) appear.
void emu86_execute(struct emu86_state * state);
void emu86_push16(struct emu86_state * state, u16 data);

#endif

