/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:23:14 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/12 07:56:23 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player_position_up(t_all *all)
{
	double	new_x;
	double	new_y;

	new_x = all->player.pos.x;
	new_y = all->player.pos.y;
	if (all->player.w_press == true)
	{
		new_x = all->player.pos.x + all->player.dir.x * MOVESPEED;
		new_y = all->player.pos.y + all->player.dir.y * MOVESPEED;
		if (all->map[(int)new_y][(int)new_x] == '0')
		{
			all->player.pos.x = new_x;
			all->player.pos.y = new_y;
		}
	}
}

static void	move_player_position_down(t_all *all)
{
	double	new_x;
	double	new_y;

	new_x = all->player.pos.x;
	new_y = all->player.pos.y;
	if (all->player.s_press == true)
	{
		new_x = all->player.pos.x - all->player.dir.x * MOVESPEED;
		new_y = all->player.pos.y - all->player.dir.y * MOVESPEED;
		if (all->map[(int)new_y][(int)new_x] == '0')
		{
			all->player.pos.x = new_x;
			all->player.pos.y = new_y;
		}
	}
}

static void	move_player_position_left(t_all *all)
{
	double	new_x;
	double	new_y;

	new_x = all->player.pos.x;
	new_y = all->player.pos.y;
	if (all->player.a_press == true)
	{
		new_x = all->player.pos.x + all->player.dir.y * MOVESPEED;
		new_y = all->player.pos.y - all->player.dir.x * MOVESPEED;
		if (all->map[(int)new_y][(int)new_x] == '0')
		{
			all->player.pos.x = new_x;
			all->player.pos.y = new_y;
		}
	}
}

static void	move_player_position_right(t_all *all)
{
	double	new_x;
	double	new_y;

	new_x = all->player.pos.x;
	new_y = all->player.pos.y;
	if (all->player.d_press == true)
	{
		new_x = all->player.pos.x - all->player.dir.y * MOVESPEED;
		new_y = all->player.pos.y + all->player.dir.x * MOVESPEED;
		if (all->map[(int)new_y][(int)new_x] == '0')
		{
			all->player.pos.x = new_x;
			all->player.pos.y = new_y;
		}
	}
}

void	move_player_position(t_all *all)
{
	move_player_position_up(all);
	move_player_position_down(all);
	move_player_position_left(all);
	move_player_position_right(all);
}
