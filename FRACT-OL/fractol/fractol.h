#ifndef FRACTOL_H
#define FRACTOL_H

#include "minilibx/mlx.h"
#include "LIBFT/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define ERROR_MESSAGE "[Usage] :\n\t ./fractol {set} {parameters (for julia)} \n [available sets] :\n\t mandelbrot \n\t julia {optional parameters}\n"
#define WIDTH 500
#define HEIGHT 500
#define MAX_ITER 150


typedef struct s_complex
{
    double real;
    double imag;
}t_complex;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

typedef struct s_fractal
{
    void *mlx;
    void *window;
    t_img img;
    char *name;
    t_complex min;
    t_complex max;

}t_fractal;

void init_fractal(t_fractal *fractal);
void	put_pixel(t_img *img, int x, int y, int color);
void render_fractal(t_fractal *fractal);
int	create_color(int iterations);
t_complex handle_pixel(int x, int y, t_fractal *fractal);


#endif