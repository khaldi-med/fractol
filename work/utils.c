/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:34 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 16:27:57 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* Reset fractal view to default parameters */
void	reset_view(t_fractol *fractol)
{
	set_default_params(fractol);
}

/* Change the number of iterations for fractal calculation */
void	change_iterations(t_fractol *fractol, int increase)
{
	if (increase)
		fractol->max_iterations += 10;
	else if (fractol->max_iterations > 10)
		fractol->max_iterations -= 10;
}
