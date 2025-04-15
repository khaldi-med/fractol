/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:18:54 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/15 01:24:02 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	free(fractal->mlx_connection);
	exit(0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == 53)
		close_handler(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, void *param)
{
	t_fractal	*fractal;

	(void)x;
	(void)y;
	fractal = (t_fractal *)param;
	if (button == Button5)
	{
		fractal->zoom *= 0.9;
	}
	else if (button == Button4)
	{
		fractal->zoom *= 1.1;
	}
	fractal_render(fractal);
	return (0);
}
