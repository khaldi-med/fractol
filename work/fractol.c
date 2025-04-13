/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:34 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 16:27:57 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* Display an error message and exit the program */
void	error_exit(char *message)
{
	printf("%s\n", message);
	exit(1);
}

/* Clean up resources and exit the program */
void	clean_exit(t_fractol *fractol, int exit_code)
{
	if (fractol->img.img_ptr)
		mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit(exit_code);
}

/* Initialize image structure */
void	init_image(t_fractol *fractol)
{
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img.img_ptr)
		error_exit(ERROR_IMAGE);
	fractol->img.addr = mlx_get_data_addr(fractol->img.img_ptr,
			&fractol->img.bits_per_pixel,
			&fractol->img.line_length,
			&fractol->img.endian);
}

/* Set default parameters for the fractal */
void	set_default_params(t_fractol *fractol)
{
	fractol->min.real = -2.0;
	fractol->max.real = 1.0;
	fractol->min.imag = -1.5;
	fractol->max.imag = 1.5;
	fractol->julia_c.real = -0.7;
	fractol->julia_c.imag = 0.27015;
	fractol->max_iterations = MAX_ITERATIONS;
	fractol->color_scheme = COLOR_SCHEME_1;
	fractol->julia_mouse_track = 0;
}

/* Main function */
int	main(void)
{
	t_fractol	fractol;

	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		error_exit(ERROR_MLX);
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT,
			"Fractol - Mandelbrot");
	if (!fractol.win)
	{
		mlx_destroy_display(fractol.mlx);
		free(fractol.mlx);
		error_exit(ERROR_WINDOW);
	}
	init_image(&fractol);
	fractol.fractal_type = MANDELBROT;
	set_default_params(&fractol);
	render_fractol(&fractol);
	mlx_hook(fractol.win, KEY_PRESS, 0, handle_key, &fractol);
	mlx_hook(fractol.win, CLIENT_EXIT, 0, close_window, &fractol);
	mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
	mlx_hook(fractol.win, MOUSE_MOVE, 0, handle_mouse_move, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
