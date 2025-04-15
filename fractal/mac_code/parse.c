/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:37:26 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/15 02:51:19 by mohkhald         ###   ########.fr       */
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

void	handle_julia(char **av, t_fractal *fractal)
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

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static double	handle_decimal_part(const char *str, int *i)
{
	double	decimal_part;
	double	decimal_factor;

	decimal_part = 0.0;
	decimal_factor = 0.1;
	(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		decimal_part += (str[*i] - '0') * decimal_factor;
		decimal_factor *= 0.1;
		(*i)++;
	}
	return (decimal_part);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	int		i;

	result = 0.0;
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
		result += handle_decimal_part(str, &i);
	return (result * sign);
}
