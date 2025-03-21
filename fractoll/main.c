/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:08 by jazailac          #+#    #+#             */
/*   Updated: 2025/03/21 00:59:07 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "fractol.h"
#include <unistd.h>
#include "minilibx/mlx.h"

int	handle_key(int keycode, t_fractal *fractal);

int close_window(t_fractal *fractal)
{
    mlx_destroy_window(fractal->mlx, fractal->window);
    free(fractal->name);
    free(fractal->mlx);
    exit(0);
    return (0);
}

int main(int ac, char **av)
{
    int nbr;

    if (ac < 2)
    {
        ft_putstr_fd(ERROR_MESSAGE, 1);
        exit(1);
    }
    t_fractal fractal;
    
    ft_memset(&fractal, 0, sizeof(t_fractal));
    nbr = ft_atoi(av[1]);   
    if ((nbr == 1 || nbr == 2) && ac >= 2)
    {
        if (nbr == 2 && ac == 4)
        {
            fractal.name = ft_strdup("julia");
            if (nbr == 2 && ac == 4)
            {
                fractal.julia.real = ft_atof(av[2], 0);
                fractal.julia.imag = ft_atof(av[3], 0);
            }
        }
        else if (nbr == 1 && ac == 2)
            fractal.name = ft_strdup("mandelbrot");
        else
         {
            ft_putstr_fd(ERROR_MESSAGE, 2);
            exit(1);
        }
        init_fractal(&fractal);
        render_fractal(&fractal);
        mlx_mouse_hook(fractal.window, handle_mouse, &fractal);
        mlx_key_hook(fractal.window, handle_key, &fractal);
        mlx_hook(fractal.window, 17, 0, close_window, &fractal);
        mlx_loop(fractal.mlx);
    }
    else
        ft_putstr_fd(ERROR_MESSAGE, 2);
    return 1;
}