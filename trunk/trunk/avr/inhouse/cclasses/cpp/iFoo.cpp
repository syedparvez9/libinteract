#include "iFoo.h"
#include <stdio.h>

// accessors
void iFoo::setFoo(int v)
{
	this->foo = v;
}
int iFoo::getFoo()
{
	return this->foo;
}
// constructor
iFoo::iFoo()
{
	printf("hello\n");
}
// destructor
iFoo::~iFoo()
{
	printf("bye!\n");
}
