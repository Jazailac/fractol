/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:06 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/23 02:50:01 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include "LIBFT/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>

# define WIDTH 300           
# define HEIGHT 300

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

typedef struct s_fractal
{
	void		*mlx;
	void		*window;
	t_img		img;
	char		*name;
	t_complex	min;
	double		zoom;
	double		offset_x;
	double		offset_y;
	t_complex	max;
	t_complex	julia;
	int			max_iterations;
	double		zoom_x;
	double		zoom_y;

}t_fractal;

void		init_fractal(t_fractal *fractal);
void		put_pixel(t_img *img, int x, int y, int color);
void		render_fractal(t_fractal *fractal);
int			create_color(int iterations, int max_iterations);
t_complex	handle_pixel(int x, int y, t_fractal *fractal);
void		zoom(t_fractal *fractal, int mouse_x,
				int mouse_y, double zoom_factor);
int			mandelbrot_iter(t_complex c, t_fractal *fractal);
int			handle_mouse(int button, int x, int y, t_fractal *fractal);
double		ft_atof(char *str, double res);
void		square_complex(t_complex *z, t_complex *c);
int			cloe_window(t_fractal *fractal);
void		fill_fractal(t_fractal *fractal);
int			print_usage_e(void);
int			set_frcatal_name(int nbr, int ac, t_fractal *fractal, char **av);
#endif