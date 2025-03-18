#include "fractol.h"

int	handle_key(int keycode, t_fractal *fractal);

int	create_color(int iterations, int max_iterations)
{
	double	ratio;
	int		r;
	int		g;
	int		b;
	int		color_zones;
	
	// If the point is in the set, return black
	if (iterations == max_iterations)
		return (0x000000);
	
	// Create 20 distinct color zones for showing depth
	color_zones = 20;
	ratio = (double)iterations / max_iterations;
	
	// Color scheme that reveals depth through distinct but gradual changes
	if (ratio < 0.16)
	{
		// Deep areas - dark blues
		r = 0;
		g = 0;
		b = (int)(150 + ratio * 650);  // 150-255 range
	}
	else if (ratio < 0.42)
	{
		// Mid-deep areas - blue to cyan
		r = 0;
		g = (int)((ratio - 0.16) * 750);  // 0-255 range
		b = 255;
	}
	else if (ratio < 0.6425)
	{
		// Mid areas - cyan to green
		r = 0;
		g = 255;
		b = 255 - (int)((ratio - 0.42) * 1150);  // 255-0 range
	}
	else if (ratio < 0.8575)
	{
		// Shallow areas - green to yellow to orange
		r = (int)((ratio - 0.6425) * 1150);  // 0-255 range
		g = 255;
		b = 0;
	}
	else
	{
		// Very shallow areas - orange to red
		r = 255;
		g = 255 - (int)((ratio - 0.8575) * 1800);  // 255-0 range
		b = 0;
	}
	
	// Combine RGB values into a single integer
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