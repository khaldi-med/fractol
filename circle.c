#include <math.h>
#include <mlx.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	circle(void)
{
	t_data	img;
	int		x;
	int		y;
	int		center_x;
	int		center_y;
	int		radius;
	int		dx;
	int		dy;

	center_x = 960;
	center_y = 540;
	radius = 100;
	while (i < 1080)
	{
		if
	}
	my_mlx_pixel_put(&img, x, y, 0xFFFFFF);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Triangle!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	circle();
	mlx_put_image_to_window(mlx, mlx_win, img.img, 2, 2);
	mlx_loop(mlx);
}
