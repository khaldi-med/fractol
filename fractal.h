
#ifndef FRACTOL_H
# define FRACTOL_H

/* Libraries */
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <math.h>

/* Window dimensions */
# define WIDTH 800
# define HEIGHT 800

/* Mouse buttons */
# define Button4 4
# define Button5 5
# define ESC_KEY 65307
# define PLUS_KEY 61
# define MINUS_KEY 45
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364

/* Colors */
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFF8000
# define PURPLE 0x8000FF
# define PINK 0xFF0080
# define LIME 0x80FF00
# define TURQUOISE 0x00FF80
# define VIOLET 0x8080FF
# define GOLD 0xFFD700
# define SILVER 0xC0C0C0

/* Error messages */
# define ERROR_MESSAGE                                                     \
	"Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia " \
	"<value_1> <value_2>\"\n"

/* Complex number */
typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

/* Image */
typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

/* Fractal */
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

/* Range for mapping */
typedef struct s_range
{
	double	min;
	double	max;
}			t_range;

/* Function prototypes */
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
