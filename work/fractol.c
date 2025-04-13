#include "draw.h"
#include <string.h>

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
	fractol->img.addr =
		mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bits_per_pixel,
				&fractol->img.line_length, &fractol->img.endian);
}

/* Set default parameters for the fractal */
void	set_default_params(t_fractol *fractol)
{
	double	aspect_ratio;
	double	height_range;
	double	width_range;
	double	mid_real;

	/* Calculate aspect ratio */
	aspect_ratio = (double)WIDTH / HEIGHT;
	/* Set complex plane boundaries based on fractal type */
	if (fractol->fractal_type == MANDELBROT)
	{
		/* Mandelbrot set viewing window */
		fractol->min.real = -2.0;
		fractol->min.imag = -1.5;
		fractol->max.real = 1.0;
		fractol->max.imag = 1.5;
		/* Adjust width based on aspect ratio to maintain proportions */
		height_range = fractol->max.imag - fractol->min.imag;
		width_range = height_range * aspect_ratio;
		/* Center the view horizontally */
		mid_real = (fractol->min.real + fractol->max.real) / 2.0;
		fractol->min.real = mid_real - width_range / 2.0;
		fractol->max.real = mid_real + width_range / 2.0;
	}
	/* Set default Julia set complex parameter */
	if (fractol->fractal_type == JULIA)
	{
		/* These parameters create a visually striking Julia set */
		fractol->julia_c.real = -0.4;
		fractol->julia_c.imag = 0.6;
		/*
     * Other interesting Julia sets to try:
     * c = -0.7 + 0.27015i  (Dendrite fractal)
     * c = -0.8 + 0.156i    (Douady's rabbit fractal)
     * c = -0.1 + 0.8i      (Dragon-like fractal)
     * c = 0.285 + 0.01i    (San Marco fractal)
     * c = -0.835 - 0.2321i (Siegel disk fractal)
     */
	}
	/* Initialize other parameters */
	fractol->max_iterations = MAX_ITERATIONS;
	fractol->color_scheme = COLOR_SCHEME_1;
	fractol->julia_mouse_track = 0;
	/* Set initial zoom and movement */
	if (fractol->fractal_type == JULIA)
	{
		/*
     * Julia set initial viewing parameters
     * Zoom of 0.8 provides a good balance between:
     * - Showing the complete set (contained within a circle of radius 2)
     * - Maintaining enough detail to see the fractal structure
     * - Providing room to zoom out if needed
     */
		fractol->zoom = 0.8;
		/*
     * Start with perfect centering at the origin
     * Julia sets are always centered at (0,0)
     */
		fractol->move_x = 0.0;
		fractol->move_y = 0.0;
	}
	else /* MANDELBROT */
	{
		fractol->zoom = 1.0;
		fractol->move_x = 0.0;
		fractol->move_y = 0.0;
	}
}

/* Parse command line arguments and set the fractal type */
void	parse_args(int argc, char **argv, t_fractol *fractol)
{
	if (argc < 2)
		error_exit(ERROR_ARGS);
	if (strcmp(argv[1], "mandelbrot") == 0)
		fractol->fractal_type = MANDELBROT;
	else if (strcmp(argv[1], "julia") == 0)
	{
		fractol->fractal_type = JULIA;
		if (argc >= 4)
		{
			fractol->julia_c.real = atof(argv[2]);
			fractol->julia_c.imag = atof(argv[3]);
		}
	}
	else
		error_exit(ERROR_ARGS);
}

/* Print program usage instructions */
void	print_usage(void)
{
	printf("Usage: ./fractol [fractal_type] [parameters]\n\n");
	printf("Available fractal types:\n");
	printf("  mandelbrot    : Render the Mandelbrot set\n");
	printf("  julia [re] [im]: Render the Julia set with optional parameters\n");
	printf("                   Default: re=-0.7, im=0.27015\n\n");
	printf("Controls:\n");
	printf("  Arrow keys    : Move the view\n");
	printf("  Mouse wheel   : Zoom in/out\n");
	printf("  +/-          : Increase/decrease iterations\n");
	printf("  C            : Cycle color schemes\n");
	printf("  R            : Reset view\n");
	printf("  ESC          : Exit program\n");
	exit(0);
}

/* Main function */
int	main(int argc, char **argv)
{
	t_fractol	fractol;
	char		window_title[50];

	if (argc == 1 || (argc == 2 && strcmp(argv[1], "--help") == 0))
		print_usage();
	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		error_exit(ERROR_MLX);
	parse_args(argc, argv, &fractol);
	window_title[50] = "Fractol - ";
	if (fractol.fractal_type == MANDELBROT)
		strcat(window_title, "Mandelbrot");
	else
		strcat(window_title, "Julia");
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, window_title);
	if (!fractol.win)
	{
		mlx_destroy_display(fractol.mlx);
		free(fractol.mlx);
		error_exit(ERROR_WINDOW);
	}
	init_image(&fractol);
	set_default_params(&fractol);
	/* Set up event handlers before initial render */
	mlx_hook(fractol.win, KEY_PRESS, 0, handle_key, &fractol);
	mlx_hook(fractol.win, CLIENT_EXIT, 0, close_window, &fractol);
	mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
	mlx_hook(fractol.win, MOUSE_MOVE, 0, handle_mouse_move, &fractol);
	/* Perform initial render and force update */
	render_fractol(&fractol);
	mlx_do_sync(fractol.mlx);
	/* Put image to window again to ensure it's displayed */
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.img.img_ptr, 0,
			0);
	mlx_do_sync(fractol.mlx);
	/* Enter the main event loop */
	printf("Rendering %s fractal... Window should appear shortly.\n",
			fractol.fractal_type == MANDELBROT ? "Mandelbrot" : "Julia");
	mlx_loop(fractol.mlx);
	/* This point is never reached due to mlx_loop, but good practice */
	return (0);
}
