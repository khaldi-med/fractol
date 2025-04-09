/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:11:01 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/08 18:27:21 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammed                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-08 18:09:53                      #+#    #+#             */
/*   Updated: 2025-04-08 18:09:53                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Print usage instructions and exit the program
 * 
 * This function displays information about how to use the program,
 * including available fractal types and required parameters.
 */
void	print_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [parameters]\n\n");
	ft_printf("Available fractal types:\n");
	ft_printf("  mandelbrot : The Mandelbrot set\n");
	ft_printf("  julia      : The Julia set (requires 2 parameters)\n\n");
	ft_printf("Examples:\n");
	ft_printf("  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia -0.7 0.27015\n");
	exit(0);
}

/**
 * @brief Display error message and exit program
 * 
 * @param message The error message to display
 */
void	error_exit(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

/**
 * @brief Clean up resources and exit the program
 * 
 * @param fractol Pointer to the main fractol structure
 * @param exit_code Exit code to return
 */
void	clean_exit(t_fractol *fractol, int exit_code)
{
	if (fractol->img.img_ptr)
		mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	exit(exit_code);
}

/**
 * @brief Parse command line arguments
 * 
 * This function reads command-line arguments and sets
 * the fractal type and parameters accordingly.
 * 
 * @param fractol Pointer to the main fractol structure
 * @param argc Argument count
 * @param argv Argument values
 * @return int 1 on success, 0 on failure
 */
/**
 * @brief Case-insensitive string comparison
 * 
 * @param s1 First string
 * @param s2 Second string
 * @return int 0 if equal, non-zero otherwise
 */
int	ft_strcasecmp(const char *s1, const char *s2)
{
	unsigned char	u1;
	unsigned char	u2;

	while (*s1 && *s2)
	{
		u1 = (unsigned char)*s1++;
		u2 = (unsigned char)*s2++;
		if (u1 >= 'A' && u1 <= 'Z')
			u1 += 32;
		if (u2 >= 'A' && u2 <= 'Z')
			u2 += 32;
		if (u1 != u2)
			return (u1 - u2);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * @brief Parse command line arguments
 * 
 * This function reads command-line arguments and sets
 * the fractal type and parameters accordingly.
 * 
 * @param fractol Pointer to the main fractol structure
 * @param argc Argument count
 * @param argv Argument values
 * @return int 1 on success, 0 on failure
 */
int	parse_args(t_fractol *fractol, int argc, char **argv)
{
	if (argc < 2)
		return (0);
	
	// Handle Mandelbrot fractal
	if (ft_strcasecmp(argv[1], "mandelbrot") == 0)
	{
		fractol->fractal_type = MANDELBROT;
		return (1);
	}
	// Handle Julia fractal
	else if (ft_strcasecmp(argv[1], "julia") == 0)
	{
		fractol->fractal_type = JULIA;
		fractol->julia_mouse_track = 0;
		
		// Handle optional Julia parameters
		if (argc >= 4)
		{
			if (!is_valid_param(argv[2]) || !is_valid_param(argv[3]))
			{
				ft_printf("Error: Invalid Julia parameters. Must be valid numbers.\n");
				return (0);
			}
			
			fractol->julia_c.real = ft_atof(argv[2]);
			fractol->julia_c.imag = ft_atof(argv[3]);
		}
		else
		{
			// Default Julia parameters if not provided
			fractol->julia_c.real = -0.7;
			fractol->julia_c.imag = 0.27015;
		}
		return (1);
	}
	
	// Invalid fractal type
	return (0);
}

/**
 * @brief Set default parameters for the fractal
 * 
 * Initialize fractal viewing parameters to default values
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	set_default_params(t_fractol *fractol)
{
	fractol->zoom = 1.0;
	fractol->move_x = 0.0;
	fractol->move_y = 0.0;
	fractol->max_iterations = MAX_ITERATIONS;
	fractol->color_scheme = COLOR_SCHEME_1;
	
	// Set default complex plane coordinates
	if (fractol->fractal_type == MANDELBROT)
	{
		fractol->min.real = -2.0;
		fractol->max.real = 1.0;
		fractol->min.imag = -1.5;
		fractol->max.imag = 1.5;
	}
	else if (fractol->fractal_type == JULIA)
	{
		fractol->min.real = -2.0;
		fractol->max.real = 2.0;
		fractol->min.imag = -2.0;
		fractol->max.imag = 2.0;
	}
}

/**
 * @brief Initialize the MLX image
 * 
 * Create and setup the image that will be used for rendering
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	init_image(t_fractol *fractol)
{
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (fractol->img.img_ptr == NULL)
		error_exit(ERROR_IMAGE);
	
	fractol->img.addr = mlx_get_data_addr(
		fractol->img.img_ptr,
		&fractol->img.bits_per_pixel,
		&fractol->img.line_length,
		&fractol->img.endian
	);
}

/**
 * @brief Initialize the MLX window
 * 
 * Create the window with appropriate title based on fractal type
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	init_window(t_fractol *fractol)
{
	char	*title;

	if (fractol->fractal_type == MANDELBROT)
		title = "Fractol - Mandelbrot Set";
	else if (fractol->fractal_type == JULIA)
		title = "Fractol - Julia Set";
	else
		title = "Fractol";
	
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, title);
	if (fractol->win == NULL)
		error_exit(ERROR_WINDOW);
}

/**
 * @brief Handle closing the window
 * 
 * @param fractol Pointer to the main fractol structure
 * @return int Always returns 0
 */
int	close_window(t_fractol *fractol)
{
	clean_exit(fractol, 0);
	return (0);
}

/**
 * @brief Initialize the fractol program
 * 
 * Main initialization function that sets up MLX, 
 * creates window and image, and sets default parameters
 * 
 * @param fractol Pointer to the main fractol structure
 * @param argc Argument count
 * @param argv Argument values
 * @return int 1 on success, 0 on failure
 */
int	init_fractol(t_fractol *fractol, int argc, char **argv)
{
	// Parse command line arguments
	if (!parse_args(fractol, argc, argv))
		return (0);
	
	// Initialize MLX
	fractol->mlx = mlx_init();
	if (fractol->mlx == NULL)
		error_exit(ERROR_MLX);
	
	// Initialize window and image
	init_window(fractol);
	init_image(fractol);
	
	// Set default parameters
	set_default_params(fractol);
	
	return (1);
}

/**
 * @brief Main program entry point
 * 
 * @param argc Argument count
 * @param argv Argument values
 * @return int Program exit code
 */
int	main(int argc, char **argv)
{
	t_fractol	fractol;

	// Zero out the structure
	ft_bzero(&fractol, sizeof(t_fractol));
	
	// Initialize the program
	if (!init_fractol(&fractol, argc, argv))
	{
		print_usage();
		return (0);
	}
	
	// Setup event hooks
	mlx_hook(fractol.win, KEY_PRESS, 0, handle_key, &fractol);
	mlx_mouse_hook(fractol.win, handle_mouse, &fractol);  // Use mlx_mouse_hook for mouse buttons and scroll
	mlx_hook(fractol.win, MOUSE_MOVE, 0, handle_mouse_move, &fractol);
	mlx_hook(fractol.win, CLIENT_EXIT, 0, close_window, &fractol);
	
	// Render the initial fractal
	render_fractol(&fractol);
	
	// Start the main loop
	mlx_loop(fractol.mlx);
	
	return (0);
}
