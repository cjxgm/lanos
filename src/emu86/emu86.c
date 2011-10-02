
#include "emu86.h"
#include "stdio.h"

struct ivt_entry
{
	u16 offset;
	u16 segment;
};

void emu86_int(struct emu86_state * state, u8 int_no)
{
	printf("\n\e\xf[emu86]:\e\x7 int %Xh\n", int_no);
	emu86_push16(state, state->cs);
	emu86_push16(state, state->ip);

	struct ivt_entry * ie = (struct ivt_entry *)(int_no*4);
	state->cs = ie->segment;
	state->ip = ie->offset;

	printf("\e\xf[emu86]:\e\x7 cs:ip = %Xh:%Xh\n",
			state->cs, state->ip);
}

// return when get instruction 0xFF.
void emu86_execute(struct emu86_state * state)
{
}

void emu86_push16(struct emu86_state * state, u16 data)
{
	state->sp -= 2;
	*(u16 *)((state->ss << 4) + state->sp) = data;
	printf("\e\xf[emu86]:\e\x7 pushed %Xh to %Xh:%Xh\n",
			data, state->ss, state->sp);
}

