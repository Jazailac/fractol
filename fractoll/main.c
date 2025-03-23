/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:08 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/23 01:40:32 by jazailac         ###   ########.fr       */
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
	free(fractal->name);
	free(fractal->mlx);
	exit(0);
	return (0);
}

int	print_error(char *message)
{
	ft_putstr_fd(message, 1);
	return (1);
}

int	handle_arguments(int ac, char **av, int nbr, t_fractal *fractal)
{
	if ((nbr == 1 || nbr == 2) && ac >= 2)
	{
		if (nbr == 2 && (ac == 4 || ac == 2))
		{
			fractal->name = ft_strdup("julia");
			if (!fractal->name)
				return (print_error("Error: Malloc failed\n"));
			if (nbr == 2 && ac == 4)
			{
				fractal->julia.real = ft_atof(av[2], 0);
				fractal->julia.imag = ft_atof(av[3], 0);
			}
		}
		else if (nbr == 1 && ac == 2)
		{
			fractal->name = ft_strdup("mandelbrot");
			if (!fractal->name)
				return (print_error("Error: Malloc failed\n"));
		}
		else
			return (print_usage_e());
		return (0);
	}
	return (print_usage_e());
}

int	main(int ac, char **av)
{
	t_fractal	fractal;
	int			nbr;

	if (ac < 2)
	{
		print_usage_e();
		return (1);
	}
	ft_memset(&fractal, 0, sizeof(t_fractal));
	nbr = ft_atoi(av[1]);
	if (handle_arguments(ac, av, nbr, &fractal))
		return (1);
	init_fractal(&fractal);
	render_fractal(&fractal);
	mlx_mouse_hook(fractal.window, handle_mouse, &fractal);
	mlx_key_hook(fractal.window, handle_key, &fractal);
	mlx_hook(fractal.window, 17, 0, close_window, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
