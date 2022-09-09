/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:44:14 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/09 12:09:26 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wall(t_all *all)
{
	int	hit;

	hit = 0;
	all->rc.mapx = (int)all->player.pos.x;
	all->rc.mapy = (int)all->player.pos.y;
	while (hit == 0)
	{
		if (all->rc.sd_dist_x < all->rc.sd_dist_y)
		{
			all->rc.sd_dist_x += all->rc.ddist_x;
			all->rc.mapx += all->rc.side_x;
			all->rc.side = 0;
		}
		else
		{
			all->rc.sd_dist_y += all->rc.ddist_y;
			all->rc.mapy += all->rc.side_y;
			all->rc.side = 1;
		}
		if (all->map[all->rc.mapy][all->rc.mapx] == '1')
			hit = 1;
	}
}

void	find_distance(t_all *all)
{
	double	angle;
	// double	new_dist;

	if (all->rc.side == 0)
		all->rc.wall_dist = all->rc.sd_dist_x - all->rc.ddist_x;
	else
		all->rc.wall_dist = all->rc.sd_dist_y - all->rc.ddist_y;
	angle = angle_between_vector(all->player.dir, all->rc.ray);
	all->rc.wall_dist = all->rc.wall_dist * cos(angle);
	if (all->rc.wall_dist < 0.05)
		all->rc.wall_dist = 0.05;
}

void	find_texture(t_all *all)
{
	if (all->rc.side_x == 1 && all->rc.side == 0)
		all->rc.texture = &all->texture_we;
	else if ((all->rc.side_x == 1 && all->rc.side == 1)
		|| (all->rc.side_x == -1 && all->rc.side == 1))
	{
		if (all->rc.side_y == 1)
			all->rc.texture = &all->texture_no;
		else if (all->rc.side_y == -1)
			all->rc.texture = &all->texture_so;
	}
	else if (all->rc.side_x == -1 && all->rc.side == 0)
		all->rc.texture = &all->texture_ea;
}

void	find_wall_height_and_texture_x(t_all *all)
{
	all->rc.wall_height = (int)(SCREENH / all->rc.wall_dist);
	all->rc.draw_start = -all->rc.wall_height / 2 + SCREENH / 2;
	if (all->rc.draw_start < 0)
		all->rc.draw_start = 0;
	all->rc.draw_end = all->rc.wall_height / 2 + SCREENH / 2;
	if (all->rc.draw_end >= SCREENH)
		all->rc.draw_end = SCREENH - 1;
	if (all->rc.side == 0)
		all->rc.wall_x = all->player.pos.y + all->rc.wall_dist * all->rc.ray.y;
	else
		all->rc.wall_x = all->player.pos.x + all->rc.wall_dist * all->rc.ray.x;
	all->rc.wall_x -= floor((all->rc.wall_x));
	all->rc.texture_x = (int)(all->rc.wall_x * all->rc.texture->width);
	if (all->rc.side == 0 && all->rc.ray.x > 0)
		all->rc.texture_x = all->rc.texture->width - all->rc.texture_x - 1;
	if (all->rc.side == 1 && all->rc.ray.y < 0)
		all->rc.texture_x = all->rc.texture->width - all->rc.texture_x - 1;
}
