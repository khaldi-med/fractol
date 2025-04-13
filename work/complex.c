/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:34 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 16:27:57 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* Calculate iterations for a point in the Mandelbrot set */
int	mandelbrot_iterations(t_complex c, int max_iterations)
{
	t_complex	z;
	double		temp;
	int			i;

	z.real = 0.0;
	z.imag = 0.0;
	i = 0;
	while (i < max_iterations)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

/* Calculate iterations for a point in the Julia set */
int	julia_iterations(t_complex z, t_complex c, int max_iterations)
{
	double	temp;
	int		i;

	i = 0;
	while (i < max_iterations)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

