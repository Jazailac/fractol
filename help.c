/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:51:09 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/26 07:40:00 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "fractol.h"

t_complex	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	complex;
	double		range_real;
	double		range_imag;

	range_real = fractal->max.real - fractal->min.real;
	range_imag = fractal->max.imag - fractal->min.imag;
	complex.real = fractal->min.real + (double)x / WIDTH * range_real;
	complex.imag = fractal->max.imag - (double)y / HEIGHT * range_imag;
	return (complex);
}

void	fill_fractal(t_fractal *fractal)
{
	fractal->zoom_x = 0.76;
	fractal->zoom_y = 1.8;
	fractal->min.real = -2.0;
	fractal->min.imag = -2.0;
	fractal->max.real = 2.0;
	fractal->max.imag = 2.0;
	fractal->max_iterations = 100;
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
	{
		ft_putstr_fd("Error Initializing the mlx Connection\n", 1);
		return ;
	}
	fractal->window = mlx_new_window(fractal->mlx, WIDTH,
			HEIGHT, fractal->name);
	if (!fractal->window)
	{
		ft_putstr_fd("Error Creating Window\n", 1);
		free(fractal->mlx);
		return ;
	}
	fractal->img.img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img.img)
	{
		ft_putstr_fd("Error Creating Image\n", 1);
		mlx_destroy_window(fractal->mlx, fractal->window);
		free(fractal->mlx);
		return ;
	}
}

int	ft_isnumeric(const char *str)
{
	int	i;
	int	has_dot;
	int	has_digit;

	if (!str)
		return (0);
	i = (*str == '-' || *str == '+');
	has_dot = 0;
	has_digit = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot || !has_digit)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		else
			has_digit = 1;
		i++;
	}
	return (has_digit);
}

void	init_fractal(t_fractal *fractal)
{
	init_mlx(fractal);
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
		free(fractal->name);
		return ;
	}
	fill_fractal(fractal);
}
