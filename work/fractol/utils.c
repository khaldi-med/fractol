/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:28:15 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/14 00:45:32 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [parameters]\n\n");
	ft_printf("Available fractal types:\n");
	ft_printf("  mandelbrot    : Render the Mandelbrot set\n");
	ft_printf("  julia [re] [im]: Render the Julia set with optional parameters\n");
}

void	error_exit(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

void	parse_args(int argc, char **argv, t_fractal *fractal)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fractal->fractal_type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		fractal->fractal_type = JULIA;
		if (argc >= 4)
		{
			fractal->julia_c.real = ft_atof(argv[2]);
			fractal->julia_c.imag = ft_atof(argv[3]);
		}
	}
	else
		error_exit(ERROR_ARGS);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0.0;
	decimal = 0.0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		decimal = 0.1;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i++] - '0') * decimal;
			decimal *= 0.1;
		}
	}
	return (result * sign);
}
