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

	range_real = fractol->max.real - fractol->min.real;
	range_imag = fractol->max.imag - fractol->min.imag;
	result.real = fractol->min.real + (x * range_real) / WIDTH;
	result.imag = fractol->min.imag + (y * range_imag) / HEIGHT;
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
