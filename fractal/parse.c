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
