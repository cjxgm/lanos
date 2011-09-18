
#ifndef __COMMON__
#define __COMMON__

typedef unsigned int	u32;
typedef unsigned short	u16;
typedef unsigned char	u8;
typedef int		s32;
typedef short	s16;
typedef char	s8;

void outb(u16 port, u8  value);
void outw(u16 port, u16 value);
u8   inb (u16 port);
u16  inw (u16 port);

#define NULL ((void *)0)

#endif

