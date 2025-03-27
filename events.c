/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:47:58 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/26 09:56:16 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == 4)
	{
		zoom(fractal, x, y, fractal->zoom_x);
		optimize_rendering(fractal);
	}
	else if (button == 5)
	{
		zoom(fractal, x, y, fractal->zoom_y);
		optimize_rendering(fractal);
	}
	return (0);
}

int	handle_key(int keycode, t_fractal *fractal)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		if (fractal->name)
			free(fractal->name);
		if (fractal->mlx)
			free(fractal->mlx);
		exit(0);
	}
	else if (keycode == 15) 
	{
		fractal->min.real = -2.0;
		fractal->min.imag = -2.0;
		fractal->max.real = 2.0;
		fractal->max.imag = 2.0;
		fractal->max_iterations = 100;
		optimize_rendering(fractal);
	}
	return (0);
}

void	zoom(t_fractal *fractal, int mouse_x, int mouse_y, double zoom_factor)
{
	t_complex	mouse_pos;
	double		real_diff;
	double		imag_diff;
	double		mr_diff;
	double		mi_diff;

	mouse_pos = handle_pixel(mouse_x, mouse_y, fractal);
	real_diff = mouse_pos.real - fractal->min.real;
	imag_diff = mouse_pos.imag - fractal->min.imag;
	mr_diff = fractal->max.real - mouse_pos.real;
	mi_diff = fractal->max.imag - mouse_pos.imag;
	fractal->min.real = mouse_pos.real - real_diff * zoom_factor; 
	fractal->min.imag = mouse_pos.imag - imag_diff * zoom_factor;
	fractal->max.real = mouse_pos.real + mr_diff * zoom_factor;
	fractal->max.imag = mouse_pos.imag + mi_diff * zoom_factor;
	if (zoom_factor < 1.0 && fractal->max_iterations <= 2147483647)
	{
		fractal->max_iterations = (int)(fractal->max_iterations + 3);
	}
	else if (zoom_factor > 1.0 && fractal->max_iterations >= 100)
		fractal->max_iterations -= 6;
}

int	print_usage_e(void)
{
	ft_putstr_fd("HOW TO USE THE PROGRAM ?\n\t", 2);
	ft_putstr_fd("CHOOSE A SET : \n\t", 2);
	ft_putstr_fd("\tFOR MANDELBROT TYPE './fractol mandelbrot'\n\t", 2);
	ft_putstr_fd("\tFOR JULIA TYPE './fractol julia'\n\t", 2);
	ft_putstr_fd("IF YOU WANT JULIA WITH COSTUM PARAMS :\n\t", 2);
	ft_putstr_fd("\tTYPE './fractol julia [real] [imaginary]'\n\t", 2);
	ft_putstr_fd("\tF.E './fractol julia 0.3 0.01'\n", 2);
	exit (1);
}
