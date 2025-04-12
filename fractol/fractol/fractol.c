#include "../fractol.h"
#include <stdio.h>
t_complex	add_complex(t_complex a, t_complex b)
{
	t_complex	result;

	/* Add the real and imaginary parts separately */
	result.imag = a.imag + b.imag;
	result.real = a.real + b.real;
	return (result);
}
int	main(void)
{
	t_complex	t;
	t_complex	s;
	t_complex	result;

	/* Initialize first complex number */
	t.imag = 2.5;
	t.real = 3.0;
	
	/* Initialize second complex number */
	s.imag = 2.7;  /* 2.5 + 0.2 */
	s.real = 6.0;  /* 3.0 + 3.0 */
	
	/* Add the complex numbers */
	result = add_complex(t, s);
	
	/* Print the result */
	printf("Complex number 1: %.1f + %.1fi\n", t.real, t.imag);
	printf("Complex number 2: %.1f + %.1fi\n", s.real, s.imag);
	printf("Sum: %.1f + %.1fi\n", result.real, result.imag);
	
	return (0);
}
