#include "LIBFT/libft.h"
#include "fractol.h"
#include <unistd.h>
#include "minilibx/mlx.h"

int	handle_key(int keycode, t_fractal *fractal);

int main(int ac, char **av)
{
    if (ac < 2)
    {
        ft_putstr_fd(ERROR_MESSAGE, 1);
        exit(1);
    }
    t_fractal fractal;
    
    ft_putnbr_fd(getpid(), 1);
    ft_memset(&fractal, 0, sizeof(t_fractal));
    if ((ft_strncmp(av[1], "mandelbrot", 10) == 0)
            || ft_strncmp(av[1], "julia", 5) == 0 && ac >= 2)
    {
        if (av[1][0] == 'j')
            fractal.name = ft_strdup("julia");
        else if (av[1][0] == 'm')
            fractal.name = ft_strdup("mandelbrot");

        //TL;DR  
        //first i need to initialize the fractal struct 
        init_fractal(&fractal);
        // then i need to render the fractal 
        render_fractal(&fractal);
        //handle events
        mlx_key_hook(fractal.window, handle_key, &fractal);
        //mlx loop
        mlx_loop(fractal.mlx);
    }
    else
        ft_putstr_fd(ERROR_MESSAGE, 1);
    return 1;
}