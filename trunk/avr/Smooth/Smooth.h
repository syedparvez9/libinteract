typedef struct 
{
	float last;	
	float slide;
} Smooth_t;

void  Smooth_init(Smooth_t *me, float f);
void  Smooth_setLast(Smooth_t *me, float f);
void  Smooth_setSlide(Smooth_t *me, float f);
float Smooth_slide(Smooth_t *me, float f);
