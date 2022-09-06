#include <mlx.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
	bool	w_pressed;
	bool	s_pressed;
	bool	a_pressed;
	bool	d_pressed;
}				t_vars;

int	key_press(int keycode, t_vars *vars)
{
	(void)vars;
	printf("Key pressed: %d\n", keycode);
	if (keycode == 119)
	{
		// printf("Set w_press to true\n");
		vars->w_pressed = true;
	}
	else if (keycode == 115)
		vars->s_pressed = true;
	else if (keycode == 100)
		vars->d_pressed = true;
	else if (keycode == 97)
		vars->a_pressed = true;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	(void)vars;
	printf("Key released: %d\n", keycode);
	if (keycode == 119)
	{
		// printf("Set w_press to false\n");
		vars->w_pressed = false;
	}
	else if (keycode == 115)
		vars->s_pressed = false;
	else if (keycode == 100)
		vars->d_pressed = false;
	else if (keycode == 97)
		vars->a_pressed = false;
	return (0);
}

int	loop(t_vars *vars)
{
	// printf("Yo\n");
	if (vars->w_pressed == true)
		printf("J'AVANCEEEEEEEE\n");
	if (vars->a_pressed == true)
		printf("GAUUUUUUCHE\n");
	// sleep(1);
	return (0);
}

// clangc exploration/mlx_autorepeat.c -I minilibx -lmlx -lXext -lX11 -L minilibx

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	// mlx_do_key_autorepeatoff(vars.mlx);
	// mlx_do_key_autorepeaton(vars.mlx);
	mlx_hook(vars.win, 2, 1L<<0,key_press, &vars);
	mlx_hook(vars.win, 3, 1L<<1,key_release, &vars);
	mlx_loop_hook(vars.mlx, loop, &vars);
	mlx_loop(vars.mlx);
}
