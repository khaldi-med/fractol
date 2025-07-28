
#include "fractal.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	free(fractal->mlx_connection);
	exit(0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == ESC_KEY)
		close_handler(fractal);
	else if (keysym == PLUS_KEY)
	{
		fractal->zoom *= 1.2;
		fractal_render(fractal);
	}
	else if (keysym == MINUS_KEY)
	{
		fractal->zoom *= 0.8;
		fractal_render(fractal);
	}
	else if (keysym == LEFT_KEY)
	{
		fractal->shift_x -= 0.1 / fractal->zoom;
		fractal_render(fractal);
	}
	else if (keysym == RIGHT_KEY)
	{
		fractal->shift_x += 0.1 / fractal->zoom;
		fractal_render(fractal);
	}
	else if (keysym == UP_KEY)
	{
		fractal->shift_y -= 0.1 / fractal->zoom;
		fractal_render(fractal);
	}
	else if (keysym == DOWN_KEY)
	{
		fractal->shift_y += 0.1 / fractal->zoom;
		fractal_render(fractal);
	}
	return (0);
}

int	mouse_handler(int button, int x, int y, void *param)
{
	t_fractal	*fractal;
	double		mouse_re, mouse_im;
	double		zoom_factor;

	fractal = (t_fractal *)param;
	
	// Convert mouse coordinates to complex plane
	mouse_re = (((double)x / WIDTH) - 0.5) * 4.0 / fractal->zoom + fractal->shift_x;
	mouse_im = (((double)y / HEIGHT) - 0.5) * 4.0 / fractal->zoom + fractal->shift_y;
	
	if (button == Button5) // Scroll down - zoom out
	{
		zoom_factor = 0.8;
		fractal->zoom *= zoom_factor;
		// Adjust shift to keep mouse point centered
		fractal->shift_x = mouse_re - (mouse_re - fractal->shift_x) * zoom_factor;
		fractal->shift_y = mouse_im - (mouse_im - fractal->shift_y) * zoom_factor;
	}
	else if (button == Button4) // Scroll up - zoom in
	{
		zoom_factor = 1.25;
		fractal->zoom *= zoom_factor;
		// Adjust shift to keep mouse point centered
		fractal->shift_x = mouse_re - (mouse_re - fractal->shift_x) * zoom_factor;
		fractal->shift_y = mouse_im - (mouse_im - fractal->shift_y) * zoom_factor;
	}
	fractal_render(fractal);
	return (0);
}
