#include "cub3d.h"

int	camera_hook(int keycode, t_all *all)
{
	double	old_dir_x;
	double	old_dir_y;

	old_dir_x = all->player.dir.x;
	old_dir_y = all->player.dir.y;

	printf("old_dir_x = %f\n", all->player.dir.x);
	printf("old_dir_y = %f\n", all->player.dir.y);

	if (keycode == 65361)  // fleche GAUCHE
	{
		printf("Moving counter clockwise\n");
		all->player.dir.x = (old_dir_x * cos(0.02)) + (-sin(0.02) * old_dir_y);
		all->player.dir.y = (sin(0.02) * old_dir_x) + (cos(0.02) * old_dir_y);
		printf("new dir_x = %f\n", all->player.dir.x);
		printf("new dir_y = %f\n", all->player.dir.y);
		printf("\n");

		// (x * cos(0,0174533)) + (-sin(0,0174533) * y) = x'
		// (sin(0,0174533) * x) + (cos(0,0174533) * y) = y'
	}
	else if (keycode == 65363)  // fleche DROITE
	{
		printf("Moving clockwise\n");
		all->player.dir.x = (all->player.dir.x * cos(-0.02)) + (-sin(-0.02) * all->player.dir.y);
		all->player.dir.y = (sin(-0.02) * all->player.dir.x) + (cos(-0.02) * all->player.dir.y);
		printf("new dir_x = %f\n", all->player.dir.x);
		printf("new dir_y = %f\n", all->player.dir.y);
		printf("\n");
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_all *all;
//
// 	all = init_all();
// 	if (all == NULL)
// 		return (1);
// 	if (parser(argc, argv, all) != 0)
// 		return (destroy_all(all), 1);
// 	init_player(&all->player, all->map);
// 	all->mlx = mlx_init();
// 	all->win = mlx_new_window(all->mlx, 640, 480, "Hello world!");
// 	mlx_hook(all->win, 02, (1L<<0), camera_hook, all);
// 	mlx_loop(all->mlx);
// }

// right - D = 100
// left - A = 97
// front - W = 119
// back - S = 115

// fleche droite = 65363
// fleche gauche = 65361
// esc = 65307
