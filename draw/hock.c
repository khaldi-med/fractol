#include "./minilibx_opengl_20191021/mlx.h"
#include <unistd.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

int	print(void)
{
	write(1, "Done!\n", 6);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 6, 0, print, &vars);
	mlx_loop(vars.mlx);
}
