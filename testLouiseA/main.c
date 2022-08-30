#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	// (void)vars;
	// printf("printing on repeat key : %d\n", keycode);
	if (keycode == 100)
		printf("I'm moving right thanks: %d\n", keycode);
	else if (keycode == 97)
		printf("I'm moving left thanks: %d\n", keycode);
	else if (keycode == 119)
		printf("I'm moving forward thanks: %d\n", keycode);
	else if (keycode == 115)
		printf("I'm moving backward thanks: %d\n", keycode);
	else if (keycode == 65363)
		printf("Seeing what's on my right\n");
	else if (keycode == 65361)
		printf("Seeing what's on my left\n");
	else if (keycode == 65307)
	{
		printf("I'm leaving this place...");
		mlx_destroy_window(vars->mlx, vars->win);
		exit (1);
	}
	else
		printf("What are you trying to do ?\n");
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 02, (1L<<0), key_hook, &vars);
	mlx_loop(vars.mlx);
}

// right - D = 100
// left - A = 97
// front - W = 119
// back - S = 115

// fleche droite = 65363
// fleche gauche = 65361
// esc = 65307
