#include <stdio.h>
#include "iFoo.h"
int main(int argc, char **argv)
{
	iFoo *x = iFoo_new();
	
	iFoo_setFoo(x, 54);
	printf("foo: %d\n", iFoo_getFoo(x));
	iFoo_free(x);
	
	return 0;
}

