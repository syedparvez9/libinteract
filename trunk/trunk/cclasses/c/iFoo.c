#include "iFoo.h"
#include <stdio.h>
#include <stdlib.h>

// accessors
int iFoo_getFoo(iFoo *x)
{
	return x->foo;
}
void iFoo_setFoo(iFoo *x, int v)
{
	x->foo = v;
}
// constructor
iFoo *iFoo_new()
{
	printf("hello\n");
	return (iFoo *) malloc(sizeof(iFoo));
}
// destructor
void iFoo_free(iFoo *x)
{
	free(x);
	printf("bye!\n");
}

