#include "draw.h"

/* Display an error message and exit the program */
void	error_exit(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

/* Clean up resources and exit the program */
void	clean_exit(t_fractol *fractol, int exit_code)
{
	if (fractol->img.img_ptr)
		mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	if (fractol->win)
		mlx_clear_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_clear_window(fractol->mlx, 0);
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
			&fractol->img.bits_per_pixel, &fractol->img.line_length,
			&fractol->img.endian);
}

/* Set default parameters for the fractal */
/* Adjust window based on aspect ratio */
void	adjust_window_ratio(t_fractol *fractol)
{
	double	aspect_ratio;
	double	height_range;
	double	width_range;
	double	mid_real;

	/* Calculate aspect ratio */
	aspect_ratio = (double)WIDTH / HEIGHT;
	/* Adjust width based on aspect ratio to maintain proportions */
	height_range = fractol->max.imag - fractol->min.imag;
	width_range = height_range * aspect_ratio;
	/* Center the view horizontally */
	mid_real = (fractol->min.real + fractol->max.real) / 2.0;
	fractol->min.real = mid_real - width_range / 2.0;
	fractol->max.real = mid_real + width_range / 2.0;
}

/* Set Mandelbrot-specific parameters */
void	set_mandelbrot_params(t_fractol *fractol)
{
	/* Mandelbrot set viewing window */
	fractol->min.real = -2.0;
	fractol->min.imag = -1.5;
	fractol->max.real = 1.0;
	fractol->max.imag = 1.5;
	adjust_window_ratio(fractol);
	/* Set initial zoom and movement */
	fractol->zoom = 1.0;
	fractol->move_x = 0.0;
	fractol->move_y = 0.0;
}

/* Set Julia-specific parameters */
void	set_julia_params(t_fractol *fractol)
{
	/* These parameters create a visually striking Julia set */
	fractol->julia_c.real = -0.4;
	fractol->julia_c.imag = 0.6;
	/* Set initial zoom and movement */
	fractol->zoom = 0.8;
	fractol->move_x = 0.0;
	fractol->move_y = 0.0;
}

/* Set default parameters for the fractal */
void	set_default_params(t_fractol *fractol)
{
	/* Initialize common parameters */
	fractol->max_iterations = MAX_ITERATIONS;
	fractol->color_scheme = COLOR_SCHEME_1;
	fractol->julia_mouse_track = 0;
	/* Set specific parameters based on fractal type */
	if (fractol->fractal_type == MANDELBROT)
		set_mandelbrot_params(fractol);
	else if (fractol->fractal_type == JULIA)
		set_julia_params(fractol);
}

/* Parse command line arguments and set the fractal type */
void	parse_args(int argc, char **argv, t_fractol *fractol)
{
	if (argc < 2)
		error_exit(ERROR_ARGS);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fractol->fractal_type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		fractol->fractal_type = JULIA;
		if (argc >= 4)
		{
			fractol->julia_c.real = ft_atof(argv[2]);
			fractol->julia_c.imag = ft_atof(argv[3]);
		}
	}
	else
		error_exit(ERROR_ARGS);
}

/* Print program usage instructions */
void	print_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [parameters]\n\n");
	ft_printf("Available fractal types:\n");
	ft_printf("  mandelbrot    : Render the Mandelbrot set\n");
	ft_printf("  julia [re] [im]: Render the Julia set with optional parameters\n");
	ft_printf("                   Default: re=-0.7, im=0.27015\n\n");
	ft_printf("Controls:\n");
	ft_printf("  Arrow keys    : Move the view\n");
	ft_printf("  Mouse wheel   : Zoom in/out\n");
	ft_printf("  +/-          : Increase/decrease iterations\n");
	ft_printf("  C            : Cycle color schemes\n");
	ft_printf("  R            : Reset view\n");
	ft_printf("  ESC          : Exit program\n");
	exit(0);
}
/* Create window title based on fractal type */
void	create_window_title(t_fractol *fractol, char *title)
{
	ft_strcpy(title, "Fractol - ");
	if (fractol->fractal_type == MANDELBROT)
		ft_strcat(title, "Mandelbrot");
	else
		ft_strcat(title, "Julia");
}
/* Initialize MLX and window */
void	init_window(t_fractol *fractol)
{
	char	window_title[50];

	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		error_exit(ERROR_MLX);
	create_window_title(fractol, window_title);
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, window_title);
	if (!fractol->win)
	{
		mlx_clear_window(fractol->mlx, 0);
		free(fractol->mlx);
		error_exit(ERROR_WINDOW);
	}
	init_image(fractol);
}

/* Set up all event handlers */
void	setup_events(t_fractol *fractol)
{
	mlx_hook(fractol->win, KEY_PRESS, 0, handle_key, fractol);
	mlx_hook(fractol->win, CLIENT_EXIT, 0, close_window, fractol);
	mlx_mouse_hook(fractol->win, handle_mouse, fractol);
	mlx_hook(fractol->win, MOUSE_MOVE, 0, handle_mouse_move, fractol);
}

/* Perform initial render and display */
void	setup_render(t_fractol *fractol)
{
	render_fractol(fractol);
	mlx_do_sync(fractol->mlx);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0,
		0);
	mlx_do_sync(fractol->mlx);
	if (fractol->fractal_type == MANDELBROT)
		ft_printf("Rendering Mandelbrot fractal... Window should appear shortly.\n");
	else
		ft_printf("Rendering Julia fractal... Window should appear shortly.\n");
}

/* Main function */
int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "--help") == 0))
		print_usage();
	parse_args(argc, argv, &fractol);
	init_window(&fractol);
	set_default_params(&fractol);
	setup_events(&fractol);
	setup_render(&fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
