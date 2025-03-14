#include "fractol.h"

int	mandelbrot_iter(t_complex c)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	
	while (i < MAX_ITER)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break;
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

int	julia_iter(t_complex z, t_complex c)
{
	int		i;
	double	temp;

	i = 0;
	while (i < MAX_ITER)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break;
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

t_complex	pixel_to_complex(int x, int y, t_fractal *fractal)
{
	t_complex	complex;
	double		width;
	double		height;

	width = fractal->max.real - fractal->min.real;
	height = fractal->max.imag - fractal->min.imag;
	
	complex.real = fractal->min.real + (double)x / WIDTH * width;
	complex.imag = fractal->min.imag + (double)y / HEIGHT * height;
	
	return (complex);
}

void	render_fractal(t_fractal *fractal)
{
	int			x;
	int			y;
	int			iterations;
	t_complex	complex;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			complex = pixel_to_complex(x, y, fractal);
			if (!strcmp(fractal->type, MANDELBROT))
				iterations = mandelbrot_iter(complex);
			else if (!strcmp(fractal->type, JULIA))
				iterations = julia_iter(complex, fractal->julia_param);
			else
				iterations = 0;
			put_pixel(&fractal->img, x, y, create_color(iterations));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img.img, 0, 0);
}