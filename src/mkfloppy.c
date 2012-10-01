
// vim: ft=c ts=4 sw=4 sts=0 noet
#include <stdio.h>
#include <assert.h>




static void print_help();
static void mkfloppy(FILE * img, FILE * boot, FILE * core);




int main(int argc, char * argv[])
{
	// check parameters
	if (argc != 4) print_help(argv[0]);

	// open files
	FILE * img = fopen(argv[1], "w");
	assert(img);
	FILE * boot = fopen(argv[2], "r");
	assert(boot);
	FILE * core = fopen(argv[3], "r");
	assert(core);

	// make floppy
	mkfloppy(img, boot, core);

	// close files
	fclose(boot);
	fclose(core);
	fclose(img);

	// succeeded
	return 0;
}


static void print_help(const char * self)
{
	printf("\nmkfloppy - lanos boot floppy maker\n");
	printf("Copyright (C) eXerigumo Clanjor, 2012.\n");
	printf("Licensed under GPLv2. ABSOLUTELY NO WARRANTY!\n\n");
	printf("usage: %s <floppy.img> <boot> <core>\n\n", self);
}


static void mkfloppy(FILE * img, FILE * boot, FILE * core)
{
	/* there are 2880 sectors in a generic floppy.
	 * each sector has 512 bytes.
	 */

	int ch;
	int size_left;

	// write <boot>: the boot sector
	printf("writing boot...");
	while ((ch = fgetc(boot)) != EOF)
		fputc(ch, img);

	size_left = 510 - ftell(img);	// remaining space in the 1st sector
	assert(size_left >= 0);
	while (size_left--)
		fputc(0, img);

	fputc(0x55, img);				// `. bootable signature
	fputc(0xAA, img);				// /
	printf("\n");

	// write <core>: the core (kernel), up to 63.5kb (127 sectors)
	printf("writing core...");
	while ((ch = fgetc(core)) != EOF)
		fputc(ch, img);
	assert(ftell(img) <= 128*512);	// up to 127(+1 for boot) sectors
	printf("\n");

	// fill up to a floppy size
	printf("filling up to a floppy size...");
	size_left = 2880*512 - ftell(img);	// space left in a floppy
	while (size_left--)
		fputc(0, img);
	printf("\n");
}

