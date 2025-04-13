/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:12:00 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 02:23:35 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/**
 * @brief Display error message and exit program
 * 
 * @param message The error message to display
 */
void	error_exit(char *message)
{
	printf("%s\n", message);
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
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit(exit_code);
}

/**
 * @brief Print usage instructions and exit the program
 * 
 * This function displays information about how to use the program,
 * including available fractal types and required parameters.
 */
void	print_usage(void)
{
	printf("Usage: ./fractol [fractal_type] [parameters]\n\n");
	printf("Available fractal types:\n");
	printf("  mandelbrot : The Mandelbrot set\n");
	printf("  julia      : The Julia set (requires 2 parameters)\n\n");
	printf("Examples:\n");
	printf("  ./fractol mandelbrot\n");
	printf("  ./fractol julia -0.7 0.27015\n");
	exit(0);
}
