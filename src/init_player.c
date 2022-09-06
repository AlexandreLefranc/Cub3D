/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:53:50 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/06 16:58:19 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	find_player_position(char **map, int *x, int *y)
{
	while (map[*y])
	{
		*x = 0;
		while (map[*y][*x])
		{
			if (map[*y][*x] == 'N' || map[*y][*x] == 'S' || map[*y][*x] == 'W'
				|| map[*y][*x] == 'E')
				return (map[*y][*x]);
			(*x)++;
		}
		(*y)++;
	}
	return ('\0');
}

static void	init_player_pos(char **map, t_vec *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (find_player_position(map, &x, &y) != '\0')
	{
		pos->x = x + 0.5;
		pos->y = y + 0.5;
	}
}

static void	init_player_dir(char **map, t_vec *dir)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (find_player_position(map, &x, &y) == 'N')
	{
		dir->x = 0;
		dir->y = -1;
	}
	if (find_player_position(map, &x, &y) == 'S')
	{
		dir->x = 0;
		dir->y = 1;
	}
	if (find_player_position(map, &x, &y) == 'E')
	{
		dir->x = 1;
		dir->y = 0;
	}
	if (find_player_position(map, &x, &y) == 'W')
	{
		dir->x = -1;
		dir->y = 0;
	}
}

static void	remove_player_map_position(t_all *all)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < ft_strtabsize(all->map))
	{
		x = 0;
		while (x < ft_strlen(all->map[y]))
		{
			if (all->map[y][x] == 'N' || all->map[y][x] == 'S'
				|| all->map[y][x] == 'W' || all->map[y][x] == 'E' )
				all->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	init_player(t_all *all)
{
	init_player_pos(all->map, &all->player.pos);
	init_player_dir(all->map, &all->player.dir);
	player_plane(all);
	remove_player_map_position(all);
}
