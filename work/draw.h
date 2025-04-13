#ifndef FT_DRAW_H
# define FT_DRAW_H

/* Required libraries */
# include "../mlx/mlx.h" /* MiniLibX graphics library */
# include "./libft/libft.h" /* For libft functions */
# include "./ft_printf/ft_printf.h" /* For ft_printf functions */
# include <math.h>       /* For mathematical operations */
/* Error messages */
# define ERROR_ARGS "Error: Invalid arguments\nUsage: ./fractol [fractal_type] [parameters]"
# define ERROR_MLX "Error: Failed to initialize MLX"
# define ERROR_WINDOW "Error: Failed to create window"
# define ERROR_IMAGE "Error: Failed to create image"

/* Fractal types */
# define MANDELBROT 1
# define JULIA 2

/* Window dimensions */
# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATIONS 100 /* Default max iterations for fractal calculation */

/* Color schemes */
# define COLOR_SCHEME_1 1
# define COLOR_SCHEME_2 2
# define COLOR_SCHEME_3 3

/* Key and mouse event codes for Linux/X11 */
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_C 99  /* Change color scheme */
# define KEY_R 114 /* Reset view */
# define KEY_1 49  /* Select Mandelbrot */
# define KEY_2 50  /* Select Julia */
# define KEY_3 51  /* Select Burning Ship (bonus) */

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

/* Structures */
/* Complex number structure */
typedef struct s_complex
{
	double	real;
	double	imag;
}			t_complex;

/* Image data structure */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;
/* Main data structure */
typedef struct s_fractol
{
	void *mlx;          /* MLX pointer */
	void *win;          /* Window pointer */
	t_img img;          /* Image data */
	int fractal_type;   /* Current fractal type */
	double zoom;        /* Zoom level */
	double move_x;      /* X-axis offset */
	double move_y;      /* Y-axis offset */
	t_complex julia_c;  /* Julia set parameter */
	t_complex min;      /* Minimum coordinates in complex plane */
	t_complex max;      /* Maximum coordinates in complex plane */
	int max_iterations; /* Maximum iterations for fractal calculation */
	int color_scheme;   /* Current color scheme */
	int		julia_mouse_track;
	/* Flag to track mouse for Julia set parameters */
}			t_fractol;

/* Initialization functions */
void		error_exit(char *message);
void		clean_exit(t_fractol *fractol, int exit_code);
void		init_image(t_fractol *fractol);
void		set_default_params(t_fractol *fractol);

/* Rendering functions */
void		render_fractol(t_fractol *fractol);
void		draw_pixel(t_img *img, int x, int y, int color);
t_complex	pixel_to_complex(int x, int y, t_fractol *fractol);

/* Color functions */
int			create_color(int iterations, int max_iterations, int color_scheme);
void		change_color_scheme(t_fractol *fractol);

/* Complex calculation functions */
int			mandelbrot_iterations(t_complex c, int max_iterations);
int			julia_iterations(t_complex z, t_complex c, int max_iterations);

/* Event handling functions */
int			handle_key(int keycode, t_fractol *fractol);
void		handle_movement(int keycode, t_fractol *fractol);
int			handle_mouse(int button, int x, int y, t_fractol *fractol);
int			handle_mouse_move(int x, int y, t_fractol *fractol);
int			close_window(t_fractol *fractol);

/* Utility functions */
void		reset_view(t_fractol *fractol);
void		change_iterations(t_fractol *fractol, int increase);

/* String utility functions */
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
double		ft_atof(const char *str);
int			ft_isspace(int c);

#endif
