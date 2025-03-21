/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:47:58 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/21 01:09:10 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int handle_mouse(int button, int x, int y, t_fractal *fractal)
{
    t_complex complex;
    complex = handle_pixel(x, y, fractal);
    if (button == 1)
    {
        zoom(fractal, x, y, fractal->zoom_x);
        render_fractal(fractal);
    }
    else if (button == 2)
    {
        zoom(fractal, x, y,fractal->zoom_y);
        render_fractal(fractal);
    }
    return (0);
}


int	handle_key(int keycode, t_fractal *fractal)
{
    int temp;

    temp = 0;
    if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		free(fractal->name);
        free(fractal->mlx);
		exit(0);
	}
    else if (keycode == 8)
    {
        fractal->color_shift = (fractal->color_shift + 10) % 256;
        render_fractal(fractal);
    }
    else if (keycode == 7) 
    {
        fractal->color_shift = (fractal->color_shift - 10 + 256) % 256;
        render_fractal(fractal);
    }
	return (0);
}
// void zoom(t_fractal *fractal, int mouse_x, int mouse_y, double zoom_factor)
// {
//     t_complex mouse_pos;
//     double real_diff;
//     double imag_diff;

//     mouse_pos = handle_pixel(mouse_x, mouse_y, fractal);
//     real_diff = mouse_pos.real - fractal->min.real;
//     imag_diff = mouse_pos.imag - fractal->min.imag;

//     fractal->min.real = mouse_pos.real - real_diff * zoom_factor;
//     fractal->min.imag = mouse_pos.imag - imag_diff * zoom_factor;
//     fractal->max.real = mouse_pos.real + (fractal->max.real - mouse_pos.real) * zoom_factor;
//     fractal->max.imag = mouse_pos.imag + (fractal->max.imag - mouse_pos.imag) * zoom_factor;
//     if (zoom_factor < 1.0 && fractal->max_iterations < 500)
//         fractal->max_iterations = (int)(fractal->max_iterations * 1.2);
//     else if (zoom_factor > 1.0 && fractal->max_iterations > 100)
//         fractal->max_iterations -= 1;

// }


void zoom(t_fractal *fractal, int mouse_x, int mouse_y, double zoom_factor)
{
    t_complex mouse_pos;
    double real_diff;
    double imag_diff;
    double new_width;
    double new_height;
    double initial_width = 4.0; 
    double initial_height = 4.0; 
    double max_zoom_in = 0.0000000001;  
    double max_zoom_out = 2.0;
    mouse_pos = handle_pixel(mouse_x, mouse_y, fractal);
    real_diff = mouse_pos.real - fractal->min.real;
    imag_diff = mouse_pos.imag - fractal->min.imag;
    
    new_width = (fractal->max.real - fractal->min.real) * zoom_factor;
    new_height = (fractal->max.imag - fractal->min.imag) * zoom_factor;

    if (new_width < initial_width * max_zoom_in || new_height < initial_height * max_zoom_in)
    {
        fractal->min.real = -2.0;
        fractal->min.imag = -2.0;
        fractal->max.real = 2.0;
        fractal->max.imag = 2.0;
        fractal->max_iterations = 70;
        return;
    }
    else if (new_width > initial_width * max_zoom_out || new_height > initial_height * max_zoom_out)
    {
        fractal->min.real = -2.0;
        fractal->min.imag = -2.0;
        fractal->max.real = 2.0;
        fractal->max.imag = 2.0;
        fractal->max_iterations = 70;
        return;
    }
    fractal->min.real = mouse_pos.real - real_diff * zoom_factor;
    fractal->min.imag = mouse_pos.imag - imag_diff * zoom_factor;
    fractal->max.real = mouse_pos.real + (fractal->max.real - mouse_pos.real) * zoom_factor;
    fractal->max.imag = mouse_pos.imag + (fractal->max.imag - mouse_pos.imag) * zoom_factor;
    if (zoom_factor < 1.0 && fractal->max_iterations < 500)
        fractal->max_iterations = fractal->max_iterations * 1.1;
    else if (zoom_factor > 1.0 && fractal->max_iterations > 70)
        fractal->max_iterations /= 1.1;
}