#include "./minilibx_mms_20191025_beta/mlx.h"

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

void	traingle(void)
{
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		i;
	int		j;
	int		w;
	int		k;
	int		b;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Triangle!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	i = 0;
	w = 1920;
	b = 960;
	j = w / 2;
	k = w / 2 + 1;
	while (i < 1080)
	{
		if (j > 0)
		{
			my_mlx_pixel_put(&img, j, i, 0x05FF5500);
			j--;
		}
		if (k < w)
		{
			my_mlx_pixel_put(&img, k, i, 0x055ff33);
			k++;
		}
		i++;
	}
	i = 0;
	while (i < w)
	{
		my_mlx_pixel_put(&img, i, b, 0x087965a);
		i++;
	}
	traingle();
	mlx_put_image_to_window(mlx, mlx_win, img.img, 2, 2);
	mlx_loop(mlx);
}
