/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 600
# define HEIGHT 600

typedef struct s_image
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_image;

typedef struct s_var
{
	double	a;
	double	b;
	double	aa;
	double	bb;
	double	a_r;
	double	b_r;
	int		num_iteration;
}			t_var;

typedef struct s_fractol
{
	void	*cnx;
	void	*window;
	t_image	image;
	t_var	var;
	double	zoom;
	double	ox;
	double	oy;
	int		max_iteration;
	int		color;
	int		julia;
}			t_fractol;

void		ft_instructions(void);
int			ft_close(t_fractol *fractol);
int			ft_atoi(char *num);
double		ft_map(int in, double min, double max);
void		ft_init(t_fractol *fractol, int number);
double		ft_atof(char *str, double res);
void		ft_pre_cal(t_fractol *fractol, int x, int y);
void		ft_calculater(t_fractol *fractol);
void		ft_mlx_pixel_put(t_fractol fractol, int x, int y, int color);
void		ft_draw(t_fractol fractol);
int			ft_key_hook(int keycode, void *param);
void		julia_args(char **av);
void		ft_mouse_zoom(t_fractol *fractol, int button, int x, int y);
int			ft_mouse_hook(int button, int x, int y, void *param);
#endif