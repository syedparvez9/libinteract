#include "t_autoscale.h"

#include <stdlib.h> /* for malloc */

float _autoscale_min(float f, float g)
{
	return (f <= g) ? f : g;
}
float _autoscale_max(float f, float g)
{
	return (f >= g) ? f : g;
}

float autoscale_compute(t_autoscale *x, float val) 
{
	float ratio; // on 1.0
	float range;
	x->max = _autoscale_max(x->max, val);
	x->min = _autoscale_min(x->min, val);
	range = (x->max - x->min);
	if (range == 0.0)
	{
		range = 0.1; // avoids division by 0
	}
	ratio = (val - x->min ) / range;
	return (ratio * x->scale_to) + x->scale_from;
}

t_autoscale *autoscale_new()
{
	t_autoscale *x = malloc(sizeof(t_autoscale));
	
	// set initial values
	x->scale_from = 0.0;
	x->scale_to = 1.0;
	autoscale_reset(x);
	return x;
}

void autoscale_reset(t_autoscale *x)
{
	x->min = AUTOSCALE_MAXFLOAT;
	x->max = AUTOSCALE_MINFLOAT;
}


void autoscale_free(t_autoscale *x)
{
	free(x);
}
