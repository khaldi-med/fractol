/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:38:00 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 01:38:00 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * The Mandelbrot set is defined by the formula: z = z² + c
 * where:
 * - z is a complex number that starts at 0+0i
 * - c is a complex number representing a point in the complex plane
 *
 * For each point c:
 * 1. Initialize z = 0+0i
 * 2. Compute z = z² + c repeatedly
 * 3. If |z| stays less than 2 after many iterations, c is in the Mandelbrot set
 * 4. If |z| exceeds 2, c is not in the set, and we color it based on how quickly it escaped
 */

/*
 * Calculate the number of iterations for a point c in the Mandelbrot set
 * Returns the number of iterations before |z| exceeds 2, or max_iterations
 */
int	mandelbrot_iterations(t_complex c, int max_iterations)
{
	t_complex	z;
	t_complex	z_squared;
	int			iterations;
	double		temp;

	z.real = 0.0;
	z.imag = 0.0;
	iterations = 0;

	/* 
	 * Execute the Mandelbrot algorithm: z = z² + c
	 * For a point to be in the Mandelbrot set, |z| must stay <= 2
	 * We use |z|² <= 4 for efficiency (avoiding square root)
	 */
	while (iterations < max_iterations)
	{
		/* Calculate z² */
		z_squared.real = (z.real * z.real) - (z.imag * z.imag);
		z_squared.imag = 2 * z.real * z.imag;

		/* Add c to get z = z² + c */
		z.real = z_squared.real + c.real;
		z.imag = z_squared.imag + c.imag;

		/* 
		 * Check if |z| > 2
		 * We calculate |z|² = real² + imag²
		 * If |z|² > 4, then |z| > 2
		 */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break;

		iterations++;
	}

	return (iterations);
}

/*
 * Convert pixel coordinates (x, y) to complex plane coordinates
 * The complex plane is typically mapped as:
 * - x-axis: real component (usually from -2.5 to 1.0)
 * - y-axis: imaginary component (usually from -1.0 to 1.0)
 */
t_complex	pixel_to_complex(int x, int y, t_fractol *fractol)
{
	t_complex	c;
	double		range_real;
	double		range_imag;

	/* Calculate the range of the complex plane we're viewing */
	range_real = fractol->max.real - fractol->min.real;
	range_imag = fractol->max.imag - fractol->min.imag;

	/* 
	 * Map pixel coordinates to complex plane:
	 * - x=0 maps to min.real, x=WIDTH maps to max.real
	 * - y=0 maps to max.imag, y=HEIGHT maps to min.imag (y-axis is inverted in screen coordinates)
	 * Also apply zoom and movement factors
	 */
	c.real = fractol->min.real + ((double)x / WIDTH) * range_real;
	c.imag = fractol->max.imag - ((double)y / HEIGHT) * range_imag;

	/* Apply zoom (centered around current view) */
	if (fractol->zoom != 1.0)
	{
		c.real = fractol->min.real + (c.real - fractol->min.real) / fractol->zoom;
		c.imag = fractol->max.imag - (fractol->max.imag - c.imag) / fractol->zoom;
	}

	/* Apply movement offsets */
	c.real += fractol->move_x;
	c.imag += fractol->move_y;

	return (c);
}

/*
 * Create a color based on the number of iterations
 * This function maps iteration counts to colors
 */
int	create_fractal_color(int iterations, int max_iterations, int color_scheme)
{
	double	t;
	int		r;
	int		g;
	int		b;

	/* If the point is in the Mandelbrot set (didn't escape), color it black */
	if (iterations == max_iterations)
		return (0x000000);

	/* Normalize iterations to range [0, 1] */
	t = (double)iterations / (double)max_iterations;

	/* Different color schemes */
	if (color_scheme == COLOR_SCHEME_1)
	{
		/* Blue-purple color scheme */
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (color_scheme == COLOR_SCHEME_2)
	{
		/* Fire color scheme */
		r = (int)(255 * t);
		g = (int)(128 * t * t);
		b = (int)(64 * t * t * t);
	}
	else /* COLOR_SCHEME_3 */
	{
		/* Grayscale */
		r = g = b = (int)(255 * t);
	}

	/* Combine RGB components into a single color value */
	return ((r << 16) | (g << 8) | b);
}

/*
 * Render the Mandelbrot fractal to the image
 */
void	render_mandelbrot(t_fractol *fractol)
{
	int			x;
	int			y;
	int			iterations;
	int			color;
	t_complex	c;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			/* Convert pixel coordinates to a point in the complex plane */
			c = pixel_to_complex(x, y, fractol);

			/* Calculate how many iterations this point takes to escape */
			iterations = mandelbrot_iterations(c, fractol->max_iterations);

			/* Map the iteration count to a color */
			color = create_fractal_color(iterations, fractol->max_iterations, fractol->color_scheme);

			/* Draw the pixel in the image */
			draw_pixel(&fractol->img, x, y, color);

			x++;
		}
		y++;
	}
}
