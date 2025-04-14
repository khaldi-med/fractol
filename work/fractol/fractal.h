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

# define ERROR_MLX "Error: Failed to initialize MLX"
# define ERROR_WINDOW "Error: Failed to create window"
# define ERROR_IMAGE "Error: Failed to create image"

/* Fractal types */
# define MANDELBROT 1
# define JULIA 2

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATIONS 100

# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MOUSE_BUTTON_LEFT 1

/* Events */
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define MOUSE_PRESS 4
# define MOUSE_RELEASE 5
# define MOUSE_MOVE 6
# define CLIENT_EXIT 17

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

typedef struct s_fractal
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
}				t_fractal;

void	parse_args(int argc, char **argv, t_fractal *fractal)

void	setup_events(t_fractal *fractal);
void	error_exit(char *message);
void	init_window(t_fractal *fractal);
void	init_image(t_fractal *fractal);
void	print_usage(void);
double	ft_atof(const char *str);
void	create_window_title(t_fractal *fractal, char *title);
#endif
