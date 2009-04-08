#include "Smooth.h"
void Smooth_init(Smooth_t *me, float f)
{
	me->last = f;
	me->slide = 1;
}
void Smooth_setLast(Smooth_t *me, float f)
{
	me->last = f;
}
void Smooth_setSlide(Smooth_t *me, float f)
{
	me->slide = f;
}
float Smooth_slide(Smooth_t *me, float f)
{
	me->last = me->last + (f - me->last) / me->slide;
	return me->last;
}
