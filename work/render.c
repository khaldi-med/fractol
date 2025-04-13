/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:34 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 16:27:57 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* Function to draw a pixel at coordinates (x,y) with the specified color */
void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* Convert pixel coordinates to complex plane coordinates */
t_complex	pixel_to_complex(int x, int y, t_fractol *fractol)
{
	t_complex	result;
	double		range_real;
	double		range_imag;
	double		center_x, center_y;
	double		aspect_ratio;
	
	/* Calculate aspect ratio */
	aspect_ratio = (double)WIDTH / HEIGHT;
	
	if (fractol->fractal_type == MANDELBROT)
	{
		/* Mandelbrot set coordinate mapping */
		/* Calculate the range of the complex plane with zoom */
		range_real = (fractol->max.real - fractol->min.real) / fractol->zoom;
		range_imag = range_real / aspect_ratio; /* Maintain aspect ratio */
		
		/* Calculate the center point of the view with offsets */
		center_x = (fractol->min.real + fractol->max.real) / 2.0 + fractol->move_x;
		center_y = (fractol->min.imag + fractol->max.imag) / 2.0 + fractol->move_y;
		
		/* Map pixel coordinates to complex plane coordinates */
		result.real = center_x - range_real / 2.0 + (x * range_real) / WIDTH;
		result.imag = center_y - range_imag / 2.0 + (y * range_imag) / HEIGHT;
	}
	else /* JULIA set */
	{
		/* 
		 * Julia set coordinate mapping with perfect square aspect ratio
		 * Always use a range of -2 to 2 scaled by zoom
		 */
		
		/* Determine scaling factor to make a perfect square in the viewport */
		double min_dim = (WIDTH < HEIGHT) ? WIDTH : HEIGHT;
		
		/* Calculate the range scaled by zoom */
		double range = 4.0 / fractol->zoom;  /* Fixed range of -2 to 2 */
		
		/* 
		 * Map coordinates to a square centered in the viewport
		 * This ensures we maintain a perfect aspect ratio
		 * regardless of window dimensions
		 */
		double scaled_x = (x - WIDTH / 2.0) / (min_dim / 2.0);  /* Range: -1 to 1 */
		double scaled_y = (y - HEIGHT / 2.0) / (min_dim / 2.0); /* Range: -1 to 1 */
		
		/* Apply range scaling and movement offset */
		result.real = scaled_x * range / 2.0 + fractol->move_x;
		result.imag = scaled_y * range / 2.0 + fractol->move_y;
	}
	
	return (result);
}

/* Calculate iterations and color for a single point */
static int	calculate_point(int x, int y, t_fractol *fractol)
{
	t_complex	c;
	int			iterations;

	c = pixel_to_complex(x, y, fractol);
	if (fractol->fractal_type == MANDELBROT)
		iterations = mandelbrot_iterations(c, fractol->max_iterations);
	else if (fractol->fractal_type == JULIA)
		iterations = julia_iterations(c, fractol->julia_c,
				fractol->max_iterations);
	else
		iterations = 0;
	return (create_color(iterations, fractol->max_iterations,
			fractol->color_scheme));
}

/* Render a single line of the fractal */
static void	render_line(t_fractol *fractol, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < WIDTH)
	{
		color = calculate_point(x, y, fractol);
		draw_pixel(&fractol->img, x, y, color);
		x++;
	}
}

/* Function to render the selected fractal */
void	render_fractol(t_fractol *fractol)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		render_line(fractol, y);
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img_ptr, 0, 0);
}
