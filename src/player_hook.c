/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:31:51 by lmarecha          #+#    #+#             */
/*   Updated: 2022/09/08 19:35:25 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player_direction(t_all *all)
{
	double	old_dir_x;
	double	old_dir_y;
	double	new_dirx;
	double	new_diry;

	old_dir_x = all->player.dir.x;
	old_dir_y = all->player.dir.y;
	if (all->player.left_arrow_press == true)
	{
		new_dirx = (old_dir_x * cos(-ROTSPEED)) + (-sin(-ROTSPEED) * old_dir_y);
		new_diry = (sin(-ROTSPEED) * old_dir_x) + (cos(-ROTSPEED) * old_dir_y);
		all->player.dir.x = new_dirx;
		all->player.dir.y = new_diry;
	}
	old_dir_x = all->player.dir.x;
	old_dir_y = all->player.dir.y;
	if (all->player.right_arrow_press == true)
	{
		new_dirx = (old_dir_x * cos(ROTSPEED)) + (-sin(ROTSPEED) * old_dir_y);
		new_diry = (sin(ROTSPEED) * old_dir_x) + (cos(ROTSPEED) * old_dir_y);
		all->player.dir.x = new_dirx;
		all->player.dir.y = new_diry;
	}
	player_plane(all);
}

int	key_press(int keycode, t_all *all)
{
	if (keycode == 109)
		all->minimap_display = !all->minimap_display;
	if (keycode == 65361)
		all->player.left_arrow_press = true;
	else if (keycode == 65363)
		all->player.right_arrow_press = true;
	else if (keycode == 97)
		all->player.a_press = true;
	else if (keycode == 100)
		all->player.d_press = true;
	else if (keycode == 119)
		all->player.w_press = true;
	else if (keycode == 115)
		all->player.s_press = true;
	else if (keycode == 65307)
		destroy_all_exit(all);
	return (0);
}

int	key_release(int keycode, t_all *all)
{
	if (keycode == 65361)
		all->player.left_arrow_press = false;
	else if (keycode == 65363)
		all->player.right_arrow_press = false;
	else if (keycode == 97)
		all->player.a_press = false;
	else if (keycode == 100)
		all->player.d_press = false;
	else if (keycode == 119)
		all->player.w_press = false;
	else if (keycode == 115)
		all->player.s_press = false;
	return (0);
}

int	loop_hook(t_all *all)
{
	move_player_direction(all);
	move_player_position(all);
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

// minimap = m = 109
