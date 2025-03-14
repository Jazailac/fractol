#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include "minilibx/mlx.h"

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 200
# define MANDELBROT "mandelbrot"
# define JULIA "julia"

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
}	t_img;

typedef struct s_fractal
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		*type;
	t_complex	min;
	t_complex	max;
	t_complex	julia_param;
	double		zoom;
}	t_fractal;

void	display_help(void);
int		parse_args(int argc, char **argv, t_fractal *fractal);
int		init_fractal(t_fractal *fractal);

int		mandelbrot_iter(t_complex c);
int		julia_iter(t_complex z, t_complex c);
t_complex	pixel_to_complex(int x, int y, t_fractal *fractal);
void	render_fractal(t_fractal *fractal);

int		create_color(int iterations);
void	put_pixel(t_img *img, int x, int y, int color);
int		handle_key(int keycode, t_fractal *fractal);
int		handle_mouse(int button, int x, int y, t_fractal *fractal);
int		close_window(t_fractal *fractal);
double	ft_atof(char *str);

#endif