/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:34:09 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/15 14:47:11 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <math.h>

# define WIDTH 800
# define HEIGHT 800

# define Button4 4
# define Button5 5
# define NoExpose 53

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define MAGENTA_BURST 0xFF00FF
# define LIME_SHOCK 0xCCFF00
# define NEON_ORANGE 0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM 0x33CCCC
# define HOT_PINK 0xFF66B2
# define ELECTRIC_BLUE 0x0066FF
# define LAVA_RED 0xFF3300

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
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}			t_fractal;

t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

double		map(double unscaled_num, double new_min, double new_max,
				double old_min, double old_max);
double		ft_atof(const char *str);
void		fractal_init(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
int			ft_isspace(int c);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, void *param);
int			key_handler(int keysym, t_fractal *fractal);
int			mouse_move_handler(int x, int y, void *param);

#endif
