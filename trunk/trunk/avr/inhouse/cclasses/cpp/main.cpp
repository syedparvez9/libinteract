#include <stdio.h>
#include "iFoo.h"
int main(int argc, char **argv)
{
	iFoo *x = new iFoo;
	
	x->setFoo(54);
	printf("foo: %d\n",x->getFoo());
	delete x;
	return 0;
}

