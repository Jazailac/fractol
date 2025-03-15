#include "fractol.h"

int handle_mouse(int button, int x, int y, t_fractal *fractal)
{
    if (button == 4)
    {
        zoom(fractal, x, y, 0.9);
    }
    else if (button == 5)
    {
        zoom(fractal, x, y, 1.1 );
    }
    return (0);
}


int	handle_key(int keycode, t_fractal *fractal)
{
    if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		free(fractal->name);
        free(fractal->mlx);
		exit(0);
	}
    else if (keycode == 69)//to replace with +iterations keycode to zoom in
    {
        fractal->max_iterations += 30;
    }
    else if (keycode == 78)//to replace with -iterations keycode to zoom in
    {
        fractal->max_iterations -= 30;
    }
	return (0);
}

void zoom(t_fractal *fractal, int mouse_x, int mouse_y, double zoom_factor)
{
    t_complex   center;
    double new_range_real;
    double new_range_imag;

    center = handle_pixel(mouse_x, mouse_y, fractal);
    new_range_imag = (fractal->max.imag - fractal->min.imag) * zoom_factor;
    new_range_real = (fractal->max.real - fractal->min.real) * zoom_factor;
    fractal->min.real = center.real - new_range_real / 2;
    fractal->min.imag = center.imag - new_range_real / 2;
    fractal->max.real = center.real + new_range_real / 2;
    fractal->max.imag = center.imag + new_range_real / 2;
    render_fractal(fractal);
}