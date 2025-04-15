/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:21:01 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/15 02:01:14 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
		z->x = 0;
		z->y = 0;
	}
}

static int	get_color(int i, t_fractal *fractal)
{
	if (i == fractal->max_iterations)
		return (BLACK);
	return (ELECTRIC_BLUE + (i * 10));
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.x = (map(x, -2, 2, 0, WIDTH) / fractal->zoom) + fractal->shift_x;
	z.y = (map(y, 2, -2, 0, HEIGHT) / fractal->zoom) + fractal->shift_y;
	mandel_vs_julia(&z, &c, fractal);
	i = 0;
	while (i < fractal->max_iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
			break ;
		++i;
	}
	my_pixel_put(x, y, &fractal->img, get_color(i, fractal));
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}
