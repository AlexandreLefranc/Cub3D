#include "cub3d.h"

static void	move_player_direction(t_all *all)
{
	double	old_dirX;
	double	old_dirY;
	double	new_dirX;
	double	new_dirY;

	old_dirX = all->player.dir.x;
	old_dirY = all->player.dir.y;

	if (all->player.left_arrow_press == true)  // fleche GAUCHE
	{
		new_dirX = (old_dirX * cos(-ROTSPEED)) + (-sin(-ROTSPEED) * old_dirY);
		new_dirY = (sin(-ROTSPEED) * old_dirX) + (cos(-ROTSPEED) * old_dirY);
	}
	else if (all->player.right_arrow_press == true)  // fleche DROITE
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

static void	move_player_position(t_all *all, double *x, double *y)
{
	if (all->player.a_press == true) // A (moving left)
	{
		*x = all->player.pos.x + all->player.dir.y * MOVESPEED;
		*y = all->player.pos.y - all->player.dir.x * MOVESPEED;
	}
	else if (all->player.d_press == true) // D (moving right)
	{
		*x = all->player.pos.x - all->player.dir.y * MOVESPEED;
		*y = all->player.pos.y + all->player.dir.x * MOVESPEED;
	}
	else if (all->player.w_press == true) // W (moving forwards)
	{
		*x = all->player.pos.x + all->player.dir.x * MOVESPEED;
		*y = all->player.pos.y + all->player.dir.y * MOVESPEED;

	}
	else if (all->player.s_press == true) // S (moving backwards)
	{
		*x = all->player.pos.x - all->player.dir.x * MOVESPEED;
		*y = all->player.pos.y - all->player.dir.y * MOVESPEED;
	}
	else
		return ;
}

int	key_press(int keycode, t_all *all)
{
	if (keycode == 109) // m
		all->minimap_display = true;
	if (keycode == 65361)  // fleche GAUCHE
		all->player.left_arrow_press = true;
	else if (keycode == 65363)  // fleche DROITE
		all->player.right_arrow_press = true;
	else if (keycode == 97) // A (moving left)
		all->player.a_press = true;
	else if (keycode == 100) // D (moving right)
		all->player.d_press = true;
	else if (keycode == 119) // W (moving forwards)
		all->player.w_press = true;
	else if (keycode == 115) // S (moving backwards)
		all->player.s_press = true;
	else if (keycode == 65307) // (ESC)
		destroy_all_exit(all);
	return (0);
}

int	key_release(int keycode, t_all *all)
{
	if (keycode == 109) // m
		all->minimap_display = false;
	if (keycode == 65361)  // fleche GAUCHE
		all->player.left_arrow_press = false;
	else if (keycode == 65363)  // fleche DROITE
		all->player.right_arrow_press = false;
	else if (keycode == 97) // A (moving left)
		all->player.a_press = false;
	else if (keycode == 100) // D (moving right)
		all->player.d_press = false;
	else if (keycode == 119) // W (moving forwards)
		all->player.w_press = false;
	else if (keycode == 115) // S (moving backwards)
		all->player.s_press = false;
	return (0);
}

int	loop_hook(t_all *all)
{
	double	new_pos_x;
	double	new_pos_y;

	if (all->minimap_display == true && ft_strlen(all->map[0]) * TILE < SCREENW &&
		ft_strtabsize(all->map) * TILE < SCREENH)
			draw_minimap(all, &all->img);
	if (all->player.left_arrow_press == true || all->player.right_arrow_press == true)
		move_player_direction(all);
	else if (all->player.a_press == true || all->player.d_press == true
		|| all->player.w_press == true || all->player.s_press == true)
	{
		move_player_position(all, &new_pos_x, &new_pos_y);
		if (all->map[(int)new_pos_y][(int)new_pos_x] == '0')
		{
			all->player.pos.x = new_pos_x;
			all->player.pos.y = new_pos_y;
		}
	}
	else
		return (0);
	// usleep(10000);
	render_raycasting(all);
	return (1);
}
