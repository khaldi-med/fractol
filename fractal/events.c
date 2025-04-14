#include "fractal.h"


int close_handler(t_fractal *fractal) {
  mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
  mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
  free(fractal->mlx_connection);
  exit(0);
}

int key_handler(int keysym, t_fractal *fractal) {
  if (keysym == NoExpose)
    close_handler(fractal);
    return 0;
}

int mouse_handler(int button, int x, int y, void *param) {
  (void)x;
  (void)y;
  t_fractal *fractal = (t_fractal *)param;
  if (button == Button5) {
    fractal->zoom *= 0.95;
  }
  else if (button == Button4) {
    fractal->zoom *= 1.05;
  }
  fractal_render(fractal);
  return 0;
}