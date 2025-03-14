#include "fractol.h"

int	create_color(int iterations)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations == MAX_ITER)
		return (0);
	t = (double)iterations / MAX_ITER;
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

int	handle_key(int keycode, t_fractal *fractal)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		free(fractal->type);
		exit(0);
	}
	return (0);
}

int handle_mouse(int button, int x, int y, t_fractal *fractal)
{
    t_complex mouse;
    double zoom_factor;

    mouse = pixel_to_complex(x, y, fractal);
    
    if (button == 4) 
    {
        zoom_factor = 0.85; 
    }
    else if (button == 5)  
    {
        zoom_factor = 0.98; 
    }
    else
        return (0);
    fractal->min.real = mouse.real + (fractal->min.real - mouse.real) * zoom_factor;
    fractal->min.imag = mouse.imag + (fractal->min.imag - mouse.imag) * zoom_factor;
    fractal->max.real = mouse.real + (fractal->max.real - mouse.real) * zoom_factor;
    fractal->max.imag = mouse.imag + (fractal->max.imag - mouse.imag) * zoom_factor;
    render_fractal(fractal);
    return (0);
}

int	close_window(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->win);
	free(fractal->type);
	exit(0);
	return (0);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

double is_decimale(char *str, double *result, int *i)
{
	double decimale;

	decimale = 0.1;
	(*i)++;
	while (ft_isdigit(str[(*i)]))
	{
		*result = *result + (str[(*i)++] - '0') * decimale;
		decimale *= 0.1;
	}
	return (*result);
}

double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		i;

	result = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (str[i] == '.')
		result = is_decimale(str, &result, &i);
	return (sign * result);
}