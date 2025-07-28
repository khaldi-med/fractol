
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

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	get_color(int i, t_fractal *fractal)
{
	double	t;
	int		r, g, b;

	if (i == fractal->max_iterations)
		return (BLACK);
	
	// Normalize iteration count to 0-1 range
	t = (double)i / fractal->max_iterations;
	
	// Create beautiful gradient color schemes
	if (t < 0.16)
	{
		// Deep blue to cyan transition
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (t < 0.42)
	{
		// Cyan to yellow transition
		r = (int)(8.5 * (1 - t) * t * t * t * 255);
		g = (int)(17 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(0.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (t < 0.6425)
	{
		// Yellow to red transition
		r = (int)(255 * (1 - (1 - t) * (1 - t)));
		g = (int)(255 * (1 - t * t));
		b = (int)(128 * (1 - t));
	}
	else if (t < 0.8575)
	{
		// Red to magenta transition
		r = (int)(255 * (1 - 0.2 * t));
		g = (int)(32 * t);
		b = (int)(255 * t * t);
	}
	else
	{
		// Magenta to white transition
		r = (int)(255 * (0.5 + 0.5 * t));
		g = (int)(255 * t * t * t);
		b = (int)(255 * (0.8 + 0.2 * t));
	}
	
	// Ensure values are within valid range
	r = (r > 255) ? 255 : (r < 0) ? 0 : r;
	g = (g > 255) ? 255 : (g < 0) ? 0 : g;
	b = (b > 255) ? 255 : (b < 0) ? 0 : b;
	
	return (create_trgb(0, r, g, b));
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	t_range		old_range;
	t_range		new_range;

	old_range.min = 0;
	old_range.max = WIDTH;
	new_range.min = -2;
	new_range.max = 2;
	z.x = (map(x, new_range, old_range) / fractal->zoom) + fractal->shift_x;
	new_range.min = 2;
	new_range.max = -2;
	old_range.max = HEIGHT;
	z.y = (map(y, new_range, old_range) / fractal->zoom) + fractal->shift_y;
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
