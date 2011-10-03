
#ifndef __EMU86__
#define __EMU86__

#include "common.h"

union reg16 {
	u16 a;
	u8  b[2];
};

struct emu86_state
{
	union reg16 gp[8];	// general purpose registers
	u16 seg[4];			// segment registers

	u16 ip;
	u16 flags;
};

void emu86_int (struct emu86_state * state, u8  int_no);
// execute until hlt(0xF4) appear.
void emu86_exec(struct emu86_state * state);
void emu86_push(struct emu86_state * state, u16 data);
u16  emu86_pop (struct emu86_state * state);
// check condition codes
u8   emu86_cond(struct emu86_state * state, u8  cond);

#define SEG2LN(SEG,OFFSET)	(((SEG) << 4) + (OFFSET))

#define CHECK_BIT(X,BIT)	((X) & (1 << (BIT)))
#define SET_BIT(X,BIT)		((X) | (1 << (BIT)))
#define CLEAR_BIT(X,BIT)	((X) & ~(1 << (BIT)))

#define AX(S)		((S).gp[0])
#define CX(S)		((S).gp[1])
#define DX(S)		((S).gp[2])
#define BX(S)		((S).gp[3])
#define SP(S)		((S).gp[4])
#define BP(S)		((S).gp[5])
#define SI(S)		((S).gp[6])
#define DI(S)		((S).gp[7])

#define ES(S)		((S).seg[0])
#define CS(S)		((S).seg[1])
#define SS(S)		((S).seg[2])
#define DS(S)		((S).seg[3])

#define IP(S)		((S).ip)
#define FLAGS(S)	((S).flags)

#define FLAG_CF_BIT		0
#define FLAG_PF_BIT		2
#define FLAG_ZF_BIT		6
#define FLAG_SF_BIT		7
#define FLAG_OF_BIT		11

#endif

