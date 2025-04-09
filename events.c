#include "fractol.h"

/**
 * @brief Handle key press events
 * 
 * Processes keyboard inputs for various controls
 * 
 * @param keycode The key that was pressed
 * @param fractol Pointer to the main fractol structure
 * @return int Always returns 0
 */
int	handle_key(int keycode, t_fractol *fractol)
{
	double	move_factor;
	double	range_x;
	
	/* Calculate movement factor based on current view size */
	range_x = fractol->max.real - fractol->min.real;
	move_factor = range_x * 0.05;
	
	if (keycode == KEY_ESC)
		clean_exit(fractol, 0);
	else if (keycode == KEY_UP)
	{
		fractol->min.imag -= move_factor;
		fractol->max.imag -= move_factor;
		render_fractol(fractol);
	}
	else if (keycode == KEY_DOWN)
	{
		fractol->min.imag += move_factor;
		fractol->max.imag += move_factor;
		render_fractol(fractol);
	}
	else if (keycode == KEY_LEFT)
	{
		fractol->min.real -= move_factor;
		fractol->max.real -= move_factor;
		render_fractol(fractol);
	}
	else if (keycode == KEY_RIGHT)
	{
		fractol->min.real += move_factor;
		fractol->max.real += move_factor;
		render_fractol(fractol);
	}
	else if (keycode == KEY_C)
		change_color_scheme(fractol);
	else if (keycode == KEY_R)
		reset_view(fractol);
	else if (keycode == KEY_PLUS)
		change_iterations(fractol, 1);
	else if (keycode == KEY_MINUS)
		change_iterations(fractol, 0);
	
	return (0);
}

/**
 * @brief Handle mouse events
 * 
 * Process mouse clicks and scrolling for zoom and other interactions
 * 
 * @param button The mouse button that was clicked
 * @param x X-coordinate of the mouse
 * @param y Y-coordinate of the mouse
 * @param fractol Pointer to the main fractol structure
 * @return int Always returns 0
 */
int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	double		zoom_factor;
	t_complex	mouse_pos;
	double		center_x;
	double		center_y;
	double		width;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		/* Get the position before zoom */
		mouse_pos = pixel_to_complex(x, y, fractol);
		
		/* Calculate zoom factor (more gradual) */
		zoom_factor = (button == MOUSE_SCROLL_UP) ? 0.95 : 1.05;
		
		/* Get current width for bounds checking */
		width = fractol->max.real - fractol->min.real;
		
		/* Check zoom bounds to prevent excessive zoom */
		if ((button == MOUSE_SCROLL_UP && width > 1e-13) || 
			(button == MOUSE_SCROLL_DOWN && width < 4.0))
		{
			/* Calculate the new boundaries */
			center_x = mouse_pos.real;
			center_y = mouse_pos.imag;
			
			/* Update boundaries while maintaining aspect ratio */
			fractol->min.real = center_x - (center_x - fractol->min.real) * zoom_factor;
			fractol->max.real = center_x + (fractol->max.real - center_x) * zoom_factor;
			fractol->min.imag = center_y - (center_y - fractol->min.imag) * zoom_factor;
			fractol->max.imag = center_y + (fractol->max.imag - center_y) * zoom_factor;
			
			render_fractol(fractol);
		}
	}
	else if (button == MOUSE_BUTTON_LEFT && fractol->fractal_type == JULIA)
	{
		/* Toggle Julia set mouse parameter tracking */
		fractol->julia_mouse_track = !fractol->julia_mouse_track;
	}
	
	return (0);
}

/**
 * @brief Handle mouse movement
 * 
 * Update Julia set parameters when mouse tracking is enabled
 * 
 * @param x X-coordinate of the mouse
 * @param y Y-coordinate of the mouse
 * @param fractol Pointer to the main fractol structure
 * @return int Always returns 0
 */
int	handle_mouse_move(int x, int y, t_fractol *fractol)
{
	/* Only update Julia parameters if tracking is enabled and we're using Julia set */
	if (fractol->julia_mouse_track && fractol->fractal_type == JULIA)
	{
		/* Convert screen coordinates to complex plane */
		fractol->julia_c = pixel_to_complex(x, y, fractol);
		
		/* Render with new parameters */
		render_fractol(fractol);
	}
	
	return (0);
}

/**
 * @brief Display information about the current fractal
 * 
 * Prints the current parameters and controls to the console
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	display_info(t_fractol *fractol)
{
	ft_printf("\n--- Fractol Information ---\n");
	if (fractol->fractal_type == MANDELBROT)
		ft_printf("Fractal: Mandelbrot Set\n");
	else if (fractol->fractal_type == JULIA)
	{
		ft_printf("Fractal: Julia Set\n");
		ft_printf("Parameters: c = %.6f + %.6fi\n", 
			fractol->julia_c.real, fractol->julia_c.imag);
		if (fractol->julia_mouse_track)
			ft_printf("Julia mouse tracking: ON\n");
		else
			ft_printf("Julia mouse tracking: OFF\n");
	}
	
	ft_printf("Zoom: %.2f\n", fractol->zoom);
	ft_printf("Position: (%.6f, %.6f)\n", fractol->move_x, fractol->move_y);
	ft_printf("Max iterations: %d\n", fractol->max_iterations);
	ft_printf("Color scheme: %d\n", fractol->color_scheme);
	
	ft_printf("\n--- Controls ---\n");
	ft_printf("Arrow keys: Move around\n");
	ft_printf("Mouse wheel: Zoom in/out\n");
	ft_printf("Left click (Julia): Toggle parameter tracking\n");
	ft_printf("C: Change color scheme\n");
	ft_printf("R: Reset view\n");
	ft_printf("+/-: Increase/decrease iterations\n");
	ft_printf("ESC: Exit\n");
}

