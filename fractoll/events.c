#include "fractol.h"

int	handle_key(int keycode, t_fractal *fractal)
{
    if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		free(fractal->name);
        free(fractal->mlx);
		exit(0);
	}
    else if (keycode == 34)//to replace with left keycode to zoom in
    {

    }
    else if (keycode == 34)//to replace with right keycode to zoom in
    {

    }
    else if (keycode == 34)//to replace with up keycode to zoom in
    {

    }
    else if (keycode == 34)//to replace with down keycode to zoom in
    {

    }
    else if (keycode == 34)//to replace with +iterations keycode to zoom in
    {
        fractal->max_iterations += 30;
    }
    else if (keycode == 34)//to replace with -iterations keycode to zoom in
    {
        fractal->max_iterations -= 30;
    }
	return (0);
}