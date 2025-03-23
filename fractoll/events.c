/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:47:58 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/23 02:42:46 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	t_complex	complex;

	complex = handle_pixel(x, y, fractal);
	if (button == 1)
	{
		zoom(fractal, x, y, fractal->zoom_x);
		render_fractal(fractal);
	}
	else if (button == 2)
	{
		zoom(fractal, x, y, fractal->zoom_y);
		render_fractal(fractal);
	}
	return (0);
}

int	handle_key(int keycode, t_fractal *fractal)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		free(fractal->name);
		free(fractal->mlx);
		exit(0);
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
		fractal->max_iterations = (int)(fractal->max_iterations + 15);
	else if (zoom_factor > 1.0 && fractal->max_iterations >= 100)
		fractal->max_iterations -= 25;
}

int	print_usage_e(void)
{
	ft_putstr_fd("HOW TO USE THE PROGRAM ?\n\t", 2);
	ft_putstr_fd("CHOOSE A SET : \n\t", 2);
	ft_putstr_fd("\tFOR MANDELBROT TYPE './fractol 1'\n\t", 2);
	ft_putstr_fd("\tFOR JULIA TYPE './fractol 2'\n\t", 2);
	ft_putstr_fd("IF YOU WANT JULIA WITH COSTUM PARAMS :\n\t", 2);
	ft_putstr_fd("\tTYPE './fractol 2 [real] [imaginary]'\n", 2);
	return (1);
}
