
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
	emu86_push(state, FLAGS(STATE));
	emu86_push(state, IP(STATE));
	emu86_push(state, CS(STATE));

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
void emu86_exec(struct emu86_state * state)
{
	__(u8  cnt = 0);
	u8  op;
	s16 tmp_s16;
	s8  tmp_s8;

	while (1) {
		op = *(u8 *)SEG2LN(CS(STATE), IP(STATE));
		__(
				printf("\e\x7%X:%X ", CS(STATE), IP(STATE));
				cnt = (cnt + 1) & 0x0F;
		  );
		IP(STATE)++;

		switch (op) {
			/* execution end signature */
			case 0xFF:
				__(printf("\e\xe[emu86]: \e\x9halt\e\x7\n"));
				return;

				/* push/pop flags */
			case 0x9C:
			case 0x9D:
				__(printf("\e\xe[emu86]: \e\x9%sf	\e\xf",
							(op & 1 ? "pop" : "push")));

				if (op & 1)
					FLAGS(STATE) = emu86_pop(state);
				else
					emu86_push(state, FLAGS(STATE));

				__(printf("(%b)\n", FLAGS(STATE)));

				break;

				/* iret */
			case 0xCF:
				__(printf("\e\xe[emu86]: \e\x9iret\n"));

				CS(STATE) = emu86_pop(state);
				IP(STATE) = emu86_pop(state);
				FLAGS(STATE) = emu86_pop(state);
				break;

				/* call near */
			case 0xE8:
				tmp_s16 = *(s16 *)SEG2LN(CS(STATE), IP(STATE));
				__(printf("\e\xe[emu86]: \e\x9"
							"call	\e\xf%X\n",
							tmp_s16));
				IP(STATE) += 2;
				emu86_push(state, IP(STATE));
				IP(STATE) += tmp_s16;
				break;

				/* jmp short */
			case 0xEB:
				tmp_s8 = *(s8 *)SEG2LN(CS(STATE), IP(STATE));
				__(printf("\e\xe[emu86]: \e\x9"
							"jmp	\e\xf%X\n",
							tmp_s8));
				IP(STATE)++;
				emu86_push(state, IP(STATE));
				IP(STATE) += tmp_s8;
				break;

			default:
				/* push/pop gp_reg */
				if (op >= 0x50 && op < 0x60) {
					__(printf("\e\xe[emu86]: \e\x9%s	\e\xf%s ",
								(CHECK_BIT(op, 3) ? "pop" : "push"),
								gp_reg_name[op & 7]));

					if (CHECK_BIT(op, 3))
						state->gp[op & 7].a = emu86_pop(state);
					else
						emu86_push(state, state->gp[op & 7].a);

					__(printf("(%X)\n", state->gp[op & 7].a));
				}

				/* jcc short - jump if condition code */
				else if (op >> 4 == 7) {
					tmp_s8 = *(s8 *)SEG2LN(CS(STATE), IP(STATE));
					__(printf("\e\xe[emu86]: \e\x9"
								"jcc%d	\e\xf%X\n",
								op & 0x0F, tmp_s8));
					if (emu86_cond(state, op & 0x0F)) {
						emu86_push(state, IP(STATE));
						IP(STATE) += tmp_s8;
					}
					IP(STATE)++;
				}

				/* unknown op */
				else {
					__(printf("\e\xe[emu86]: \e\xcunknown opcode \e\xf"
								"%X\n", op));
					// return;
				}
		}

#ifdef __DEBUG__
		if (!cnt) {
			printf("\e\xe[emu86]: \e\xdpress ENTER to continue...");
			// wait for enter.
			char ch;
			readline(&ch, 0);
		}
#endif
	}
}

void emu86_push(struct emu86_state * state, u16 data)
{
	SP(STATE).a -= 2;
	*(u16 *)SEG2LN(SS(STATE), SP(STATE).a) = data;
}

u16 emu86_pop(struct emu86_state * state)
{
	u16 data = *(u16 *)SEG2LN(SS(STATE), SP(STATE).a);
	SP(STATE).a += 2;
	return data;
}

u8 emu86_cond(struct emu86_state * state, u8 cond)
{
	assert(!(cond >> 4));

	u8 result;
	switch (cond >> 1) {
		case 0: result = CHECK_BIT(FLAGS(STATE), FLAG_OF_BIT);
				break;
		case 1: result = CHECK_BIT(FLAGS(STATE), FLAG_CF_BIT);
				break;
		case 2: result = CHECK_BIT(FLAGS(STATE), FLAG_ZF_BIT);
				break;
		case 3: result = CHECK_BIT(FLAGS(STATE), FLAG_CF_BIT)
				| CHECK_BIT(FLAGS(STATE), FLAG_ZF_BIT);
				break;
		case 4: result = CHECK_BIT(FLAGS(STATE), FLAG_SF_BIT);
				break;
		case 5: result = CHECK_BIT(FLAGS(STATE), FLAG_PF_BIT);
				break;
		case 6: result = CHECK_BIT(FLAGS(STATE), FLAG_SF_BIT)
				^ CHECK_BIT(FLAGS(STATE), FLAG_OF_BIT);
				break;
		case 7: result = CHECK_BIT(FLAGS(STATE), FLAG_ZF_BIT)
				| (CHECK_BIT(FLAGS(STATE), FLAG_SF_BIT)
						^ CHECK_BIT(FLAGS(STATE), FLAG_OF_BIT));
				break;
	}

	if (cond & 1) result = !result;
	return result;
}

