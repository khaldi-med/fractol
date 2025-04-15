/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:36:55 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/15 15:46:12 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	validate_julia_params(char *str)
{
	int	i;
	int	has_digit;
	int	has_decimal;

	i = 0;
	has_digit = 0;
	has_decimal = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else if (str[i] == '.' && !has_decimal)
			has_decimal = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}

static void	handle_julia(char **av, t_fractal *fractal)
{
	if (!validate_julia_params(av[2]) || !validate_julia_params(av[3]))
	{
		ft_putstr_fd("Error: Invalid Julia parameters.\n", 2);
		ft_putstr_fd(ERROR_MESSAGE, 2);
		exit(1);
	}
	fractal->name = av[1];
	fractal->julia_x = ft_atof(av[2]);
	fractal->julia_y = ft_atof(av[3]);
}

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
