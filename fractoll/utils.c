#include "fractol.h"

int	handle_key(int keycode, t_fractal *fractal);

int	create_color(int iterations, t_fractal *fractal)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations == fractal->max_iterations)
		return (0);
	t = (double)iterations / fractal->max_iterations;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	
	return ((r << 16) | (g << 8) | b);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void event_init(t_fractal *fractal)
{
	mlx_hook(fractal->window, 02, (1L<<0),handle_key, fractal);
	//need to make handle_mouse();
	// mlx_hook(fractal->window, 04, (1L<<2), handle_mouse, fractal);
	mlx_hook(fractal->window, 05, (1L<<17), handle_key, fractal);

}