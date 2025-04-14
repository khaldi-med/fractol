
#include "../fractol.h"

int	ft_atoi(char *num)
{
	int	nbr;
	int	index;

	index = -1;
	nbr = 0;
	while (num[++index])
		nbr = nbr * 10 + (num[index] - '0');
	return (nbr);
}

double	ft_map(int in, double min, double max)
{
	double	maped;

	maped = in * ((max - min) / WIDTH) + min;
	return (maped);
}

int	ft_close(t_fractol *fractol)
{
	mlx_destroy_window(fractol->cnx, fractol->window);
	exit(0);
}

void	ft_instructions(void)
{
	write(1, "####### INSTRUCTION BY YABENMAN  ########\n", 43);
	write(1, "#                                       #\n", 43);
	write(1, "# esc | q - Quit                        #\n", 43);
	write(1, "#                                       #\n", 43);
	write(1, "############## INSTRUCTION ##############\n", 43);
}

double	ft_atof(char *str, double res)
{
	int	i;
	int	sign;
	int	divider;

	i = -1;
	res = 0;
	sign = 1;
	divider = 1;
	if (str[++i] == '-')
		sign = -1;
	while (str[++i] && str[i] != '.')
		res = res * 10 + str[i] - '0';
	if (str[i++] == '.')
	{
		while (str[i])
		{
			res = res * 10 + str[i++] - '0';
			divider *= 10;
		}
	}
	return (res * sign / divider);
}
