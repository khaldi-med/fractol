
#include "../fractol.h"

int	ft_key_hook(int keycode, void *param)
{
	t_fractol	*fractol;

	fractol = param;
	(void)fractol;
	if (keycode == 53 || keycode == 12)
		exit(0);
	return (0);
}
