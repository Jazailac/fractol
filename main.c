/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:08 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/26 06:27:52 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "fractol.h"
#include <unistd.h>
#include "minilibx/mlx.h"

int	handle_key(int keycode, t_fractal *fractal);

int	close_window(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->window);
	mlx_destroy_image(fractal->mlx, fractal->img.img);
	if (fractal->name)
		free(fractal->name);
	if (fractal->mlx)
		free(fractal->mlx);
	exit(0);
}

int	print_error(char *message)
{
	ft_putstr_fd(message, 1);
	return (1);
}

int	check_julia(t_fractal *fractal, int ac, char **av)
{
	fractal->name = ft_strdup("julia");
	if (!fractal->name)
		return (print_error("Error: Malloc failed\n"));
	if (ac == 4)
	{
		if (!ft_isnumeric(av[2]) || !ft_isnumeric(av[3]))
			return (print_usage_e(fractal));
		fractal->julia.real = ft_atof(av[2], 0);
		fractal->julia.imag = ft_atof(av[3], 0);
	}
	else if (ac == 2)
	{
		fractal->julia.real = 0.3;
		fractal->julia.imag = 0.5;
		return (1);
	}
	return (1);
}

int	handle_arguments(int ac, char **av, t_fractal *fractal)
{
	if (ac < 2 || !av)
		return (print_usage_e(fractal));
	if (ft_strncmp("mandelbrot", av[1], 10) == 0
		&& (ac == 2 && ft_strlen(av[1]) == 10))
	{
		fractal->name = ft_strdup("mandelbrot");
		if (!fractal->name)
			return (print_error("Error: Malloc failed\n"));
		return (0);
	}
	else if (ft_strncmp("julia", av[1], 5) == 0 
		&& ((ac == 2 || ac == 4)
			&& ft_strlen(av[1]) == 5))
	{
		if (!check_julia(fractal, ac, av))
			return (print_error("RECHECK JULIA PARAMS\n"));
		return (0);
	}
	return (print_usage_e(fractal));
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac < 2)
	{
		print_usage_e(&fractal);
		return (1);
	}
	ft_memset(&fractal, 0, sizeof(t_fractal));
	if (handle_arguments(ac, av, &fractal))
		return (1);
	init_fractal(&fractal);
	optimize_rendering(&fractal);
	mlx_mouse_hook(fractal.window, handle_mouse, &fractal);
	mlx_key_hook(fractal.window, handle_key, &fractal);
	mlx_hook(fractal.window, 17, 0, close_window, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
