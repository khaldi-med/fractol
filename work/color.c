#include "draw.h"

/* Create blue to white color scheme */
static int	create_color_scheme1(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (r << 16 | g << 8 | b);
}

/* Create red to yellow color scheme */
static int	create_color_scheme2(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255);
	g = (int)(t * t * 255);
	b = (int)(t * 100);
	return (r << 16 | g << 8 | b);
}

/* Create purple to green color scheme */
static int	create_color_scheme3(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(9 * t * (1 - t) * (1 - t) * (1 - t) * 255);
	g = (int)(8.5 * t * t * (1 - t) * (1 - t) * 255);
	b = (int)(9 * t * t * t * (1 - t) * 255);
	return (r << 16 | g << 8 | b);
}

/* Create color based on iteration count and color scheme */
int	create_color(int iterations, int max_iterations, int color_scheme)
{
	double	t;

	if (iterations == max_iterations)
		return (0x000000);
	t = (double)iterations / max_iterations;
	if (color_scheme == COLOR_SCHEME_1)
		return (create_color_scheme1(t));
	else if (color_scheme == COLOR_SCHEME_2)
		return (create_color_scheme2(t));
	else
		return (create_color_scheme3(t));
}

/* Change to next color scheme */
void	change_color_scheme(t_fractol *fractol)
{
	fractol->color_scheme = (fractol->color_scheme % 3) + 1;
}
