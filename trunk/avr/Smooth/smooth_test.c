#include <stdio.h>
#include "Smooth.h"
int main(int argc, char **argv)
{
	int i;
	int run[] = {1,4,9,9,9,1,1,45,4,7};
	Smooth_t s;
	float r;
	
	Smooth_init(&s, 0);
	Smooth_setSlide(&s, 7.0);
	
	for (i=0;i<10;i++)
	{
		r = Smooth_slide(&s,run[i]);
		printf("%f\n",r);
	}
	return 0;
}
