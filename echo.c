#include <stdio.h>


int main(int argc, char **argv)
{
	while (*++argv)
		printf("%s%s", *argv, *(argv+1) ? " ":"");
	printf("\n");
	return 0;
}
