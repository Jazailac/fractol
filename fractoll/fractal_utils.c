#include "LIBFT/libft.h"
#include "fractol.h"
#include "minilibx/mlx.h"


int	mandelbrot_iter(t_complex c, t_fractal *fractal)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	
	while (i < fractal->max_iterations)
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

void init_fractal(t_fractal *fractal)
{
    fractal->mlx = mlx_init();
    if (!fractal->mlx)
    {
        ft_putstr_fd("Error Initializing the mlx Connection\n", 1);
        return;
    }
    
    fractal->window = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, fractal->name);
    if (!fractal->window)
    {
        ft_putstr_fd("Error Creating Window\n", 1);
        free(fractal->mlx);
        return;
    }
    
    fractal->img.img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
    if (!fractal->img.img)
    {
        ft_putstr_fd("Error Creating Image\n", 1);
        mlx_destroy_window(fractal->mlx, fractal->window);
        free(fractal->mlx);
        return;
    }
    
    fractal->img.addr = mlx_get_data_addr(fractal->img.img, 
                                         &fractal->img.bits_per_pixel, 
                                         &fractal->img.line_length, 
                                         &fractal->img.endian);
    if (!fractal->img.addr)
    {
        ft_putstr_fd("Error Getting Image Address\n", 1);
        mlx_destroy_image(fractal->mlx, fractal->img.img);
        mlx_destroy_window(fractal->mlx, fractal->window);
        free(fractal->mlx);
        return;
    }
    fractal->shift_x = 0.0;
    fractal->shift_y = 0.0;
    fractal->min.real = -2.0;
	fractal->min.imag = -1.5;
	fractal->max.real = 1.0;
	fractal->max.imag = 1.5;
    fractal->max_iterations = 278;  
    // Set up event hooks
    // event_init(fractal);
}

t_complex handle_pixel(int x, int y, t_fractal *fractal)
{
    t_complex complex;
    double range_real = fractal->max.real - fractal->min.real;
    double range_imag = fractal->max.imag - fractal->min.imag;

    complex.real = fractal->min.real + (double)x / WIDTH * range_real;
    complex.imag = fractal->min.imag + (double)y / HEIGHT * range_imag;
    return (complex);
}

void render_fractal(t_fractal *fractal)
{
    int iterations;
    int x;
    int y;
    t_complex cmplx;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            cmplx = handle_pixel(x, y, fractal);
            if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
            {
                iterations = mandelbrot_iter(cmplx, fractal);
            }
            else 
                iterations = 0;
            put_pixel(&fractal->img, x, y, create_color(iterations, fractal));
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->img.img, 0, 0);
}