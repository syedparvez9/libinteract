#include <stdio.h>
#include "t_autoscale.h"


// print stuff
void debug_it(t_autoscale *x, float val)
{
	printf("--------\n");
	printf("val : %f\n", val);
	printf("scaled : %f\n", autoscale_compute(x, val));
}

// MAIN
int main(int argc, char *argv[])
{
	int i;
	t_autoscale *x = autoscale_new();
	
	printf("### autoscale test ###\n");
	printf("from 0 to 100.0\n");
	
	for (i = 0; i < 10; i++)
	{
		debug_it(x, 15.0 - i);
	}
	for (i = 0; i < 10; i++)
	{
		debug_it(x, (float) i);
	}
	for (i = 10; i < 20; i++)
	{
		debug_it(x, (float) i);
	}
	
	autoscale_free(x);
	return 0;
}

