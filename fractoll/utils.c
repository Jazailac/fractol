/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:10 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/23 02:46:25 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key(int keycode, t_fractal *fractal);

// int	create_color(int iterations, int max_iterations)
// {
// 	int	color;
// 	int	r;
// 	int	g;
// 	int	b;

// 	if (iterations == max_iterations)
// 		return (0x000000);
// 	r = (iterations * 7) % 256;
// 	g = (iterations * 11) % 256;
// 	b = (iterations * 17) % 256;
// 	color = (r << 16) | (g << 8) | b;
// 	return (color);
// }
int create_color(int iterations, int max_iterations) {
    if (iterations == max_iterations)
        return 0x000000; // Black for points inside the set

    // Smooth color gradient
    double t = (double)iterations / max_iterations;
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    return (r << 16) | (g << 8) | b;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	return (res * sign / divider);
}
