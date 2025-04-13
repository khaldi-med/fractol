/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:34 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/13 02:23:09 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* Function to put a pixel in the image */
void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	/* Calculate the memory address of the pixel position */
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	/* Put the color value at that memory address */
	*(unsigned int *)dst = color;
}

/* Function to create a color with RGB values */
int	create_color(int r, int g, int b)
{
	/* Combine RGB values into a single integer */
	return (r << 16 | g << 8 | b);
}

/* Draw a gradient pattern using while loops */
void	draw_gradient(t_img *img, int width, int height)
{
	int	x;
	int	y;
	int	color;
	int	r;
	int	g;
	int	b;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			/* Create a gradient based on x and y position */
			r = (x * 255) / width;
			/* Red increases with x */
			g = (y * 255) / height;
			/* Green increases with y */
			b = 255 - ((x + y) * 255) / (width + height);
			/* Blue creates contrast */
			/* Create color and draw pixel */
			color = create_color(r, g, b);
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

/* Initialize image structure */
void	init_image(t_fractol *fractol)
{
	/* Create a new image */
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img.img_ptr)
		error_exit(ERROR_IMAGE);
	/* Get image data address and properties */
	fractol->img.addr = mlx_get_data_addr(fractol->img.img_ptr,
											&fractol->img.bits_per_pixel,
											&fractol->img.line_length,
											&fractol->img.endian);
}

/* Handle key press events */
int	handle_key(int keycode, t_fractol *fractol)
{
	/* Exit program when ESC is pressed */
	if (keycode == KEY_ESC)
		clean_exit(fractol, 0);
	return (0);
}

/* Handle window close event */
int	close_window(t_fractol *fractol)
{
	clean_exit(fractol, 0);
	return (0);
}

/* Main function */
int	main(void)
{
	t_fractol	fractol;

	/* Initialize MLX */
	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		error_exit(ERROR_MLX);
	/* Create window */
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "Gradient Demo");
	if (!fractol.win)
	{
		mlx_destroy_display(fractol.mlx);
		free(fractol.mlx);
		error_exit(ERROR_WINDOW);
	}
	/* Initialize image */
	init_image(&fractol);
	/* Draw the gradient */
	draw_gradient(&fractol.img, WIDTH, HEIGHT);
	/* Put the image to the window */
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.img.img_ptr, 0,
			0);
	/* Set up event hooks */
	mlx_hook(fractol.win, KEY_PRESS, 0, handle_key, &fractol);
	mlx_hook(fractol.win, CLIENT_EXIT, 0, close_window, &fractol);
	/* Start the MLX loop */
	mlx_loop(fractol.mlx);
	/* This point should never be reached because of mlx_loop */
	return (0);
}
