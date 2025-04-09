/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:05:10 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/08 21:05:10 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Draw a single pixel to the image buffer
 * 
 * @param img Pointer to the image structure
 * @param x X-coordinate (horizontal position)
 * @param y Y-coordinate (vertical position)
 * @param color Color in RGB format
 */
void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	/* Check if the pixel is within bounds */
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	
	/* Calculate the address of the pixel */
	i = img->bits_per_pixel / 8;
	pixel = img->addr + (y * img->line_length + x * i);
	
	/* Set the pixel color (accounting for endianness) */
	*(unsigned int *)pixel = color;
}

/**
 * @brief Convert pixel coordinates to complex plane coordinates
 * 
 * Maps screen coordinates to the complex plane based on current view settings
 * 
 * @param x X-coordinate (horizontal position)
 * @param y Y-coordinate (vertical position)
 * @param fractol Pointer to the main fractol structure
 * @return t_complex Complex number coordinates
 */
t_complex	pixel_to_complex(int x, int y, t_fractol *fractol)
{
	t_complex	point;
	double		width;
	double		height;

	width = fractol->max.real - fractol->min.real;
	height = fractol->max.imag - fractol->min.imag;

	/* Improved precision mapping */
	point.real = fractol->min.real + ((double)x / WIDTH) * width;
	point.imag = fractol->min.imag + ((double)y / HEIGHT) * height;

	return (point);
}

/**
 * @brief Reset view to default parameters
 * 
 * Resets the view boundaries to their default values based on fractal type
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	reset_view(t_fractol *fractol)
{
	if (fractol->fractal_type == MANDELBROT)
	{
		fractol->min.real = -2.0;
		fractol->max.real = 1.0;
		fractol->min.imag = -1.5;
		fractol->max.imag = 1.5;
	}
	else if (fractol->fractal_type == JULIA)
	{
		fractol->min.real = -2.0;
		fractol->max.real = 2.0;
		fractol->min.imag = -2.0;
		fractol->max.imag = 2.0;
	}
	
	/* Reset other parameters */
	fractol->max_iterations = MAX_ITERATIONS;
	
	/* If it's Julia set, reset to default parameters */
	if (fractol->fractal_type == JULIA)
	{
		fractol->julia_c.real = -0.7;
		fractol->julia_c.imag = 0.27015;
		fractol->julia_mouse_track = 0;
	}
	
	render_fractol(fractol);
}

/**
 * @brief Create a color based on iteration count
 * 
 * Generates a color using a smooth interpolation algorithm
 * to create visually pleasing color transitions.
 * 
 * @param iterations Number of iterations for current pixel
 * @param max_iterations Maximum iterations limit
 * @param color_scheme Selected color scheme (1-3)
 * @return int RGB color value
 */
int	create_color(int iterations, int max_iterations, int color_scheme)
{
	double	t;
	int		r;
	int		g;
	int		b;
	
	/* If we reached max iterations, return black */
	if (iterations == max_iterations)
		return (0x000000);
	
	/* Calculate a normalized value between 0 and 1 */
	t = (double)iterations / (double)max_iterations;
	
	/* Apply different color schemes */
	if (color_scheme == COLOR_SCHEME_1)
	{
		/* Vibrant blue to orange scheme */
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (color_scheme == COLOR_SCHEME_2)
	{
		/* Purple to yellow scheme */
		r = (int)(9 * (1 - t) * t * t * 255);
		g = (int)(15 * (1 - t) * t * t * t * 255);
		b = (int)(8.5 * (1 - t) * t * 255);
	}
	else
	{
		/* Green to blue gradient */
		r = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		g = (int)(9 * (1 - t) * t * t * 255);
		b = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	}
	
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Calculate iterations for Mandelbrot set
 * 
 * Implements the Mandelbrot set algorithm, which tests if a point
 * in the complex plane belongs to the set by iterating the function
 * f(z) = z² + c starting with z = 0.
 * 
 * @param c Complex point to test
 * @param max_iterations Maximum iteration limit
 * @return int Number of iterations before divergence, or max_iterations
 */
int	mandelbrot_iterations(t_complex c, int max_iterations)
{
	t_complex	z;
	int			iterations;
	double		temp;
	
	z.real = 0.0;
	z.imag = 0.0;
	iterations = 0;
	
	/* Test if the point escapes to infinity */
	while (iterations < max_iterations)
	{
		/* Check if magnitude exceeds 2 (diverges) */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		
		/* Calculate next value: z = z² + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		
		iterations++;
	}
	
	return (iterations);
}

/**
 * @brief Calculate iterations for Julia set
 * 
 * Implements the Julia set algorithm, which tests if a point
 * in the complex plane belongs to the set by iterating the function
 * f(z) = z² + c where c is a constant parameter.
 * 
 * @param z Starting complex point (the pixel coordinate)
 * @param c The Julia set parameter (constant)
 * @param max_iterations Maximum iteration limit
 * @return int Number of iterations before divergence, or max_iterations
 */
int	julia_iterations(t_complex z, t_complex c, int max_iterations)
{
	int			iterations;
	double		temp;
	
	iterations = 0;
	
	/* Test if the point escapes to infinity */
	while (iterations < max_iterations)
	{
		/* Check if magnitude exceeds 2 (diverges) */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		
		/* Calculate next value: z = z² + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		
		iterations++;
	}
	
	return (iterations);
}

/**
 * @brief Main rendering function
 * 
 * Calculates and draws the fractal by iterating through each pixel,
 * converting it to complex plane coordinates, calculating the appropriate
 * fractal value, and setting the pixel color.
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	render_fractol(t_fractol *fractol)
{
	int			x;
	int			y;
	int			iterations;
	int			color;
	t_complex	c;
	
	y = 0;
	/* Loop through every pixel in the window */
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			/* Convert pixel coordinate to complex plane coordinate */
			c = pixel_to_complex(x, y, fractol);
			
			/* Calculate iterations based on fractal type */
			if (fractol->fractal_type == MANDELBROT)
				iterations = mandelbrot_iterations(c, fractol->max_iterations);
			else if (fractol->fractal_type == JULIA)
				iterations = julia_iterations(c, fractol->julia_c, 
					fractol->max_iterations);
			else
				iterations = 0;
			
			/* Create color based on iterations */
			color = create_color(iterations, fractol->max_iterations, 
				fractol->color_scheme);
			
			/* Draw pixel with appropriate color */
			draw_pixel(&fractol->img, x, y, color);
			
			x++;
		}
		y++;
	}
	
	/* Update display */
	mlx_put_image_to_window(fractol->mlx, fractol->win, 
		fractol->img.img_ptr, 0, 0);
}

