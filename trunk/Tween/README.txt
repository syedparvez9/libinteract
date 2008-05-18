Tween.h Tween.c
Part of LibInteract for AVR
Alexandre Quessy 2008

This is a first working draft of a C class for motion tweening.
The crucial maths are taken from the excellent Robert Penner easing
equations. BSD License.

This is a C classes. It uses a struct for storing the attributes. 
All function calls need a pointer to a variable of type Tween_t as a
first argument. Look for tutorials on pointers. 

