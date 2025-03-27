/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:10 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/26 01:48:41 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key(int keycode, t_fractal *fractal);

int	create_color(int iterations, int max_iterations)
{
	int	color;
	int	r;
	int	g;
	int	b;

	if (iterations == max_iterations)
		return (0x000000);
	r = (iterations * 3) % 256;
	g = (iterations * 5) % 256;
	b = (iterations * 7) % 256;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_isspace(char c)
{
	if (c == 32 || c >= 9)
		return (0);
	else 
		return (1);
}

double	ft_atof(char *str, double res)
{
	int	i;
	int	sign;
	int	divider;

	i = -1;
	res = 0;
	sign = 1;
	divider = 1;
	if ((str[i] <= '0' && str[i] >= '9'))
		return (0);
	if (str[++i] == '-')
		sign = -1;
	while (str[++i] && str[i] != '.')
		res = res * 10 + str[i] - '0';
	if (str[i++] == '.')
	{
		while (str[i])
		{
			res = res * 10 + str[i++] - '0';
			divider *= 10;
		}
	}
	if (str[i] != '\0')
		return (0);
	return ((res * sign) / (double)divider);
}

void	optimize_rendering(t_fractal *fractal)
{
	if (fractal->img.img)
	{
		mlx_destroy_image(fractal->mlx, fractal->img.img);
	}
	fractal->img.img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->img.addr = mlx_get_data_addr(fractal->img.img,
			&fractal->img.bits_per_pixel,
			&fractal->img.line_length,
			&fractal->img.endian);
	render_fractal(fractal);
}
