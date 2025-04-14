/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:58:59 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/14 00:45:06 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	main(int ac, char **av)
{
	t_fractal fractal;
	
	if (ac > 2)
	{
		parse_args(ac, av, &fractal);

		// print usage
		init_window(&fractal);
		//fractol_render(&fractal);
		mlx_loop(fractal.mlx);
	}
	else
	{
		print_usage();
		exit(0);
	}
}
