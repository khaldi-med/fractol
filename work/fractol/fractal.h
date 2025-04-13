/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:22:57 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/14 00:32:13 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <math.h>

# define ERROR_ARGS "Error: Invalid arguments\nUsage: ./fractol [fractal_type] [parameters]"

typedef struct s_complex
{
	double		real;
	double		imag;
}				t_complex;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			fractal_type;
	double		zoom;
	double		move_x;
	double		move_y;
	t_complex	julia_c;
	t_complex	min;
	t_complex	max;
	int			max_iterations;
	int			color_scheme;
	int			julia_mouse_track;
}				t_fractol;

#endif
