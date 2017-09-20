#include "river.h"

int main(int argc, const char *argv[])
{
	int distance = 0;
	if(argv[1])
		distance = load_file((char*)argv[1]);
	else
		fprintf(stderr, "Forget to put ./river.in0!\n");
	printf("%d\n", distance);
	return EXIT_SUCCESS;
}
