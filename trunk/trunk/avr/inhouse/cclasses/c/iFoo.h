// class iFoo
// attributes
typedef struct 
{
	int foo;
} iFoo;

// methods
int iFoo_getFoo(iFoo *x);
void iFoo_setFoo(iFoo *x, int v);
iFoo *iFoo_new();
void iFoo_free(iFoo *x);
