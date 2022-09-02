#include "cub3d.h"

// (x * cos(0,0174533)) + (-sin(0,0174533) * y) = x'
// (sin(0,0174533) * x) + (cos(0,0174533) * y) = y'

static void	move_player_direction(int keycode, t_all *all)
{
	double	old_dirX;
	double	old_dirY;
	double	new_dirX;
	double	new_dirY;

	old_dirX = all->player.dir.x;
	old_dirY = all->player.dir.y;

	if (keycode == 65361)  // fleche GAUCHE
	{
		new_dirX = (old_dirX * cos(-ROTSPEED)) + (-sin(-ROTSPEED) * old_dirY);
		new_dirY = (sin(-ROTSPEED) * old_dirX) + (cos(-ROTSPEED) * old_dirY);
	}
	else if (keycode == 65363)  // fleche DROITE
	{
		new_dirX = (old_dirX * cos(ROTSPEED)) + (-sin(ROTSPEED) * old_dirY);
		new_dirY = (sin(ROTSPEED) * old_dirX) + (cos(ROTSPEED) * old_dirY);
	}
	else
		return ;
	all->player.dir.x = new_dirX;
	all->player.dir.y = new_dirY;
	player_plane(all);
}

static void	move_player_position(int keycode, t_all *all, double *x, double *y)
{
	if (keycode == 97) // A (moving left)
	{
		*x = all->player.pos.x + all->player.dir.y * MOVESPEED;
		*y = all->player.pos.y - all->player.dir.x * MOVESPEED;
	}
	else if (keycode == 100) // D (moving right)
	{
		*x = all->player.pos.x - all->player.dir.y * MOVESPEED;
		*y = all->player.pos.y + all->player.dir.x * MOVESPEED;
	}
	else if (keycode == 119) // W (moving forwards)
	{
		*x = all->player.pos.x + all->player.dir.x * MOVESPEED;
		*y = all->player.pos.y + all->player.dir.y * MOVESPEED;

	}
	else if (keycode == 115) // S (moving backwards)
	{
		*x = all->player.pos.x - all->player.dir.x * MOVESPEED;
		*y = all->player.pos.y - all->player.dir.y * MOVESPEED;
	}
	else
		return ;
}

int	key_hook(int keycode, t_all *all)
{
	double	new_pos_x;
	double	new_pos_y;

	if (keycode == 65361 || keycode == 65363)
		move_player_direction(keycode, all);
	else if (keycode == 97 || keycode == 100 || keycode == 119 || keycode == 115)
	{
		move_player_position(keycode, all, &new_pos_x, &new_pos_y);
		if (all->map[(int)new_pos_y][(int)new_pos_x] == '0')
		{
			all->player.pos.x = new_pos_x;
			all->player.pos.y = new_pos_y;
		}
	}
	else if (keycode == 65307) // (ESC)
		destroy_all_exit(all);
	else
		return (0);
	display_minimap(all, 20, 20);
	render_raycasting(all);
	return (1);
}

// right - D = 100
// left - A = 97
// front - W = 119
// back - S = 115

// fleche droite = 65363
// fleche gauche = 65361
// esc = 65307
