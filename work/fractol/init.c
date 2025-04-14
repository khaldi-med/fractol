#include "fractal.h"

void	create_window_title(t_fractal *fractal, char *title)
{
	ft_strcpy(title, "Fractal - ");
	if (fractal->fractal_type == MANDELBROT)
		ft_strcat(title, "Mandelbrot");
	else
		ft_strcat(title, "Julia");
}

void	init_image(t_fractal *fractal)
{
	fractal->img.img_ptr = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img.img_ptr)
		error_exit(ERROR_IMAGE);
	fractal->img.addr =
		mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bits_per_pixel,
				&fractal->img.line_length, &fractal->img.endian);
}

void	setup_events(t_fractal *fractal)
{
	mlx_hook(fractal->win, KEY_PRESS, 0, handle_key, fractal);
	mlx_hook(fractal->win, CLIENT_EXIT, 0, close_window, fractal);
	mlx_mouse_hook(fractal->win, handle_mouse, fractal);
	mlx_hook(fractal->win, MOUSE_MOVE, 0, handle_mouse_move, fractal);
}

int	handle_key(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
		clean_exit(fractal, 0);
	if (keycode != KEY_ESC)
		render_fractal(fractal);
	return (0);
}

*void init_window(t_fractal *fractal)
{
	char	window_title[50];

	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		error_exit(ERROR_MLX);
	create_window_title(fractal, window_title);
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, window_title);
	if (!fractal->win)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		error_exit(ERROR_WINDOW);
	}
	init_image(fractal);
}
