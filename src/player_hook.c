#include "cub3d.h"

// (x * cos(0,0174533)) + (-sin(0,0174533) * y) = x'
// (sin(0,0174533) * x) + (cos(0,0174533) * y) = y'

// creer une variable temporaire dans laquelle on stock ntore nouvelle position
// souaitee, si cette position est ok (pas un 1) alors on peut y aller
// sinon on empeche notre camera d'y aller

int	key_hook(int keycode, t_all *all)
{
	double	old_dir_x;
	double	old_dir_y;

	old_dir_x = all->player.dir.x;
	old_dir_y = all->player.dir.y;

	if (keycode == 65361)  // fleche GAUCHE
	{
		all->player.dir.x = (old_dir_x * cos(-ROTSPEED)) + (-sin(-ROTSPEED) * old_dir_y);
		all->player.dir.y = (sin(-ROTSPEED) * old_dir_x) + (cos(-ROTSPEED) * old_dir_y);
		player_plane(all);
	}
	else if (keycode == 65363)  // fleche DROITE
	{
		all->player.dir.x = (old_dir_x * cos(ROTSPEED)) + (-sin(ROTSPEED) * old_dir_y);
		all->player.dir.y = (sin(ROTSPEED) * old_dir_x) + (cos(ROTSPEED) * old_dir_y);
		player_plane(all);
	}
	else if (keycode == 97) // A (moving left)
	{
		all->player.pos.x += all->player.dir.y * MOVESPEED;
		all->player.pos.y -= all->player.dir.x * MOVESPEED;
	}
	else if (keycode == 100) // D (moving right)
	{
		all->player.pos.x -= all->player.dir.y * MOVESPEED;
		all->player.pos.y += all->player.dir.x * MOVESPEED;
	}
	else if (keycode == 119) // W (moving forwards)
	{
			all->player.pos.x += all->player.dir.x * MOVESPEED;
			all->player.pos.y += all->player.dir.y * MOVESPEED;
	}
	else if (keycode == 115) // S (moving backwards)
	{
			all->player.pos.x -= all->player.dir.x * MOVESPEED;
			all->player.pos.y -= all->player.dir.y * MOVESPEED;
	}
	else
		return (0);
	display_minimap(all, 20, 20);
	return (1);
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
