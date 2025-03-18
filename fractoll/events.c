#include "fractol.h"

int handle_mouse(int button, int x, int y, t_fractal *fractal)
{
    t_complex complex;
    complex = handle_pixel(x, y, fractal);
    if (button == 4)
    {
        zoom(fractal, x, y, fractal->zoom_x);
        render_fractal(fractal);
    }
    else if (button == 5)
    {
        zoom(fractal, x, y,fractal->zoom_y);
        render_fractal(fractal);
    }
    return (0);
}


int	handle_key(int keycode, t_fractal *fractal)
{
    int temp;

    temp = 0;
    if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		free(fractal->name);
        free(fractal->mlx);
		exit(0);
	}
    else if (keycode == 69)//to replace with +-iterations keycode to zoom in
    {
        temp = fractal->max_iterations + 20;
        if (temp <= 280)
            fractal->max_iterations += 20;
        render_fractal(fractal);
    }
    else if (keycode == 78)//to replace with -iterations keycode to zoom in
    {
        temp = fractal->max_iterations - 20;
        if (temp >= -500 && temp <= 280)
            fractal->max_iterations -= 20;
        render_fractal(fractal);
    }
	return (0);
}

void zoom(t_fractal *fractal, int mouse_x, int mouse_y, double zoom_factor)
{
    t_complex   mouse_pos;
    double range_real, range_imag;

    mouse_pos = handle_pixel(mouse_x, mouse_y, fractal);
    range_real = fractal->max.real - fractal->min.real;
    range_imag = fractal->max.imag - fractal->min.imag;
    fractal->min.real = mouse_pos.real - (mouse_pos.real - fractal->min.real) * zoom_factor;
    fractal->min.imag = mouse_pos.imag - (mouse_pos.imag - fractal->min.imag) * zoom_factor;
    fractal->max.real = mouse_pos.real + (fractal->max.real - mouse_pos.real) * zoom_factor;
    fractal->max.imag = mouse_pos.imag + (fractal->max.imag - mouse_pos.imag) * zoom_factor;
    if (zoom_factor < 1.0 && fractal->max_iterations < 500)
        fractal->max_iterations *= 1.2; 
}