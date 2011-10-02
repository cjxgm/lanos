
#include "emu86.h"
#include "stdio.h"
#include "assert.h"

struct ivt_entry
{
	u16 offset;
	u16 segment;
};

#ifdef __DEBUG__
static const char * gp_reg_name[] = {
	"ax", "cx", "dx", "bx",
	"sp", "bp", "si", "di"
};
#endif

#define STATE	(*state)

void emu86_int(struct emu86_state * state, u8 int_no)
{
	__(
			printf("\n");
			printf("\e\xe[emu86]: \e\x9int	\e\xf%X\n", int_no);
			printf("\e\xe[emu86]: \e\x1push	\e\x7"
				"flags (%X)\n", FLAGS(STATE));
			printf("\e\xe[emu86]: \e\x1push	\e\x7"
				"ip (%X)\n", IP(STATE));
			printf("\e\xe[emu86]: \e\x1push	\e\x7"
				"cs (%X)\n", CS(STATE));
	  );
	emu86_push16(state, FLAGS(STATE));
	emu86_push16(state, IP(STATE));
	emu86_push16(state, CS(STATE));

	struct ivt_entry * ie = (struct ivt_entry *)(int_no * 4);
	CS(STATE) = ie->segment;
	IP(STATE) = ie->offset;

	__(
			printf("\e\xe[emu86]: \e\x1mov	\e\x7"
				"cs, %X\n", CS(STATE));
			printf("\e\xe[emu86]: \e\x1mov	\e\x7"
				"ip, %X\n", IP(STATE));
	  );
}

// return when get instruction 0xFF.
void emu86_execute(struct emu86_state * state)
{
	u8 op;
	while (1) {
		// __(printf("\e\x7%X:%X ", CS(STATE), IP(STATE)));
		switch ((op = *(u8 *)SEG2LN(CS(STATE), IP(STATE)))) {
			/* execution end signature */
			case 0xFF:
				return;

				/* push/pop flags */
			case 0x9C:
			case 0x9D:
				__(printf("\e\xe[emu86]: \e\x9%sf\e\xf\n",
							(op & 1 ? "pop" : "push")));

				if (op & 1)
					FLAGS(STATE) = emu86_pop16(state);
				else
					emu86_push16(state, FLAGS(STATE));

				break;

				/* iret */
			case 0xCF:
				__(printf("\e\xe[emu86]: \e\x9iret	\e\xf\n"));

				CS(STATE) = emu86_pop16(state);
				IP(STATE) = emu86_pop16(state) - 1;
				FLAGS(STATE) = emu86_pop16(state);
				break;

			default:
				/* push/pop gp_reg */
				if (op >= 0x50 && op < 0x60) {
					__(printf("\e\xe[emu86]: \e\x9%s	\e\xf%s\n",
								(CHECK_BIT(op, 3) ? "pop" : "push"),
								gp_reg_name[op & 7]));

					if (CHECK_BIT(op, 3))
						state->gp[op & 7].a = emu86_pop16(state);
					else
						emu86_push16(state, state->gp[op & 7].a);
				}

				/* unknown op */
				else {
					__(printf("\e\xe[emu86]: \e\xcunknown opcode \e\xf"
								"%X\n", op));
					// return;
				}
		}

		IP(STATE)++;
#ifdef __DEBUG__
		if (!(IP(STATE) & 0x0f)) {
			printf("\e\xe[emu86]: \e\xdpress ENTER to continue...");
			// wait for enter.
			char ch;
			readline(&ch, 0);
		}
#endif
	}
}

void emu86_push16(struct emu86_state * state, u16 data)
{
	SP(STATE).a -= 2;
	*(u16 *)SEG2LN(SS(STATE), SP(STATE).a) = data;
}

u16 emu86_pop16(struct emu86_state * state)
{
	u16 data = *(u16 *)SEG2LN(SS(STATE), SP(STATE).a);
	SP(STATE).a += 2;
	return data;
}

