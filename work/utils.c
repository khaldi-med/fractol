#include "draw.h"

/* Reset fractal view to default parameters */
void	reset_view(t_fractol *fractol)
{
	set_default_params(fractol);
}

/* Change the number of iterations for fractal calculation */
void	change_iterations(t_fractol *fractol, int increase)
{
	if (increase)
		fractol->max_iterations += 10;
	else if (fractol->max_iterations > 10)
		fractol->max_iterations -= 10;
}

/* Custom string concatenation function */
char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/* Check if character is a space */
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
			c == '\r');
}

/* Custom string to double conversion */
double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0.0;
	decimal = 0.0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		decimal = 0.1;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i++] - '0') * decimal;
			decimal *= 0.1;
		}
	}
	return (result * sign);
}
