
// vim: ft=c ts=4 sw=4 sts=0 noet
#include <stdio.h>
#include <assert.h>




static void print_help();
static void mkfloppy(FILE * img, FILE * boot, FILE * loader, FILE * core);




int main(int argc, char * argv[])
{
	// check parameters
	if (argc != 5) {
		print_help(argv[0]);
		return 1;
	}

	// open files
	FILE * img = fopen(argv[1], "w");
	assert(img);
	FILE * boot = fopen(argv[2], "r");
	assert(boot);
	FILE * loader = fopen(argv[3], "r");
	assert(loader);
	FILE * core = fopen(argv[4], "r");
	assert(core);

	// make floppy
	mkfloppy(img, boot, loader, core);

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
	printf("usage: %s <floppy.img> <boot> <loader> <core>\n\n", self);
}


static void mkfloppy(FILE * img, FILE * boot, FILE * loader, FILE * core)
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

	// write <loader>: the stage 2 of boot loader,
	// up to 63.5kb (127 sectors)
	printf("writing loader...");
	while ((ch = fgetc(loader)) != EOF)
		fputc(ch, img);
	// up to 127(+1 for <boot>) sectors
	size_left = 128*512 - ftell(img);
	assert(size_left >= 0);
	while (size_left--)
		fputc(0, img);
	printf("\n");

	// write <core>: the core of os (kernel)
	// up to 1376kb (2880-128 = 2752 sectors)
	printf("writing core...");
	while ((ch = fgetc(core)) != EOF)
		fputc(ch, img);
	assert(ftell(img) <= 2880*512);	// up to 2880(floppy size) sectors
	printf("\n");

	// fill up to a floppy size
	printf("filling up to a floppy size...");
	size_left = 2880*512 - ftell(img);	// space left in a floppy
	while (size_left--)
		fputc(0, img);
	printf("\n");
}

