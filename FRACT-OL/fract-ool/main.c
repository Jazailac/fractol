#include "fractol.h"

void	display_help(void)
{
	printf("Usage: ./fractol [fractal_type] [parameters]\n\n");
	printf("Available fractal types:\n");
	printf("  mandelbrot : Display Mandelbrot set\n");
	printf("  julia [real] [imag] : Display Julia set with optional parameters\n");
	printf("\nExamples:\n");
	printf("  ./fractol mandelbrot\n");
	printf("  ./fractol julia\n");
	printf("  ./fractol julia -0.7 0.27\n");
	exit(0);
}

int	parse_args(int argc, char **argv, t_fractal *fractal)
{
	if (argc < 2)
		return (0);
	
	if (!strcmp(argv[1], MANDELBROT))
		fractal->type = strdup(MANDELBROT);
	else if (!strcmp(argv[1], JULIA))
	{
		fractal->type = strdup(JULIA);
		if (argc >= 4)
		{
			fractal->julia_param.real = ft_atof(argv[2]);
			fractal->julia_param.imag = ft_atof(argv[3]);
		}
		else
		{
			fractal->julia_param.real = -0.7;
			fractal->julia_param.imag = 0.27;
		}
	}
	else
		return (0);
	return (1);
}

int	init_fractal(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		return (0);
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "Fractol");
	if (!fractal->win)
		return (0);
	fractal->img.img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img.img)
		return (0);
	fractal->img.addr = mlx_get_data_addr(fractal->img.img,
			&fractal->img.bits_per_pixel, &fractal->img.line_length,
			&fractal->img.endian);
	
	fractal->min.real = -2.0;
	fractal->min.imag = -2.0;
	fractal->max.real = 2.0;
	fractal->max.imag = 2.0;
	fractal->zoom = 1.0;
	
	return (1);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (!parse_args(argc, argv, &fractal))
	{
		display_help();
		return (1);
	}
	if (!init_fractal(&fractal))
	{
		printf("Error initializing fractal\n");
		free(fractal.type);
		return (1);
	}
	render_fractal(&fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);
	mlx_mouse_hook(fractal.win, handle_mouse, &fractal);
	mlx_hook(fractal.win, 17, 0, close_window, &fractal);
	
	mlx_loop(fractal.mlx);
	return (0);
}