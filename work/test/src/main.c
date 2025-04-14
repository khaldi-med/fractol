
#include "../fractol.h"

char	*ft_get_title(int number)
{
	if (number == 1)
		return ("FRACTOL - Mandelbrot by yabenman");
	else
		return ("FRACTOL - Julia by yabenman");
}

void	ft_init(t_fractol *fractol, int number)
{
	fractol->cnx = mlx_init();
	fractol->window = mlx_new_window(fractol->cnx, WIDTH, HEIGHT,
			ft_get_title(number));
	fractol->max_iteration = 100;
	fractol->ox = 0;
	fractol->oy = 0;
	fractol->zoom = 2;
	fractol->image.img_ptr = mlx_new_image(fractol->cnx, WIDTH, HEIGHT);
	fractol->image.pixels_ptr = mlx_get_data_addr(fractol->image.img_ptr,
			&fractol->image.bits_per_pixel, &fractol->image.line_len,
			&fractol->image.endian);
	fractol->color = 0x00ffd9;
	fractol->julia = (number == 2);
	fractol->var.a_r = -0.466;
	fractol->var.b_r = 0.622;
}

int	main(int ac, char **av)
{
	t_fractol	fractol;
	int			number;

	if (ac == 2)
	{
		number = ft_atoi(av[1]);
		if (number == 1 || number == 2)
		{
			ft_instructions();
			ft_init(&fractol, number);
			ft_draw(fractol);
			mlx_key_hook(fractol.window, ft_key_hook, &fractol);
			mlx_mouse_hook(fractol.window, ft_mouse_hook, &fractol);
			mlx_hook(fractol.window, 17, 0, ft_close, &fractol);
			mlx_loop(fractol.cnx);
		}
	}
	else if (ac == 4 && ft_atoi(av[1]) == 2)
	{
		julia_args(av);
	}
	write(1, "Usage:\t./fractol [1, 2]\n\n", 28);
	write(1, "[1]:\tMandelbrot\n[2]:\tJulia\n", 47);
	return (0);
}

void	julia_args(char **av)
{
	t_fractol	fractol;

	ft_instructions();
	ft_init(&fractol, 2);
	fractol.var.a_r = ft_atof(av[2], 0);
	fractol.var.b_r = ft_atof(av[3], 0);
	ft_draw(fractol);
	mlx_key_hook(fractol.window, ft_key_hook, &fractol);
	mlx_mouse_hook(fractol.window, ft_mouse_hook, &fractol);
	mlx_hook(fractol.window, 17, 0, ft_close, &fractol);
	mlx_loop(fractol.cnx);
}
