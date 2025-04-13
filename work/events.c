#include "draw.h"

/* Handle window close event */
int	close_window(t_fractol *fractol)
{
	clean_exit(fractol, 0);
	return (0);
}

/* Handle keyboard movement keys (UP, DOWN, LEFT, RIGHT) */
/* Calculate the movement amount based on fractal type and zoom */
static double	calculate_move_amount(t_fractol *fractol)
{
	double	move_amount;
	double	window_scale;

	/* Use the smaller dimension for consistent movement */
	if (WIDTH < HEIGHT)
		window_scale = WIDTH;
	else
		window_scale = HEIGHT;
	
	/* Scale movement based on zoom level and window size */
	if (fractol->fractal_type == JULIA)
	{
		/* 4.0 is the base range (-2 to 2) */
		move_amount = (4.0 / window_scale) * (10.0 / fractol->zoom);
	}
	else /* MANDELBROT */
	{
		move_amount = 0.1 / fractol->zoom;
	}
	return (move_amount);
}

/* Handle keyboard movement keys (UP, DOWN, LEFT, RIGHT) */
static void	handle_view_keys(int keycode, t_fractol *fractol)
{
	double	move_amount;

	move_amount = calculate_move_amount(fractol);
	
	/* Apply movement with the calculated amount */
	if (keycode == KEY_UP)
		fractol->move_y -= move_amount;
	else if (keycode == KEY_DOWN)
		fractol->move_y += move_amount;
	else if (keycode == KEY_LEFT)
		fractol->move_x -= move_amount;
	else if (keycode == KEY_RIGHT)
		fractol->move_x += move_amount;
}

/* Handle key press events */
int	handle_key(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		clean_exit(fractol, 0);
	else if (keycode == KEY_R)
		reset_view(fractol);
	else if (keycode == KEY_C)
		change_color_scheme(fractol);
	else if (keycode == KEY_PLUS)
		change_iterations(fractol, 1);
	else if (keycode == KEY_MINUS)
		change_iterations(fractol, 0);
	else if (keycode >= KEY_UP && keycode <= KEY_RIGHT)
		handle_view_keys(keycode, fractol);
	if (keycode != KEY_ESC)
		render_fractol(fractol);
	return (0);
}

/* Handle mouse movement for Julia set */
/* Update Julia parameters based on mouse position */
static void	update_julia_params(int x, int y, t_fractol *fractol)
{
	double	real_range;
	double	imag_range;

	/* Map mouse coordinates to create interesting Julia sets */
	real_range = 1.5;
	imag_range = 1.5;
	fractol->julia_c.real = real_range * ((double)x / WIDTH - 0.5);
	fractol->julia_c.imag = imag_range * ((double)y / HEIGHT - 0.5);
}

/* Clamp Julia parameters to ensure interesting patterns */
static void	clamp_julia_params(t_fractol *fractol)
{
	/* Clamp values to ensure interesting patterns */
	if (fractol->julia_c.real > 0.7)
		fractol->julia_c.real = 0.7;
	if (fractol->julia_c.real < -1.5)
		fractol->julia_c.real = -1.5;
	if (fractol->julia_c.imag > 1.0)
		fractol->julia_c.imag = 1.0;
	if (fractol->julia_c.imag < -1.0)
		fractol->julia_c.imag = -1.0;
}

/* Handle mouse movement for Julia set */
int	handle_mouse_move(int x, int y, t_fractol *fractol)
{
	if (fractol->fractal_type == JULIA && fractol->julia_mouse_track)
	{
		/* Map mouse coordinates to complex plane for Julia parameter */
		update_julia_params(x, y, fractol);
		clamp_julia_params(fractol);
		render_fractol(fractol);
	}
	return (0);
}
/* Apply zoom centered on mouse position */
static void	apply_zoom(t_complex mouse_pos, double zoom_factor,
		t_fractol *fractol)
{
	double	mouse_real_offset;
	double	mouse_imag_offset;

	/* Calculate offsets from cursor position to current view center */
	mouse_real_offset = mouse_pos.real - fractol->move_x;
	mouse_imag_offset = mouse_pos.imag - fractol->move_y;
	/* Apply zoom directly to zoom factor with limits to prevent excessive zooming
   */
	fractol->zoom *= (1.0 / zoom_factor);
	/* Set limits on zoom to prevent rendering issues */
	if (fractol->zoom < 0.05)
		fractol->zoom = 0.05;
	if (fractol->zoom > 500.0)
		fractol->zoom = 500.0;
	/*
   * Move view center toward mouse position proportionally to zoom change
   * This creates a zoom that's centered on the mouse position
   */
	fractol->move_x += mouse_real_offset * (1.0 - zoom_factor);
	fractol->move_y += mouse_imag_offset * (1.0 - zoom_factor);
}

/* Handle mouse button events for zoom */
int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	t_complex	mouse_pos;
	double		zoom_factor;

	mouse_pos = pixel_to_complex(x, y, fractol);
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		/* Different zoom factors for different fractal types */
		if (fractol->fractal_type == MANDELBROT)
			zoom_factor = (button == MOUSE_SCROLL_UP) ? 0.8 : 1.25;
		else /* JULIA - gentler zooming for better detail control */
			zoom_factor = (button == MOUSE_SCROLL_UP) ? 0.85 : 1.15;
		apply_zoom(mouse_pos, zoom_factor, fractol);
		render_fractol(fractol);
	}
	else if (button == MOUSE_BUTTON_LEFT && fractol->fractal_type == JULIA)
	{
		/* Toggle Julia mouse tracking on left click */
		fractol->julia_mouse_track = !fractol->julia_mouse_track;
		if (fractol->julia_mouse_track)
			ft_printf("Julia mouse tracking: ON\n");
		else
			ft_printf("Julia mouse tracking: OFF\n");
	}
	return (0);
}
