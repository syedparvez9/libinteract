#ifndef AUTOSCALE_H
#define AUTOSCALE_H

// 32 bits floats like in the ATmega8
#define AUTOSCALE_MAXFLOAT  3.4028235E+38
#define AUTOSCALE_MINFLOAT -3.4028235E+38

// attributes
typedef struct _autoscale
{
	float min;
	float max;
	float scale_from;
	float scale_to;	
} t_autoscale;

// methods
// constructor, destructor
t_autoscale *autoscale_new();
void autoscale_free(t_autoscale *x);

// 
void autoscale_reset(t_autoscale *x);
float autoscale_compute(t_autoscale *x, float val);

#endif
