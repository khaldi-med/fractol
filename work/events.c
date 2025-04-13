#include "draw.h"

/* Handle window close event */
int	close_window(t_fractol *fractol)
{
	clean_exit(fractol, 0);
	return (0);
}

/* Handle keyboard movement keys (UP, DOWN, LEFT, RIGHT) */
static void	handle_view_keys(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_UP)
		fractol->min.imag -= 0.1 * (fractol->max.imag - fractol->min.imag);
	else if (keycode == KEY_DOWN)
		fractol->min.imag += 0.1 * (fractol->max.imag - fractol->min.imag);
	else if (keycode == KEY_LEFT)
		fractol->min.real -= 0.1 * (fractol->max.real - fractol->min.real);
	else if (keycode == KEY_RIGHT)
		fractol->min.real += 0.1 * (fractol->max.real - fractol->min.real);
	fractol->max.real = fractol->min.real + (fractol->max.imag
			- fractol->min.imag) * WIDTH / HEIGHT;
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
int	handle_mouse_move(int x, int y, t_fractol *fractol)
{
	if (fractol->fractal_type == JULIA && fractol->julia_mouse_track)
	{
		fractol->julia_c.real = 4.0 * ((double)x / WIDTH - 0.5);
		fractol->julia_c.imag = 4.0 * ((double)y / HEIGHT - 0.5);
		render_fractol(fractol);
	}
	return (0);
}

/* Apply zoom centered on mouse position */
static void	apply_zoom(t_complex mouse_pos, double zoom_factor,
		t_fractol *fractol)
{
	fractol->min.real = mouse_pos.real -
		(mouse_pos.real - fractol->min.real) * zoom_factor;
	fractol->min.imag = mouse_pos.imag -
		(mouse_pos.imag - fractol->min.imag) * zoom_factor;
	fractol->max.real = mouse_pos.real +
		(fractol->max.real - mouse_pos.real) * zoom_factor;
	fractol->max.imag = mouse_pos.imag +
		(fractol->max.imag - mouse_pos.imag) * zoom_factor;
}

/* Handle mouse button events for zoom */
int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	t_complex	mouse_pos;
	double		zoom_factor;

	mouse_pos = pixel_to_complex(x, y, fractol);
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		zoom_factor = (button == MOUSE_SCROLL_UP) ? 0.9 : 1.1;
		apply_zoom(mouse_pos, zoom_factor, fractol);
		render_fractol(fractol);
	}
	return (0);
}
