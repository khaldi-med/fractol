
#include "../fractol.h"

void	ft_pre_cal(t_fractol *fractol, int x, int y)
{
	fractol->var.a = ft_map(x, fractol->ox - fractol->zoom, fractol->ox
			+ fractol->zoom);
	fractol->var.b = ft_map(y, fractol->oy - fractol->zoom, fractol->oy
			+ fractol->zoom);
	if (!fractol->julia)
	{
		fractol->var.a_r = fractol->var.a;
		fractol->var.b_r = fractol->var.b;
	}
	fractol->var.num_iteration = 0;
}

void	ft_calculater(t_fractol *fractol)
{
	while (fractol->var.num_iteration < fractol->max_iteration)
	{
		fractol->var.bb = 2 * fractol->var.a * fractol->var.b;
		fractol->var.aa = fractol->var.a * fractol->var.a - fractol->var.b
			* fractol->var.b;
		fractol->var.a = fractol->var.aa + fractol->var.a_r;
		fractol->var.b = fractol->var.bb + fractol->var.b_r;
		fractol->var.num_iteration++;
		if (fractol->var.a * fractol->var.a + fractol->var.b
			* fractol->var.b > 4)
			break ;
	}
}

void	ft_mlx_pixel_put(t_fractol fractol, int x, int y, int color)
{
	char	*pixel;

	pixel = fractol.image.pixels_ptr + (y * fractol.image.line_len + x
			* (fractol.image.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	ft_draw(t_fractol fractol)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_pre_cal(&fractol, x, y);
			ft_calculater(&fractol);
			color = fractol.var.num_iteration * fractol.color;
			if (fractol.var.num_iteration == fractol.max_iteration)
				color = 0;
			ft_mlx_pixel_put(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_clear_window(fractol.cnx, fractol.window);
	mlx_put_image_to_window(fractol.cnx, fractol.window, fractol.image.img_ptr,
		0, 0);
}
