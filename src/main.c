
#include "monitor.h"
#include "printf.h"

int main(void * multiboot_header)
{
	monitor_clear();

	monitor_write("Hello, world!\n");
	monitor_write("\tMy\tG\treat OS!!\n");

	printf("printf test: %x\n", 0x1234abcd);
	printf("\t%d\t%u", -1, 12);
	printf("\t%d\t%d", 0, -0);

    return 0;
}
