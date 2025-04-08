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

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_printf("Plase entre './fractol Mandelbrot' or './fractol julia a b'\n");
		exit(0);
	}
	return (0);
}
