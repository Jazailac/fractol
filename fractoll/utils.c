/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:10 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/21 00:37:29 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key(int keycode, t_fractal *fractal);

int	create_color(int iterations, int max_iterations)
{
	double	ratio;
	int		r;
	int		g;
	int		b;
	int		color_zones;
	
	// If the point is in the set, return black
	if (iterations == max_iterations)
		return (0x000000);
	
	// Create 20 distinct color zones for showing depth
	color_zones = 20;
	ratio = (double)iterations / max_iterations;
	
	// Color scheme that reveals depth through distinct but gradual changes
	if (ratio < 0.16)
	{
		// Deep areas - dark blues
		r = 0;
		g = 0;
		b = (int)(150 + ratio * 650);  // 150-255 range
	}
	else if (ratio < 0.42)
	{
		// Mid-deep areas - blue to cyan
		r = 0;
		g = (int)((ratio - 0.16) * 750);  // 0-255 range
		b = 255;
	}
	else if (ratio < 0.6425)
	{
		// Mid areas - cyan to green
		r = 0;
		g = 255;
		b = 255 - (int)((ratio - 0.42) * 1150);  // 255-0 range
	}
	else if (ratio < 0.8575)
	{
		// Shallow areas - green to yellow to orange
		r = (int)((ratio - 0.6425) * 1150);  // 0-255 range
		g = 255;
		b = 0;
	}
	else
	{
		// Very shallow areas - orange to red
		r = 255;
		g = 255 - (int)((ratio - 0.8575) * 1800);  // 255-0 range
		b = 0;
	}
	
	// Combine RGB values into a single integer
	return ((r << 16) | (g << 8) | b);
}


// int create_color(int iterations, int max_iterations)
// {
//     int color;
//     int r, g, b;
    
//     // Black for points inside the set
//     if (iterations == max_iterations)
//         return (0x000000);
    
//     // Use a simple modulo-based color scheme with 3 components
//     r = (iterations * 7) % 256;
//     g = (iterations * 11) % 256;
//     b = (iterations * 17) % 256;
    
//     // Combine RGB values into a single integer
//     color = (r << 16) | (g << 8) | b;
    
//     return (color);
// }

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