#include "draw.h"

/* Function to draw a pixel at coordinates (x,y) with the specified color */
void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* Convert pixel coordinates to complex plane coordinates */
/* Calculate complex plane ranges for Mandelbrot set */
void	calculate_ranges(t_fractol *fractol, double *range_real, 
		double *range_imag)
{
	double aspect_ratio;

	/* Calculate aspect ratio */
	aspect_ratio = (double)WIDTH / HEIGHT;
	/* Calculate the range of the complex plane with zoom */
	*range_real = (fractol->max.real - fractol->min.real) / fractol->zoom;
	*range_imag = *range_real / aspect_ratio; /* Maintain aspect ratio */
}

/* Calculate view center with offsets */
void	calculate_center(t_fractol *fractol, double *center_x, double *center_y)
{
	/* Calculate the center point of the view with offsets */
	*center_x = (fractol->min.real + fractol->max.real) / 2.0
		+ fractol->move_x;
	*center_y = (fractol->min.imag + fractol->max.imag) / 2.0
		+ fractol->move_y;
}

/* Convert pixel to complex for Mandelbrot set */
t_complex	mandelbrot_to_complex(int x, int y, t_fractol *fractol)
{
	t_complex	result;
	double		range_real;
	double		range_imag;
	double		center_x;
	double		center_y;

	calculate_ranges(fractol, &range_real, &range_imag);
	calculate_center(fractol, &center_x, &center_y);

	/* Map pixel coordinates to complex plane coordinates */
	result.real = center_x - range_real / 2.0 + (x * range_real) / WIDTH;
	result.imag = center_y - range_imag / 2.0 + (y * range_imag) / HEIGHT;

	return (result);
}

/* Get minimum dimension for proper aspect ratio */
double	get_min_dimension(void)
{
	double min_dim;
	
	if (WIDTH < HEIGHT)
		min_dim = WIDTH;
	else
		min_dim = HEIGHT;
	
	return (min_dim);
}

/* Convert pixel to complex for Julia set */
t_complex	julia_to_complex(int x, int y, t_fractol *fractol)
{
	t_complex	result;
	double		min_dim;
	double		range;
	double		scaled_x;
	double		scaled_y;

	/* Determine scaling factor for perfect square in viewport */
	min_dim = get_min_dimension();
	/* Calculate the range scaled by zoom (fixed range of -2 to 2) */
	range = 4.0 / fractol->zoom;

	/* Map coordinates to square centered in viewport (-1 to 1) */
	scaled_x = (x - WIDTH / 2.0) / (min_dim / 2.0);
	scaled_y = (y - HEIGHT / 2.0) / (min_dim / 2.0);

	/* Apply range scaling and movement offset */
	result.real = scaled_x * range / 2.0 + fractol->move_x;
	result.imag = scaled_y * range / 2.0 + fractol->move_y;

	return (result);
}

/* Convert pixel coordinates to complex plane coordinates */
t_complex	pixel_to_complex(int x, int y, t_fractol *fractol)
{
	if (fractol->fractal_type == MANDELBROT)
		return (mandelbrot_to_complex(x, y, fractol));
	else /* JULIA set */
		return (julia_to_complex(x, y, fractol));
}

/* Calculate iterations and color for a single point */
static int	calculate_point(int x, int y, t_fractol *fractol)
{
	t_complex	c;
	int			iterations;

	c = pixel_to_complex(x, y, fractol);
	if (fractol->fractal_type == MANDELBROT)
		iterations = mandelbrot_iterations(c, fractol->max_iterations);
	else if (fractol->fractal_type == JULIA)
		iterations = julia_iterations(c, fractol->julia_c,
				fractol->max_iterations);
	else
		iterations = 0;
	return (
		create_color(iterations, fractol->max_iterations,
				fractol->color_scheme));
}

/* Render a single line of the fractal */
static void	render_line(t_fractol *fractol, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < WIDTH)
	{
		color = calculate_point(x, y, fractol);
		draw_pixel(&fractol->img, x, y, color);
		x++;
	}
}

/* Function to render the selected fractal */
void	render_fractol(t_fractol *fractol)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		render_line(fractol, y);
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0,
			0);
}
