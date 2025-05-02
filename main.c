/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:36:55 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/17 22:50:49 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	start_fractal(t_fractal *fractal)
{
	fractal_init(fractal);
	fractal_render(fractal);
	mlx_loop(fractal->mlx_connection);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		fractal.name = av[1];
		start_fractal(&fractal);
	}
	else if (ac == 4 && !ft_strncmp(av[1], "julia", 5))
	{
		handle_julia(av, &fractal);
		start_fractal(&fractal);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, 2);
		return (1);
	}
	return (0);
}
