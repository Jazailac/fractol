/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:02 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/23 00:14:29 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "fractol.h"
#include "minilibx/mlx.h"

void	square_comlex(t_complex *z, t_complex *c)
{
	double	temp;

	temp = z->real;
	z->real = z->real * z->real - z->imag * z->imag + c->real;
	z->imag = 2.0 * temp * z->imag + c->imag;
}

int	mandelbrot_iter(t_complex c, t_fractal *fractal)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	temp = 0.0;
	while (i < fractal->max_iterations)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		square_comlex(&z, &c);
		i++;
	}
	return (i);
}

int	julia_iter(t_complex z, t_complex c, t_fractal *fractal)
{
	int	i;

	i = 0;
	while (i < fractal->max_iterations)
	{
		if ((z.imag * z.imag + z.real * z.real) > 4)
			break ;
		square_comlex(&z, &c);
		i++; 
	}
	return (i);
}

void	draw(t_fractal *fractal, int x, int y)
{
	int			iterations;
	t_complex	cmplx;
	int			color;

	iterations = 0;
	color = 0;
	cmplx = handle_pixel(x, y, fractal);
	if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
	{
		iterations = mandelbrot_iter(cmplx, fractal);
	}
	else if (ft_strncmp(fractal->name, "julia", 5) == 0)
	{
		cmplx = handle_pixel(x, y, fractal);
		iterations = julia_iter(cmplx, fractal->julia, fractal);
	}
	if (iterations == fractal->max_iterations)
		color = 0x000000;
	else
		color = create_color(iterations, fractal->max_iterations);
	put_pixel(&fractal->img, x, y, color);
}

void	render_fractal(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			draw(fractal, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx,
		fractal->window, fractal->img.img, 0, 0);
}
