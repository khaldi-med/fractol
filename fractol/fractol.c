#include "fractol.h"
#include <stdio.h>

t_complex	add_complex(t_complex a, t_complex b)
{
	t_complex	result;

	// Add the real and imaginary parts separately
	// Fill in the code here
	result.img = a.img + b.img;
	result.real = b.real + b.real;
	return (result);
}

int	main(void)
{
	double		i;
	double		r;
	t_complex	t;
	t_complex	s;
	t_complex	result;

	i = 2.5;
	r = 3;
	t.img = i;
	t.real = r;
	s.img = i + 0.2;
	s.real = r + 3;
	result = add_complex(t, s);
	printf("%f\n %f\n", result.img, result.real);
	return (0);
}
