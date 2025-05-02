/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:34:09 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/17 22:50:37 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>

# define WIDTH 800
# define HEIGHT 800

# define Button4 4
# define Button5 5
# define NoExpose 53

# define BLACK 0x000000
# define LIME_SHOCK 0xCCFF00

# define ERROR_MESSAGE                                                     \
	"Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia " \
	"<value_1> <value_2>\"\n"

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;

	double	escape_value;
	int		max_iterations;
	double	zoom;
	double	julia_x;
	double	julia_y;
}			t_fractal;

typedef struct s_range
{
	double	min;
	double	max;
}			t_range;

t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

double		map(double unscaled_num, t_range new_range, t_range old_range);
double		ft_atof(const char *str);

void		fractal_init(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
void		handle_julia(char **av, t_fractal *fractal);

int			ft_isspace(int c);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, void *param);
int			key_handler(int keysym, t_fractal *fractal);
int			validate_julia_params(char *str);

#endif
