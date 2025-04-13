#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Complex number structure */
typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

/* Function to display complex number in readable format */
void print_complex(t_complex z)
{
	if (z.imag >= 0)
		printf("%.6f + %.6fi", z.real, z.imag);
	else
		printf("%.6f - %.6fi", z.real, fabs(z.imag));
}

/* Function to demonstrate Mandelbrot iteration process */
void test_mandelbrot_iterations(t_complex c, int max_iterations)
{
	t_complex	z;
	double		temp;
	int			i;
	double		magnitude;

	/* Initialize z to 0 */
	z.real = 0.0;
	z.imag = 0.0;
	
	printf("\n==== MANDELBROT ITERATION TEST ====\n");
	printf("Testing point c = ");
	print_complex(c);
	printf("\n\n");
	
	printf("Starting with z₀ = ");
	print_complex(z);
	printf("\n\n");
	
	i = 0;
	/* Iterate the formula z = z² + c */
	while (i < max_iterations)
	{
		/* Calculate magnitude of z */
		magnitude = z.real * z.real + z.imag * z.imag;
		
		/* Check if magnitude of z is greater than 2 */
		if (magnitude > 4.0)
		{
			printf("Iteration %d: |z| = %.6f > 2\n", i, sqrt(magnitude));
			printf("Point ESCAPES after %d iterations\n", i);
			printf("This point is NOT in the Mandelbrot set.\n");
			printf("In our rendering, this would be colored based on %d iterations.\n", i);
			return;
		}
		
		/* Print current iteration info */
		printf("Iteration %d: z = ", i);
		print_complex(z);
		printf(" (|z| = %.6f)\n", sqrt(magnitude));
		
		/* Calculate z² + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		
		i++;
	}
	
	/* If we reach max iterations, the point is likely in the set */
	printf("\nReached maximum iterations (%d)\n", max_iterations);
	printf("Point does NOT escape after %d iterations\n", max_iterations);
	printf("This point is likely IN the Mandelbrot set.\n");
	printf("In our rendering, this would be colored black.\n");
}

/* Main function */
int main(int argc, char **argv)
{
	t_complex	c;
	int			max_iterations;
	
	/* Set default values */
	c.real = 0.0;
	c.imag = 0.0;
	max_iterations = 20;
	
	/* Parse command line arguments */
	if (argc >= 3)
	{
		c.real = atof(argv[1]);
		c.imag = atof(argv[2]);
	}
	if (argc >= 4)
		max_iterations = atoi(argv[3]);
	
	/* Run test for point inside the set (c = 0) */
	printf("\n=== EXAMPLE 1: POINT INSIDE THE SET ===\n");
	test_mandelbrot_iterations((t_complex){0.0, 0.0}, max_iterations);
	
	/* Run test for point outside but near the edge (c = -0.75 + 0.1i) */
	printf("\n=== EXAMPLE 2: POINT NEAR EDGE OF SET ===\n");
	test_mandelbrot_iterations((t_complex){-0.75, 0.1}, max_iterations);
	
	/* Run test for point far outside the set (c = 1 + 1i) */
	printf("\n=== EXAMPLE 3: POINT FAR OUTSIDE THE SET ===\n");
	test_mandelbrot_iterations((t_complex){1.0, 1.0}, max_iterations);
	
	/* Run test for user-specified point */
	if (argc >= 3)
	{
		printf("\n=== USER-DEFINED POINT TEST ===\n");
		test_mandelbrot_iterations(c, max_iterations);
	}
	
	return (0);
}

