/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:07:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/06 16:49:44 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(t_data *img, t_point start, t_point end, int i)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;

	dx = (end.x - start.x);
	dy = (end.y - start.y);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = start.x;
	y = start.y;
	i = 1;
	while (i <= step)
	{
		my_mlx_pixel_put(img, (int)x, (int)y, 0x000000FF);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

static void	draw_player_box(t_data *img, t_point start, int color)
{
	int	i;
	int	j;

	i = -2;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			my_mlx_pixel_put(img, start.x + i, start.y + j, color);
			j++;
		}
		i++;
	}
}

void	display_player(t_all *all, t_data *img)
{
	t_point	start;
	t_point	end;

	start.x = (int)(all->player.pos.x * TILE);
	start.y = (int)(all->player.pos.y * TILE);
	end.x = (int)((all->player.pos.x + all->player.dir.x) * TILE);
	end.y = (int)((all->player.pos.y + all->player.dir.y) * TILE);
	draw_line(img, start, end, 0);
	start.x = (int)(all->player.pos.x * TILE);
	start.y = (int)(all->player.pos.y * TILE);
	end.x = (int)((all->player.pos.x
				+ (all->player.dir.x + all->player.plane.x) / 2) * TILE);
	end.y = (int)((all->player.pos.y
				+ (all->player.dir.y + all->player.plane.y) / 2) * TILE);
	draw_line(img, start, end, 0);
	start.x = (int)(all->player.pos.x * TILE);
	start.y = (int)(all->player.pos.y * TILE);
	end.x = (int)((all->player.pos.x
				+ (all->player.dir.x - all->player.plane.x) / 2) * TILE);
	end.y = (int)((all->player.pos.y
				+ (all->player.dir.y - all->player.plane.y) / 2) * TILE);
	draw_line(img, start, end, 0);
	draw_player_box(img, start, 0x00FF4500);
}

void	draw_minimap(t_all *all, t_data *img)
{
	size_t	x;
	size_t	y;
	size_t	xmax;
	size_t	ymax;

	printf("here\n");
	y = 0;
	xmax = ft_strlen(all->map[y]);
	ymax = ft_strtabsize(all->map);
	while (y < ymax)
	{
		x = 0;
		while (x < xmax)
		{
			if (all->map[y][x] == '1' || all->map[y][x] == ' ')
				my_mlx_square(img, x * TILE, y * TILE, 0x00000000);
			else
				my_mlx_square(img, x * TILE, y * TILE, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	display_player(all, img);
}
