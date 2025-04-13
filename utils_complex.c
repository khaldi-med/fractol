/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:34 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 16:27:57 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* Function to calculate the number of iterations for a point in the Mandelbrot set */
int	mandelbrot_iterations(t_complex c, int max_iterations)
{
	t_complex	z;
	double		temp;
	int			i;

	/* Initialize z to 0 */
	z.real = 0.0;
	z.imag = 0.0;
	i = 0;
	/* Iterate the formula z = z² + c */
	while (i < max_iterations)
	{
		/* Check if magnitude of z is greater than 2 */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		/* Calculate z² + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

/* Function to calculate Julia set iterations */
int	julia_iterations(t_complex z, t_complex c, int max_iterations)
{
	double	temp;
	int		i;

	i = 0;
	/* Iterate the formula z = z² + c */
	while (i < max_iterations)
	{
		/* Check if magnitude of z is greater than 2 */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		/* Calculate z² + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

